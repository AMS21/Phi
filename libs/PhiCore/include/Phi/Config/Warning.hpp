#ifndef INCG_PHI_CONFIG_WARNING_HPP
#define INCG_PHI_CONFIG_WARNING_HPP

#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Stringify.hpp"

// Suppress warnings
/* MSVC Warnings */
#if PHI_COMPILER_IS(MSVC)
#    define PHI_MSVC_SUPPRESS_WARNING_PUSH()          __pragma(warning(push))
#    define PHI_MSVC_SUPPRESS_WARNING(warning_number) __pragma(warning(disable : warning_number))
#    define PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(warning_number)                                    \
        PHI_MSVC_SUPPRESS_WARNING_PUSH() PHI_MSVC_SUPPRESS_WARNING(warning_number)
#    define PHI_MSVC_SUPPRESS_WARNING_POP() __pragma(warning(pop))
#    define PHI_COMPILER_WARNING(msg)                                                              \
        __pragma(message(__FILE__ "(" PHI_STRINGIFY(__LINE__) ") : warning: " #msg))
#else
#    define PHI_MSVC_SUPPRESS_WARNING_PUSH()             /* Nothing */
#    define PHI_MSVC_SUPPRESS_WARNING(warning)           /* Nothing */
#    define PHI_MSVC_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define PHI_MSVC_SUPPRESS_WARNING_POP()              /* Nothing */
#endif

/* Clang Warnings */
#if PHI_COMPILER_IS(CLANG)
#    define DETAIL_PHI_PRAGMA_TO_STR(string)  _Pragma(#    string)
#    define PHI_CLANG_SUPPRESS_WARNING_PUSH() _Pragma("clang diagnostic push")
#    define PHI_CLANG_SUPPRESS_WARNING(warning)                                                    \
        DETAIL_PHI_PRAGMA_TO_STR(clang diagnostic ignored warning)
#    define PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH(warning)                                          \
        PHI_CLANG_SUPPRESS_WARNING_PUSH() PHI_CLANG_SUPPRESS_WARNING(warning)
#    define PHI_CLANG_SUPPRESS_WARNING_POP() _Pragma("clang diagnostic push")
#    define PHI_COMPILER_WARNING(msg)                                                              \
        _Pragma(PHI_STRINGIFY(                                                                     \
                GCC warning(__FILE__ "(" PHI_STRINGIFY(__LINE__) ") : warning: " msg)))
#else
#    define PHI_CLANG_SUPPRESS_WARNING_PUSH()             /* Nothing */
#    define PHI_CLANG_SUPPRESS_WARNING(warning)           /* Nothing */
#    define PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define PHI_CLANG_SUPPRESS_WARNING_POP()              /* Nothing */
#endif

/* GCC Warnings */
#if PHI_COMPILER_IS(GCC)
#    define DETAIL_PHI_PRAGMA_TO_STR(string) _Pragma(#    string)
#    if PHI_COMPILER_VERSION_IS_ATLEAST(4, 7, 0)
#        define PHI_GCC_SUPPRESS_WARNING_PUSH() _Pragma("GCC diagnostic push")
#        define PHI_GCC_SUPPRESS_WARNING_POP()  _Pragma("GCC diagnostic pop")
#    else
#        define PHI_GCC_SUPPRESS_WARNING_PUSH() /* Nothing */
#        define PHI_GCC_SUPPRESS_WARNING_POP()  /* Nothing */
#    endif
#    define PHI_GCC_SUPPRESS_WARNING(warning)                                                      \
        DETAIL_PHI_PRAGMA_TO_STR(GCC diagnostic ignored warning)
#    define PHI_GCC_SUPPRESS_WARNING_WITH_PUSH(warning)                                            \
        PHI_GCC_SUPPRESS_WARNING_PUSH() PHI_GCC_SUPPRESS_WARNING(warning)
#    define PHI_COMPILER_WARNING(msg) DETAIL_PHI_PRAGMA_TO_STR(GCC warning msg)
#else
#    define PHI_GCC_SUPPRESS_WARNING_PUSH()             /* Nothing */
#    define PHI_GCC_SUPPRESS_WARNING(warning)           /* Nothing */
#    define PHI_GCC_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define PHI_GCC_SUPPRESS_WARNING_POP()              /* Nothing */
#endif

#if !defined(PHI_COMPILER_WARNING)
#    define PHI_COMPILER_WARNING(msg) /* Nothing */
#endif

#define PHI_UNUSED_PARAMETER(parameter) ((void)(parameter))

// External Warnings
#if PHI_COMPILER_IS(MSVC)
#    define PHI_EXTERNAL_HEADERS_BEGIN() __pragma(warning(push, 1))
#    define PHI_EXTERNAL_HEADERS_END()   PHI_MSVC_SUPPRESS_WARNING_POP()
#else
#    define PHI_EXTERNAL_HEADERS_BEGIN() /* Nothing */
#    define PHI_EXTERNAL_HEADERS_END()   /* Nothing */
#endif

#endif // INCG_PHI_CONFIG_WARNING_HPP
