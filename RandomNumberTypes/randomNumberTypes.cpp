/*Note: This program will not run unless the .h file is
*in the same directory. It also requires libsodium and 
*raylib to be installed
*/

#include "randomNumberTypes.h"

#include <sodium.h>
#include <raylib.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <string>

// ============================================================================
// PART 1: NUMBER GENERATION AND REPLAY
//
// Teach this section first. There is no graphics code in this section.
// ============================================================================

namespace demo
{
    std::uint32_t MillisecondSeed()
    {
        // Deliberately use a clock with millisecond granularity.
        //
        // Many iterations of a tight loop can occur during one millisecond.
        // Those iterations receive exactly the same seed.
        //
        // A timestamp is also guessable. It is NOT a security entropy source.
        const auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            ).count();

        // Keep the low 32 bits as our deliberately weak seed.
        return static_cast<std::uint32_t>(milliseconds);
    }

    int SimpleFromSeed(std::uint32_t seed)
    {
        // A deliberately simple linear congruential calculation:
        //
        //     next = a * state + c  (modulo 2^32)
        //
        // Assignment to uint32_t keeps the low 32 bits.
        std::uint32_t state = seed;
        state = state * 1664525u + 1013904223u;

        // Take some upper bits, then reduce to 0..99.
        //
        // This modulo mapping also introduces a small bias because 65536
        // is not divisible by 100. That is intentional in this BAD example.
        return static_cast<int>((state >> 16u) % ValueCount);
    }

    void GenerateSimple(SampleSet& output, ClockSeeds& usedSeeds)
    {
        for (std::size_t i = 0; i < SampleCount; ++i)
        {
            // BAD PRACTICE: reseed from the clock on EVERY iteration.
            //
            // This is analogous to repeatedly calling srand(time...),
            // except that we use a tiny explicit algorithm so its behavior
            // does not depend on a platform's implementation of rand().
            const std::uint32_t seed = MillisecondSeed();

            usedSeeds[i] = seed;
            output.values[i] = SimpleFromSeed(seed);
        }

        // Do not sleep here. Sleeping would hide the repeated-seed problem.
        // The exact number of spikes depends on machine speed and scheduling.
    }

    void GenerateStatistical(SampleSet& output, std::uint32_t seed)
    {
        // Seed ONCE, outside the loop.
        //
        // Mersenne Twister has useful statistical properties for many
        // non-security applications. It is NOT a cryptographic generator.
        std::mt19937 engine(seed);

        // A distribution maps the engine output into the desired range.
        // Do not replace this with engine() % 100.
        std::uniform_int_distribution<int> distribution(0, ValueCount - 1);

        for (std::size_t i = 0; i < SampleCount; ++i)
        {
            output.values[i] = distribution(engine);
        }

        // Same seed + same engine + same distribution implementation
        // gives the same sequence.
        //
        // The distribution's exact mapping is not required to be identical
        // between different standard-library implementations.
    }

    void GenerateSecure(SampleSet& output)
    {
        // SOURCE OF ENTROPY / "CHAOS":
        //
        // libsodium's default backend obtains randomness from the operating
        // system's secure random facility, rather than our public timestamp.
        //
        // Examples documented by libsodium include:
        //   Linux / FreeBSD: getrandom() on supported kernels
        //   Windows:        RtlGenRandom()
        //   OpenBSD:        arc4random()
        //   Other Unices:   /dev/urandom
        //
        // The OS manages its entropy sources and cryptographic RNG state.
        // Depending on the OS and hardware, entropy inputs can include
        // hardware RNGs and unpredictable event/interrupt timing.
        //
        // We do NOT promise that every returned integer is a new physical
        // measurement of chaos. The OS normally expands accumulated entropy
        // using a cryptographically secure generator.
        //
        // There is deliberately NO public application seed parameter here.
        for (std::size_t i = 0; i < SampleCount; ++i)
        {
            // Uniform 0..99, with unbiased range reduction.
            output.values[i] =
                static_cast<int>(randombytes_uniform(ValueCount));
        }

        // No insecure fallback is provided if secure randomness is unavailable.
        //
        // Also: a single 0..99 value is far too small to be a secret key!
        // This small range is ONLY for displaying the distribution.
    }

    void Analyze(SampleSet& data)
    {
        data.histogram.fill(0);
        data.occupiedBins = 0;
        data.longestRun = 1;

        int currentRun = 1;

        for (std::size_t i = 0; i < SampleCount; ++i)
        {
            ++data.histogram[data.values[i]];

            if (i > 0)
            {
                if (data.values[i] == data.values[i - 1])
                    ++currentRun;
                else
                    currentRun = 1;

                data.longestRun = std::max(data.longestRun, currentRun);
            }
        }

        for (int count : data.histogram)
        {
            if (count != 0)
                ++data.occupiedBins;
        }
    }

    void GenerateExperiment(Experiment& experiment)
    {
        GenerateSimple(experiment.sets[0], experiment.simpleSeeds);
        GenerateStatistical(experiment.sets[1], experiment.mtSeed);
        GenerateSecure(experiment.sets[2]);

        for (SampleSet& set : experiment.sets)
            Analyze(set);
    }

    void RepeatReplayExperiment(
        const Experiment& experiment,
        ReplayResult& result)
    {
        ++result.round;
        result.matches.fill(0);

        // Restart MT using the SAME PUBLIC SEED.
        std::mt19937 attackerEngine(experiment.mtSeed);
        std::uniform_int_distribution<int> distribution(0, ValueCount - 1);

        for (std::size_t i = 0; i < SampleCount; ++i)
        {
            // SIMPLE:
            // Replay using the recorded millisecond seed for this iteration.
            //
            // If a whole batch used one millisecond, that batch needs only
            // that one seed. If time advanced, the seed schedule matters.
            const int simpleReplay =
                SimpleFromSeed(experiment.simpleSeeds[i]);

            // STATISTICAL:
            // An observer who knows the seed can reproduce every value.
            const int mtReplay = distribution(attackerEngine);

            // SECURE:
            // This is a NEW OS random draw, NOT a replay or a prediction.
            // Passing our public MT seed to the OS RNG is not an operation
            // exposed by this API.
            const int freshSecure =
                static_cast<int>(randombytes_uniform(ValueCount));

            const std::array<int, 3> candidates{
                simpleReplay, mtReplay, freshSecure
            };

            for (int generator = 0; generator < 3; ++generator)
            {
                if (candidates[generator] ==
                    experiment.sets[generator].values[i])
                {
                    ++result.matches[generator];
                }

                if (i < PreviewCount)
                    result.preview[generator][i] = candidates[generator];
            }
        }

        // IMPORTANT COUNTEREXAMPLE:
        //
        // Even a cryptographic deterministic generator repeats when given
        // the same complete seed. An exposed seed is NOT magically safe.
        //
        // This deliberately public, mostly-zero seed is for this test ONLY.
        // It is never used by GenerateSecure().
        std::array<unsigned char, randombytes_SEEDBYTES> publicSeed{};
        publicSeed[0] = 42;

        std::array<unsigned char, 32> cryptoA{};
        std::array<unsigned char, 32> cryptoB{};

        randombytes_buf_deterministic(
            cryptoA.data(), cryptoA.size(), publicSeed.data());

        randombytes_buf_deterministic(
            cryptoB.data(), cryptoB.size(), publicSeed.data());

        result.knownCryptoSeedReplays = (cryptoA == cryptoB);

        std::cout
            << "\nReplay round " << result.round
            << "\n  Simple, known seed schedule: "
            << result.matches[0] << "/" << SampleCount
            << "\n  MT, public seed " << experiment.mtSeed << ": "
            << result.matches[1] << "/" << SampleCount
            << "\n  Independent secure-draw coincidences: "
            << result.matches[2] << "/" << SampleCount
            << "\n  Known cryptographic seed also replays: "
            << (result.knownCryptoSeedReplays ? "YES" : "NO")
            << "\n";

        // With independent uniform values in 0..99, about 1% of positions
        // match by chance. Neither matching nor differing samples proves
        // cryptographic security.
    }
}

