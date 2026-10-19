#include <chrono>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>

// Operating-system headers for the secure example.
// No third-party libraries are required.
#if defined(_WIN32)
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    #include <windows.h>
    #include <bcrypt.h>

    // Automatically link the built-in Windows library when using MSVC.
    #ifdef _MSC_VER
        #pragma comment(lib, "bcrypt.lib")
    #endif

#elif defined(__linux__)
    #include <cerrno>
    #include <sys/random.h>

#elif defined(__APPLE__)
    #include <cstdlib>

#else
    #error "Add your operating system's secure random API here."
#endif

// Implementations are at the bottom so the classroom examples stay together.
std::uint32_t SecureRandomWord();
int SecureRandom0To99();

int main()
{
    try
    {
        constexpr int Count = 10000;

        // Three separate, ordinary, one-dimensional arrays.
        int simpleNumbers[Count]{};
        int statisticalNumbers[Count]{};
        int secureNumbers[Count]{};

        // ================================================================
        // 1. SIMPLE / DELIBERATELY BAD
        //    Reseed from the current millisecond on EVERY iteration.
        // ================================================================

        for (int i = 0; i < Count; ++i)
        {
            const auto milliseconds =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                ).count();

            // BAD: many iterations receive exactly the same clock seed.
            std::uint32_t state =
                static_cast<std::uint32_t>(milliseconds);

            // One step of a simple linear congruential generator.
            // Storing in uint32_t keeps the low 32 bits.
            state = state * 1664525u + 1013904223u;

            // Produce a value from 0 through 99.
            // This modulo mapping also adds a small bias.
            simpleNumbers[i] = static_cast<int>((state >> 16u) % 100u);
        }

        // Repeated seeds produce repeated values.
        // The exact pattern depends on how quickly this machine runs.
        // A clock timestamp is not a suitable security seed.


        // ================================================================
        // 2. STATISTICALLY USEFUL / NOT FOR SECURITY
        //    Seed the generator ONCE, then keep drawing from it.
        // ================================================================

        const std::uint32_t seed = 12345u;

        std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(0, 99);

        for (int i = 0; i < Count; ++i)
        {
            statisticalNumbers[i] = distribution(generator);
        }

        // Same seed gives the same sequence in the same implementation.
        // Useful for reproducible simulations and classroom demonstrations.
        // NOT suitable for passwords, keys, or security tokens.


        // ================================================================
        // 3. SECURE / OPERATING-SYSTEM RANDOMNESS
        //    No application-supplied public clock seed.
        // ================================================================

        for (int i = 0; i < Count; ++i)
        {
            secureNumbers[i] = SecureRandom0To99();
        }

        // The helper obtains randomness from the OS cryptographic RNG.
        // The OS manages its entropy sources and protected generator state.
        //
        // These small 0..99 values are for demonstration only:
        // one such value is obviously much too small to be a secret key.


        // ================================================================
        // OUTPUT: Show a small sample rather than printing 30,000 numbers.
        // All 10,000 values remain stored in each array.
        // ================================================================

        std::cout << "First 20 values from each array\n\n";
        std::cout << "Index\tSimple\tStatistical\tSecure\n";

        for (int i = 0; i < 20; ++i)
        {
            std::cout
                << i << '\t'
                << simpleNumbers[i] << '\t'
                << statisticalNumbers[i] << "\t\t"
                << secureNumbers[i] << '\n';
        }

        std::cout << "\nEach array contains " << Count << " values.\n";
    }
    catch (const std::exception& error)
    {
        // Never silently fall back to an insecure generator.
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}


// ============================================================================
// SECURE RANDOM HELPER
//
// These platform details can be left out of the initial live demonstration.
// ============================================================================

std::uint32_t SecureRandomWord()
{
    std::uint32_t value = 0;

#if defined(_WIN32)

    // Windows: ask the system-preferred cryptographic RNG.
    const NTSTATUS status = BCryptGenRandom(
        nullptr,
        reinterpret_cast<PUCHAR>(&value),
        static_cast<ULONG>(sizeof(value)),
        BCRYPT_USE_SYSTEM_PREFERRED_RNG
    );

    if (status < 0)
        throw std::runtime_error("Windows secure RNG failed.");

#elif defined(__linux__)

    // Linux: getrandom() uses the kernel's secure random facility.
    // Flags = 0 lets it wait until the random source is initialized.
    //
    // Handle interruptions and partial reads rather than assuming success.
    auto* destination = reinterpret_cast<unsigned char*>(&value);
    std::size_t received = 0;

    while (received < sizeof(value))
    {
        const auto result = getrandom(
            destination + received,
            sizeof(value) - received,
            0
        );

        if (result < 0)
        {
            if (errno == EINTR)
                continue;

            throw std::runtime_error("Linux secure RNG failed.");
        }

        if (result == 0)
            throw std::runtime_error("Linux secure RNG returned no data.");

        received += static_cast<std::size_t>(result);
    }

#elif defined(__APPLE__)

    // macOS: use the system-provided cryptographic random facility.
    arc4random_buf(&value, sizeof(value));

#endif

    // The OS gathers entropy and uses it to maintain a secure RNG.
    // Exact underlying entropy sources depend on the OS and hardware.
    // We are NOT measuring a new physical noise event for every call.
    return value;
}

int SecureRandom0To99()
{
    // A 32-bit word has 2^32 possible values.
    // That count is not divisible by 100.
    //
    // Simply using SecureRandomWord() % 100 would therefore introduce bias.
    // Reject a small upper tail so the accepted range contains exactly
    // the same number of representatives for every remainder 0..99.

    constexpr std::uint32_t maximum =
        std::numeric_limits<std::uint32_t>::max();

    constexpr std::uint32_t limit =
        maximum - (maximum % 100u);

    std::uint32_t value;

    do
    {
        value = SecureRandomWord();
    }
    while (value >= limit);

    return static_cast<int>(value % 100u);
}