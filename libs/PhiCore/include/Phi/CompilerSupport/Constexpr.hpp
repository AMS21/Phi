#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_HPP

#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/PhiConfig.hpp"

// Support for C++-11 constexpr
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2235.pdf
#if (PHI_COMPILER_IS_ATLEAST(GCC, 4, 6, 0) || PHI_COMPILER_IS_ATLEAST(CLANG_COMPAT, 3, 1, 0) ||    \
     PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0)) &&                                                   \
        PHI_CPP_STANDARD_IS_ATLEAST(11)
#    define DETAIL_PHI_CONSTEXPR_SUPPORT 1
#else
#    define DETAIL_PHI_CONSTEXPR_SUPPORT 0
#endif

#if DETAIL_PHI_CONSTEXPR_SUPPORT
#    define PHI_CONSTEXPR                 constexpr
#    define PHI_CONSTEXPR_OR_CONST        constexpr
#    define PHI_CONSTEXPR_OR_INLINE       constexpr
#    define PHI_CONSTEXPR_OR_STATIC       constexpr
#    define PHI_CONSTEXPR_OR(alternative) constexpr
#else
#    define PHI_CONSTEXPR                 /* Nothing */
#    define PHI_CONSTEXPR_OR_CONST        const
#    define PHI_CONSTEXPR_OR_INLINE       inline
#    define PHI_CONSTEXPR_OR_STATIC       static
#    define PHI_CONSTEXPR_OR(alternative) alternative
#endif

// Support for C++-14 extended constexpr
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3652.html
#if (PHI_COMPILER_IS_ATLEAST(GCC, 5, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG_COMPAT, 3, 4, 0) ||    \
     PHI_COMPILER_IS_ATLEAST(MSVC, 19, 10, 0)) &&                                                  \
        PHI_CPP_STANDARD_IS_ATLEAST(14)
#    define DETAIL_PHI_EXTENDED_CONSTEXPR_SUPPORT 1
#else
#    define DETAIL_PHI_EXTENDED_CONSTEXPR_SUPPORT 0
#endif

#if DETAIL_PHI_EXTENDED_CONSTEXPR_SUPPORT
#    define PHI_EXTENDED_CONSTEXPR                 constexpr
#    define PHI_EXTENDED_CONSTEXPR_OR_CONST        constexpr
#    define PHI_EXTENDED_CONSTEXPR_OR_INLINE       constexpr
#    define PHI_EXTENDED_CONSTEXPR_OR_STATIC       constexpr
#    define PHI_EXTENDED_CONSTEXPR_OR(alternative) constexpr
#else
#    define PHI_EXTENDED_CONSTEXPR                 /* Nothing */
#    define PHI_EXTENDED_CONSTEXPR_OR_CONST        const
#    define PHI_EXTENDED_CONSTEXPR_OR_INLINE       inline
#    define PHI_EXTENDED_CONSTEXPR_OR_STATIC       static
#    define PHI_EXTENDED_CONSTEXPR_OR(alternative) alternative
#endif

// constexpr and const
#if DETAIL_PHI_CONSTEXPR_SUPPORT
#    if DETAIL_PHI_EXTENDED_CONSTEXPR_SUPPORT
#        define PHI_CONSTEXPR_AND_CONST constexpr const
#    else
#        define PHI_CONSTEXPR_AND_CONST constexpr
#    endif
#else
#    define PHI_CONSTEXPR_AND_CONST const
#endif

// Constexpr lambda expression
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0170r1.pdf
#if (PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG_COMPAT, 5, 0, 0) ||    \
     PHI_COMPILER_IS_ATLEAST(MSVC, 19, 11, 0)) &&                                                  \
        PHI_CPP_STANDARD_IS_ATLEAST(17)
#    define PHI_CONSTEXPR_LAMBDA constexpr
#else
#    define PHI_CONSTEXPR_LAMBDA /* Nothing */
#endif

// Constexpr virtual functions
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1064r0.html
#if (PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG_COMPAT, 9, 0, 0) ||    \
     PHI_COMPILER_IS_ATLEAST(MSVC, 19, 28, 0)) &&                                                  \
        PHI_CPP_STANDARD_IS_ATLEAST(20)
#    define PHI_CONSTEXPR_VIRTUAL_FUNC constexpr
#else
#    define PHI_CONSTEXPR_VIRTUAL_FUNC /* Nothing */
#endif

// Undef macros
#undef DETAIL_PHI_CONSTEXPR_SUPPORT
#undef DETAIL_PHI_EXTENDED_CONSTEXPR_SUPPORT

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_HPP