// ============================================================================
// PART 2: VISUALIZATION ONLY
//
// Everything below this divider handles presentation or GUI controls.
// The number-generation algorithms above do not depend on this code.
// ============================================================================

namespace demo
{
    namespace
    {
        // Render to one fixed logical canvas, then scale it into the window.
        // This keeps all three panels visible even when the window is resized.
        constexpr int CanvasWidth = 1440;
        constexpr int CanvasHeight = 900;

        const Color Background{6, 10, 24, 255};
        const Color Panel{13, 21, 40, 245};
        const Color Muted{153, 173, 201, 255};
        const Color TextColor{232, 241, 255, 255};

        const std::array<Color, 3> Accent{{
            {255, 91, 128, 255},   // Pink: deliberately bad.
            {55, 208, 255, 255},   // Cyan: statistical.
            {102, 255, 177, 255}   // Green: secure.
        }};

        void Text(
            float x, float y, const std::string& text,
            int size = 18, Color color = TextColor)
        {
            DrawText(
                text.c_str(),
                static_cast<int>(x),
                static_cast<int>(y),
                size,
                color);
        }

        std::string PreviewText(const Samples& values)
        {
            std::string text;

            for (std::size_t i = 0; i < PreviewCount; ++i)
            {
                if (i != 0) text += "  ";
                if (values[i] < 10) text += "0";
                text += std::to_string(values[i]);
            }

            return text;
        }

