#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_nothrow_constructible.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_NOTHROW_CONSTRUCTIBLE()

#    define PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE() 1

#    include "phi/compiler_support/warning.hpp"

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wignored-qualifiers")

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename... ArgsT>
struct is_nothrow_constructible
    : public bool_constant<PHI_IS_NOTHROW_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

template <typename TypeT, typename... ArgsT>
struct is_not_nothrow_constructible
    : public bool_constant<!PHI_IS_NOTHROW_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_constructible_v =
        PHI_IS_NOTHROW_CONSTRUCTIBLE(TypeT, ArgsT...);

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_not_nothrow_constructible_v =
        !PHI_IS_NOTHROW_CONSTRUCTIBLE(TypeT, ArgsT...);

#    endif

PHI_GCC_SUPPRESS_WARNING_POP()

#else

#    include "phi/compiler_support/warning.hpp"
#    include "phi/core/declval.hpp"
#    include "phi/core/size_t.hpp"
#    include "phi/type_traits/is_constructible.hpp"
#    include "phi/type_traits/is_reference.hpp"
#    include "phi/type_traits/remove_all_extents.hpp"

#    if PHI_HAS_WORKING_IS_CONSTRUCTIBLE()
#        define PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE() 1
#    else
#        define PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE() 0
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wdouble-promotion")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4197) // 'x': top-level volatile in cast is ignored

namespace detail
{
    template <bool, bool, typename TypeT, typename... ArgsT>
    struct is_nothrow_constructible_impl;

    template <typename TypeT, typename... ArgsT>
    struct is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ false, TypeT,
                                         ArgsT...>
        : public bool_constant<noexcept(TypeT(declval<ArgsT>()...))>
    {};

    template <typename TypeT, size_t Dimension>
    struct is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ false,
                                         TypeT[Dimension]>
        : public bool_constant<noexcept(typename remove_all_extents<TypeT>::type())>
    {};

    template <typename TypeT, size_t Dimension, typename ArgT>
    struct is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ false,
                                         TypeT[Dimension], ArgT>
        : public is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ false,
                                               TypeT, ArgT>
    {};

    template <typename TypeT, size_t Dimension, typename... ArgsT>
    struct is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ false,
                                         TypeT[Dimension], ArgsT...>
        : public is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ false,
                                               TypeT, ArgsT...>
    {};

    template <typename TypeT>
    void implicit_conversion_to(TypeT) noexcept
    {}

    template <typename TypeT, typename ArgT>
    struct is_nothrow_constructible_impl</*is constructible*/ true, /*is reference*/ true, TypeT,
                                         ArgT>
        : public bool_constant<noexcept(implicit_conversion_to<TypeT>(declval<ArgT>()))>
    {};

    template <typename TypeT, bool IsReference, typename... ArgsT>
    struct is_nothrow_constructible_impl</*is constructible*/ false, IsReference, TypeT, ArgsT...>
        : public false_type
    {};
} // namespace detail

template <typename TypeT, typename... ArgsT>
struct is_nothrow_constructible
    : public detail::is_nothrow_constructible_impl<is_constructible<TypeT, ArgsT...>::value,
                                                   is_reference<TypeT>::value, TypeT, ArgsT...>
{};

template <typename TypeT, size_t Dimension>
struct is_nothrow_constructible<TypeT[Dimension]>
    : public detail::is_nothrow_constructible_impl<is_constructible<TypeT>::value,
                                                   is_reference<TypeT>::value, TypeT>
{};

template <typename TypeT, typename... ArgsT>
struct is_not_nothrow_constructible
    : public bool_constant<!is_nothrow_constructible<TypeT, ArgsT...>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_constructible_v =
        is_nothrow_constructible<TypeT, ArgsT...>::value;

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_not_nothrow_constructible_v =
        is_not_nothrow_constructible<TypeT, ArgsT...>::value;

#    endif

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_CONSTRUCTIBLE_HPP
