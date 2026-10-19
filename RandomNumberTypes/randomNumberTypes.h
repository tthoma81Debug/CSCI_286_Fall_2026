#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace demo
{
    // All three generators use exactly the same sample count and output range.
    inline constexpr std::size_t SampleCount = 10000;
    inline constexpr int ValueCount = 100;       // Values: 0 through 99.
    inline constexpr std::size_t PreviewCount = 8;

    // These are ordinary, fixed-size, one-dimensional arrays.
    using Samples = std::array<int, SampleCount>;
    using Histogram = std::array<int, ValueCount>;
    using ClockSeeds = std::array<std::uint32_t, SampleCount>;
    using Preview = std::array<int, PreviewCount>;

    struct SampleSet
    {
        Samples values{};
        Histogram histogram{};

        // Useful descriptive statistics, not security tests.
        int occupiedBins = 0;
        int longestRun = 0;
    };

    struct Experiment
    {
        // Each element owns a separate one-dimensional values array:
        // sets[0].values, sets[1].values, and sets[2].values.
        std::array<SampleSet, 3> sets{};

        // The bad generator reseeds on EVERY iteration.
        // Therefore exact replay of that loop requires its seed schedule,
        // not just the timestamp at the start of the loop.
        ClockSeeds simpleSeeds{};

        // Deliberately public and fixed, making classroom replay easy.
        std::uint32_t mtSeed = 5489u;
    };

    struct ReplayResult
    {
        std::array<Preview, 3> preview{};
        std::array<int, 3> matches{};

        int round = 0;

        // An additional experiment proves that a cryptographic generator
        // ALSO replays if we deliberately disclose and reuse its seed.
        bool knownCryptoSeedReplays = false;
    };

    // ---------------- TEACHING / GENERATION FUNCTIONS ----------------

    std::uint32_t MillisecondSeed();
    int SimpleFromSeed(std::uint32_t seed);

    void GenerateSimple(SampleSet& output, ClockSeeds& usedSeeds);
    void GenerateStatistical(SampleSet& output, std::uint32_t seed);
    void GenerateSecure(SampleSet& output);

    void Analyze(SampleSet& data);
    void GenerateExperiment(Experiment& experiment);
    void RepeatReplayExperiment(
        const Experiment& experiment,
        ReplayResult& result
    );

    // ---------------- VISUALIZATION ENTRY POINT ----------------
    // No raylib types appear in this header.
    // The class can ignore its implementation while studying generation.
    void ShowVisualization(Experiment& experiment);
}