        std::string PreviewText(const Preview& values)
        {
            std::string text;

            for (std::size_t i = 0; i < PreviewCount; ++i)
            {
                if (i != 0) text += "  ";
                if (values[i] < 10) text += "0";
                text += std::to_string(values[i]);
            }

            return text;
        }

        int Peak(const SampleSet& set)
        {
            return *std::max_element(
                set.histogram.begin(), set.histogram.end());
        }

        void DrawAnimatedBackground(float time)
        {
            ClearBackground(Background);

            // Decorative motion uses only arithmetic and trigonometry.
            // It does not consume or modify any experimental random stream.
            for (int i = 0; i < 70; ++i)
            {
                const float x = std::fmod(
                    i * 193.7f + time * (4.0f + i % 7),
                    static_cast<float>(CanvasWidth));

                const float y =
                    450.0f + 420.0f * std::sin(i * 2.17f + time * 0.08f);

                const float brightness =
                    0.10f + 0.16f *
                    (0.5f + 0.5f * std::sin(time + i));

                DrawCircleGradient(
                    static_cast<int>(x), static_cast<int>(y),
                    12.0f, Fade(SKYBLUE, brightness), BLANK);

                DrawCircleV({x, y}, 1.3f, Fade(SKYBLUE, 0.55f));
            }

            // Slow orbital arcs give the scene a "science console" look.
            for (int i = 0; i < 3; ++i)
            {
                DrawRing(
                    {1240.0f, 70.0f},
                    75.0f + i * 18.0f,
                    76.0f + i * 18.0f,
                    time * 12.0f + i * 50.0f,
                    time * 12.0f + i * 50.0f + 210.0f,
                    80,
                    Fade(Accent[i], 0.18f));
            }
        }

