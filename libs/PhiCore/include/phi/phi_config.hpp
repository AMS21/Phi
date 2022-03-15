#ifndef INCG_PHI_PHICONFIG_HPP
#define INCG_PHI_PHICONFIG_HPP

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/platform.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/preprocessor/glue.hpp"
#include "phi/preprocessor/stringify.hpp"
#include "phi/preprocessor/versioning.hpp"

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
    {

// clang-format off
#define DETAIL_PHI_END_NAMESPACE() }
// clang-format on
/// \endcond

#if PHI_COMPILER_IS(EMCC)
#    define DETAIL_PHI_BEGIN_STD_NAMESPACE()                                                       \
        namespace std                                                                              \
        {                                                                                          \
            inline namespace __2                                                                   \
            {

// clang-format off
#    define DETAIL_PHI_END_STD_NAMESPACE() } }
// clang-format on
#else
#    define DETAIL_PHI_BEGIN_STD_NAMESPACE()                                                       \
        namespace std                                                                              \
        {

#    define DETAIL_PHI_END_STD_NAMESPACE() }
#endif

#if !defined(PHI_DEBUG) && (!defined(NDEBUG) || defined(_DEBUG))
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

#endif // INCG_PHI_PHICONFIG_HPP
