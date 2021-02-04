#ifndef INCG_PHI_CONFIG_WARNING_HPP
#define INCG_PHI_CONFIG_WARNING_HPP

#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Stringify.hpp"

// Suppress warnings
/* MSVC Warnings */
#if PHI_COMPILER_IS(MSVC)
#    define PHI_MSVC_SUPPRESS_WARNING_PUSH()          PHI_PRAGMA(warning(push))
#    define PHI_MSVC_SUPPRESS_WARNING(warning_number) PHI_PRAGMA(warning(disable : warning_number))
#    define PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(warning_number)                                    \
        PHI_MSVC_SUPPRESS_WARNING_PUSH() PHI_MSVC_SUPPRESS_WARNING(warning_number)
#    define PHI_MSVC_SUPPRESS_WARNING_POP() PHI_PRAGMA(warning(pop))
#else
#    define PHI_MSVC_SUPPRESS_WARNING_PUSH()             /* Nothing */
#    define PHI_MSVC_SUPPRESS_WARNING(warning)           /* Nothing */
#    define PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define PHI_MSVC_SUPPRESS_WARNING_POP()              /* Nothing */
#endif

/* Clang Warnings */
#if PHI_COMPILER_IS(CLANG)
#    define PHI_CLANG_SUPPRESS_WARNING_PUSH()   PHI_PRAGMA(clang diagnostic push)
#    define PHI_CLANG_SUPPRESS_WARNING(warning) PHI_PRAGMA(clang diagnostic ignored warning)
#    define PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH(warning)                                          \
        PHI_CLANG_SUPPRESS_WARNING_PUSH() PHI_CLANG_SUPPRESS_WARNING(warning)
#    define PHI_CLANG_SUPPRESS_WARNING_POP() PHI_PRAGMA(clang diagnostic push)
#else
#    define PHI_CLANG_SUPPRESS_WARNING_PUSH()             /* Nothing */
#    define PHI_CLANG_SUPPRESS_WARNING(warning)           /* Nothing */
#    define PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define PHI_CLANG_SUPPRESS_WARNING_POP()              /* Nothing */
#endif

/* GCC Warnings */
#if PHI_COMPILER_IS(GCC) && PHI_COMPILER_IS_NOT(CLANG)
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 7, 0)
#        define PHI_GCC_SUPPRESS_WARNING_PUSH() PHI_PRAGMA(GCC diagnostic push)
#        define PHI_GCC_SUPPRESS_WARNING_POP()  PHI_PRAGMA(GCC diagnostic pop)
#    else
#        define PHI_GCC_SUPPRESS_WARNING_PUSH() /* Nothing */
#        define PHI_GCC_SUPPRESS_WARNING_POP()  /* Nothing */
#    endif
#    define PHI_GCC_SUPPRESS_WARNING(warning) PHI_PRAGMA(GCC diagnostic ignored warning)
#    define PHI_GCC_SUPPRESS_WARNING_WITH_PUSH(warning)                                            \
        PHI_GCC_SUPPRESS_WARNING_PUSH() PHI_GCC_SUPPRESS_WARNING(warning)
#else
#    define PHI_GCC_SUPPRESS_WARNING_PUSH()             /* Nothing */
#    define PHI_GCC_SUPPRESS_WARNING(warning)           /* Nothing */
#    define PHI_GCC_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define PHI_GCC_SUPPRESS_WARNING_POP()              /* Nothing */
#endif

// Compiler warning
#if PHI_COMPILER_IS(MSVC)
#    define PHI_COMPILER_WARNING(msg)                                                              \
        PHI_PRAGMA(message(__FILE__ "(" PHI_STRINGIFY(__LINE__) ") : warning: " #msg))
#elif PHI_COMPILER_IS(CLANG)
#    define PHI_COMPILER_WARNING(msg)                                                              \
        PHI_PRAGMA(PHI_STRINGIFY(                                                                  \
                GCC warning(__FILE__ "(" PHI_STRINGIFY(__LINE__) ") : warning: " msg)))
#elif PHI_COMPILER_IS(GCC)
#    define PHI_COMPILER_WARNING(msg) PHI_PRAGMA(GCC warning msg)
#else
#    define PHI_COMPILER_WARNING(msg) /* Nothing */
#endif

#define PHI_UNUSED_PARAMETER(parameter) ((void)(parameter))

// External Warnings
#if PHI_COMPILER_IS(MSVC)
#    define PHI_EXTERNAL_HEADERS_BEGIN() PHI_PRAGMA(warning(push, 0))
#    define PHI_EXTERNAL_HEADERS_END()   PHI_MSVC_SUPPRESS_WARNING_POP()
#else
#    define PHI_EXTERNAL_HEADERS_BEGIN() /* Nothing */
#    define PHI_EXTERNAL_HEADERS_END()   /* Nothing */
#endif

#endif // INCG_PHI_CONFIG_WARNING_HPP