        void DrawHistogram(
            const SampleSet& set,
            Rectangle plot,
            Color accent,
            int yMaximum,
            float animationAge,
            float time)
        {
            DrawRectangleRec(plot, {7, 13, 27, 255});

            // All panels use linear count axes.
            // S toggles between independent and common vertical scaling.
            for (int line = 0; line <= 4; ++line)
            {
                const float y = plot.y + plot.height * line / 4.0f;

                DrawLineEx(
                    {plot.x, y},
                    {plot.x + plot.width, y},
                    1.0f,
                    Fade(Muted, 0.15f));
            }

            const float barWidth = plot.width / ValueCount;

            // Ease-out entrance animation. The faint full-height bars remain
            // visible underneath, so the data is not replaced by animation.
            const float p = std::clamp(animationAge / 1.6f, 0.0f, 1.0f);
            const float growth = 1.0f - std::pow(1.0f - p, 3.0f);

            const float scanner =
                std::fmod(time * 20.0f, static_cast<float>(ValueCount));

            for (int value = 0; value < ValueCount; ++value)
            {
                const float fullHeight =
                    plot.height * set.histogram[value] / yMaximum;

                const float x = plot.x + value * barWidth;

                // Static data silhouette.
                DrawRectangleRec(
                    {x, plot.y + plot.height - fullHeight,
                     barWidth - 0.6f, fullHeight},
                    Fade(accent, 0.18f));

                if (set.histogram[value] == 0)
                    continue;

                const float height = fullHeight * growth;
                const float top = plot.y + plot.height - height;

                DrawRectangleGradientV(
                    static_cast<int>(x),
                    static_cast<int>(top),
                    std::max(1, static_cast<int>(barWidth - 0.6f)),
                    std::max(1, static_cast<int>(height)),
                    accent,
                    Fade(accent, 0.25f));

                // Moving scanner lights up the actual bar tops.
                const float distance = std::fabs(value - scanner);

                if (distance < 5.0f)
                {
                    const float glow = 1.0f - distance / 5.0f;

                    DrawCircleGradient(
                        static_cast<int>(x + barWidth * 0.5f),
                        static_cast<int>(top),
                        12.0f,
                        Fade(accent, glow * 0.65f),
                        BLANK);

                    DrawCircleV(
                        {x + barWidth * 0.5f, top},
                        1.8f,
                        Fade(WHITE, glow));
                }
            }

            // Expected count for a uniform distribution:
            // 10,000 samples / 100 values = 100 samples per value.
            const float expected =
                static_cast<float>(SampleCount) / ValueCount;

            const float expectedY =
                plot.y + plot.height -
                plot.height * expected / yMaximum;

            for (float x = plot.x; x < plot.x + plot.width; x += 10.0f)
            {
                DrawLineEx(
                    {x, expectedY},
                    {std::min(x + 5.0f, plot.x + plot.width), expectedY},
                    1.0f,
                    Fade(WHITE, 0.65f));
            }

            Text(plot.x, plot.y - 20, "COUNT", 14, Muted);

            Text(
                plot.x - 39, plot.y - 3,
                std::to_string(yMaximum), 13, Muted);

            Text(
                plot.x - 17, plot.y + plot.height - 10,
                "0", 13, Muted);

            Text(plot.x, plot.y + plot.height + 8, "0", 14, Muted);

            Text(
                plot.x + plot.width * 0.46f,
                plot.y + plot.height + 8,
                "VALUE", 14, Muted);

            Text(
                plot.x + plot.width - 18,
                plot.y + plot.height + 8,
                "99", 14, Muted);
        }

        void DrawLagPlot(
            const Samples& values,
            Rectangle box,
            Color accent)
        {
            // Every adjacent pair is included:
            //
            //     horizontal coordinate = values[i]
            //     vertical coordinate   = values[i+1]
            //
            // Repeated points overlap. This is a scatter plot, not a count map.
            DrawRectangleRec(box, {5, 10, 22, 255});

            for (std::size_t i = 0; i + 1 < SampleCount; ++i)
            {
                const float x =
                    box.x + 2.0f +
                    values[i] * (box.width - 5.0f) / (ValueCount - 1);

                const float y =
                    box.y + box.height - 3.0f -
                    values[i + 1] * (box.height - 5.0f) /
                    (ValueCount - 1);

                DrawPixel(
                    static_cast<int>(x),
                    static_cast<int>(y),
                    Fade(accent, 0.70f));
            }

            DrawRectangleLinesEx(box, 1.0f, Fade(accent, 0.45f));
        }

