#ifndef INCG_PHI_PHICONFIG_HPP
#define INCG_PHI_PHICONFIG_HPP

#include <cpp/Debug.hpp>
#include <cpp/Glue.hpp>
#include <cpp/Stringify.hpp>
#include <cpp/Versioning.hpp>
#include <cstdint>

#define PHI_VERSION_MAJOR() 0
#define PHI_VERSION_MINOR() 1
#define PHI_VERSION_PATCH() 0

#define PHI_VERSION()                                                                              \
    CPP_VERSION_CREATE(PHI_VERSION_MAJOR(), PHI_VERSION_MINOR(), PHI_VERSION_PATCH())

#define PHI_VERSION_MAJOR_STR() CPP_STRINGIFY(PHI_VERSION_MAJOR())
#define PHI_VERSION_MINOR_STR() CPP_STRINGIFY(PHI_VERSION_MINOR())
#define PHI_VERSION_PATCH_STR() CPP_STRINGIFY(PHI_VERSION_PATCH())

#define PHI_VERSION_STR()                                                                          \
    PHI_VERSION_MAJOR_STR() "." PHI_VERSION_MINOR_STR() "." PHI_VERSION_PATCH_STR()

/// \cond detail
#define DETAIL_PHI_BEGIN_NAMESPACE()                                                               \
    namespace phi                                                                                  \
    {                                                                                              \
        inline namespace CPP_GLUE6(version_, PHI_VERSION_MAJOR(), _, PHI_VERSION_MINOR(), _,       \
                                   PHI_VERSION_PATCH())                                            \
        {
// clang-format off
#define DETAIL_PHI_END_NAMESPACE() } }
// clang-format on
/// \endcond

#if defined(CPP_DEBUG)
#    define PHI_DEBUG
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
