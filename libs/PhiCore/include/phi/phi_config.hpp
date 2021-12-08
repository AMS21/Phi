#ifndef INCG_PHI_PHICONFIG_HPP
#define INCG_PHI_PHICONFIG_HPP

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/features.hpp"
#include "phi/compiler_support/platform.hpp"
#include "phi/preprocessor/glue.hpp"
#include "phi/preprocessor/stringify.hpp"
#include "phi/preprocessor/versioning.hpp"
#include <cstdint>

#define PHI_VERSION_MAJOR() 0
#define PHI_VERSION_MINOR() 1
#define PHI_VERSION_PATCH() 0

#define PHI_VERSION()                                                                              \
    PHI_VERSION_CREATE(PHI_VERSION_MAJOR(), PHI_VERSION_MINOR(), PHI_VERSION_PATCH())

#define PHI_VERSION_MAJOR_STR() PHI_STRINGIFY(PHI_VERSION_MAJOR())
#define PHI_VERSION_MINOR_STR() PHI_STRINGIFY(PHI_VERSION_MINOR())
#define PHI_VERSION_PATCH_STR() PHI_STRINGIFY(PHI_VERSION_PATCH())

#define PHI_VERSION_STR()                                                                          \
    PHI_VERSION_MAJOR_STR() "." PHI_VERSION_MINOR_STR() "." PHI_VERSION_PATCH_STR()

/// \cond detail
#define DETAIL_PHI_BEGIN_NAMESPACE()                                                               \
    namespace phi                                                                                  \
    {                                                                                              \
        inline namespace PHI_GLUE6(v_, PHI_VERSION_MAJOR(), _, PHI_VERSION_MINOR(), _,             \
                                   PHI_VERSION_PATCH())                                            \
        {
// clang-format off
#define DETAIL_PHI_END_NAMESPACE() } }
// clang-format on
/// \endcond

#if !defined(NDEBUG) || defined(_DEBUG)
#    define PHI_DEBUG
#endif

// No min max on Windows
#if PHI_PLATFORM_IS(WINDOWS)
#    ifndef NOMINMAX
#        define NOMINMAX
#    endif
#endif

// Import/Export
#if PHI_PLATFORM_IS(WINDOWS)
#    define PHI_API_EXPORT __declspec(dllexport)
#    define PHI_API_IMPORT __declspec(dllimport)
#elif PHI_COMPILER_IS_ATLEAST(GCC, 4, 0, 0) || PHI_COMPILER_IS(CLANG)
#    define PHI_API_EXPORT __attribute__((__visibility__("default")))
#    define PHI_API_IMPORT __attribute__((__visibility__("default")))
#else
#    define PHI_API_EXPORT
#    define PHI_API_IMPORT
#endif

// Define PHI_API macro
#if !defined(PHI_STATIC_BUILD)
#    if defined(PHI_IMPORT)
#        define PHI_API PHI_API_IMPORT
#    else
#        define PHI_API PHI_API_EXPORT
#    endif
#else
#    define PHI_API
#endif

// Logging
#ifndef PHI_CONFIG_NO_LOG
#    define PHI_CONFIG_ENABLE_LOGGING
#    define PHI_CONFIG_ENABLE_INTERNAL_LOGGING
#    define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
#    define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

constexpr const static std::uint32_t VersionMajor{PHI_VERSION_MAJOR()};
constexpr const static std::uint32_t VersionMinor{PHI_VERSION_MINOR()};
constexpr const static std::uint32_t VersionPatch{PHI_VERSION_PATCH()};
constexpr const static std::uint32_t Version{PHI_VERSION()}; // NOLINT(hicpp-signed-bitwise)
constexpr const static char          VersionString[]{PHI_VERSION_STR()};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_PHICONFIG_HPP