        void DrawPanel(
            const Experiment& experiment,
            const ReplayResult& replay,
            int index,
            Rectangle card,
            int commonMaximum,
            bool commonScale,
            float animationAge,
            float time)
        {
            const SampleSet& set = experiment.sets[index];
            const Color accent = Accent[index];

            const char* titles[] = {
                "01 / CLOCK-RESEEDED",
                "02 / MERSENNE TWISTER",
                "03 / OS SECURE RANDOM"
            };

            const char* subtitles[] = {
                "Intentionally bad: milliseconds in a loop",
                "Statistical PRNG; NOT for secrets",
                "libsodium + operating-system entropy"
            };

            DrawRectangleRounded(card, 0.04f, 12, Panel);

            DrawRectangleRec(
                {card.x + 12, card.y, card.width - 24, 3},
                accent);

            const float x = card.x + 20;
            const float y = card.y;

            Text(x, y + 19, titles[index], 22, accent);
            Text(x, y + 52, subtitles[index], 16, Muted);

            const int localMaximum =
                std::max(125, static_cast<int>(std::ceil(Peak(set) * 1.1)));

            const int yMaximum =
                commonScale ? commonMaximum : localMaximum;

            DrawHistogram(
                set,
                {card.x + 44, y + 100, card.width - 64, 185},
                accent,
                yMaximum,
                animationAge,
                time);

            Text(x, y + 318, "ORDER: x[i] vs x[i+1]", 16, Muted);

            DrawLagPlot(
                set.values,
                {x, y + 343, 110, 110},
                accent);

            Text(x + 129, y + 344, "10,000 stored values", 17);

            Text(
                x + 129, y + 372,
                "Occupied bins: " + std::to_string(set.occupiedBins),
                17);

            Text(
                x + 129, y + 400,
                "Longest run: " + std::to_string(set.longestRun),
                17);

            Text(
                x + 129, y + 428,
                "Peak count: " + std::to_string(Peak(set)),
                17);

            Text(x, y + 475, "ORIGINAL / FIRST 8", 16, Muted);
            Text(x, y + 499, PreviewText(set.values), 23, accent);

            Text(
                x, y + 536,
                index == 2 ? "FRESH OS DRAW / NOT A PREDICTION"
                           : "PREDICTED / REPLAYED FIRST 8",
                16,
                Muted);

            Text(
                x, y + 560,
                PreviewText(replay.preview[index]),
                23,
                accent);

            if (index < 2)
            {
                Text(
                    x, y + 601,
                    "EXACT REPLAY: " +
                    std::to_string(replay.matches[index]) + " / 10000",
                    20,
                    accent);
            }
            else
            {
                Text(
                    x, y + 601,
                    "Chance matches: " +
                    std::to_string(replay.matches[index]) + " / 10000",
                    20,
                    accent);
            }

            Text(
                x, y + 631,
                index == 0 ? "Replay uses saved per-iteration clock seeds."
                : index == 1 ? "Public seed: " +
                                   std::to_string(experiment.mtSeed)
                             : "Different samples are NOT a security proof.",
                15,
                Muted);
        }
    }

    void ShowVisualization(Experiment& experiment)
    {
        // Window creation, events, animation and drawing live here.
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
        InitWindow(1200, 750, "Randomness Lab - Three Ways to Roll");
        SetWindowMinSize(960, 600);

        if (!IsWindowReady())
            return;

        SetTargetFPS(60);

        RenderTexture2D canvas =
            LoadRenderTexture(CanvasWidth, CanvasHeight);

        if (canvas.id == 0)
        {
            std::cerr << "Could not create the visualization canvas.\n";
            CloseWindow();
            return;
        }

        SetTextureFilter(canvas.texture, TEXTURE_FILTER_BILINEAR);

        ReplayResult replay{};
        RepeatReplayExperiment(experiment, replay);

        bool commonScale = false;
        bool animate = true;
        float animationAge = 0.0f;
        float time = 0.0f;

        while (!WindowShouldClose())
        {
            // P repeats the prediction/replay experiment WITHOUT changing
            // the original 30,000 stored values.
            if (IsKeyPressed(KEY_P))
                RepeatReplayExperiment(experiment, replay);

            // R creates a new clock sample and a new secure sample.
            // MT intentionally remains the same because its seed is unchanged.
            if (IsKeyPressed(KEY_R))
            {
                GenerateExperiment(experiment);
                replay = ReplayResult{};
                RepeatReplayExperiment(experiment, replay);
                animationAge = 0.0f;
            }

            // A common Y scale is useful for honest magnitude comparison.
            // Independent scales make the two approximately uniform
            // distributions easier to inspect alongside a huge clock spike.
            if (IsKeyPressed(KEY_S))
                commonScale = !commonScale;

            // Pause decorative animation for explanation or screenshots.
            if (IsKeyPressed(KEY_SPACE))
                animate = !animate;

            if (animate)
            {
                const float dt = GetFrameTime();
                time += dt;
                animationAge += dt;
            }

            int largestPeak = 0;

            for (const SampleSet& set : experiment.sets)
                largestPeak = std::max(largestPeak, Peak(set));

            const int commonMaximum =
                std::max(
                    125,
                    static_cast<int>(std::ceil(largestPeak * 1.1)));

            // Draw the entire presentation to one logical canvas.
            BeginTextureMode(canvas);
            DrawAnimatedBackground(time);

            Text(24, 18, "RANDOMNESS LAB", 38);

            Text(
                26, 66,
                "30,000 numbers. Three generators. "
                "Looking random is not the same as being unpredictable.",
                19,
                Muted);

            Text(
                26, 103,
                "[P] replay again   [R] regenerate   "
                "[S] toggle Y scales   [SPACE] freeze animation   [ESC] exit",
                18,
                Muted);

            // All three charts are drawn in the same frame, every frame.
            constexpr float margin = 24.0f;
            constexpr float gap = 16.0f;
            constexpr float width =
                (CanvasWidth - margin * 2 - gap * 2) / 3.0f;

            for (int index = 0; index < 3; ++index)
            {
                DrawPanel(
                    experiment,
                    replay,
                    index,
                    {margin + index * (width + gap), 140, width, 663},
                    commonMaximum,
                    commonScale,
                    animationAge,
                    time);
            }

            Text(
                26, 817,
                std::string("LINEAR Y AXES: ") +
                (commonScale ? "COMMON SCALE"
                             : "INDEPENDENT SCALES - check count labels") +
                "   |   Dashed line = uniform expectation: 100 per bin",
                17,
                Muted);

            Text(
                26, 844,
                "Replay round " + std::to_string(replay.round) +
                "   |   Known cryptographic seed also replays: " +
                (replay.knownCryptoSeedReplays ? "YES" : "NO") +
                "   |   Secure OS state is not our public seed.",
                17,
                TextColor);

            Text(
                26, 871,
                "A histogram or a differing second draw cannot prove security. "
                "Security depends on the generator, entropy, and protected state.",
                16,
                Muted);

            EndTextureMode();

            // Letterbox the canvas so nothing is cropped or stretched.
            const float screenWidth =
                static_cast<float>(GetScreenWidth());

            const float screenHeight =
                static_cast<float>(GetScreenHeight());

            const float scale =
                std::min(
                    screenWidth / CanvasWidth,
                    screenHeight / CanvasHeight);

            const Rectangle destination{
                (screenWidth - CanvasWidth * scale) * 0.5f,
                (screenHeight - CanvasHeight * scale) * 0.5f,
                CanvasWidth * scale,
                CanvasHeight * scale
            };

            BeginDrawing();
            ClearBackground(BLACK);

            // Render textures have inverted vertical texture coordinates.
            DrawTexturePro(
                canvas.texture,
                {0, 0, static_cast<float>(CanvasWidth),
                 -static_cast<float>(CanvasHeight)},
                destination,
                {0, 0},
                0,
                WHITE);

            EndDrawing();
        }

        UnloadRenderTexture(canvas);
        CloseWindow();
    }
}

// ============================================================================
// PROGRAM ENTRY POINT
// ============================================================================

int main()
{
    // Initialize the cryptographic library before requesting secure randomness.
    // Never silently substitute a weak generator if initialization fails.
    if (sodium_init() < 0)
    {
        std::cerr << "Secure random initialization failed. Aborting.\n";
        return 1;
    }

    demo::Experiment experiment{};
    demo::GenerateExperiment(experiment);
    demo::ShowVisualization(experiment);

    return 0;
}