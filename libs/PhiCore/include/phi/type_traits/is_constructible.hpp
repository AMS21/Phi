#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_constructible.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()

#    define PHI_HAS_WORKING_IS_CONSTRUCTIBLE() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename... ArgsT>
struct is_constructible : public bool_constant<PHI_IS_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

template <typename TypeT, typename... ArgsT>
struct is_not_constructible : public bool_constant<!PHI_IS_CONSTRUCTIBLE(TypeT, ArgsT...)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_constructible_v = PHI_IS_CONSTRUCTIBLE(TypeT, ArgsT...);

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_not_constructible_v = !PHI_IS_CONSTRUCTIBLE(TypeT, ArgsT...);

#    endif

DETAIL_PHI_END_NAMESPACE()

#else

#    include "phi/core/declval.hpp"
#    include "phi/type_traits/detail/yes_no_type.hpp"
#    include "phi/type_traits/is_complete.hpp"
#    include "phi/type_traits/is_default_constructible.hpp"
#    include "phi/type_traits/is_destructible.hpp"
#    include "phi/type_traits/is_void.hpp"

#    if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
#        define PHI_HAS_WORKING_IS_CONSTRUCTIBLE() 1
#    else
#        define PHI_HAS_WORKING_IS_CONSTRUCTIBLE() 0
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    struct is_constructible_imp
    {
        template <typename TypeT, typename... ArgsT, typename = decltype(T(declval<ArgsT>()...))>

        static yes_type test(int);
        template <typename, typename...>

        static no_type test(...);

        template <typename TypeT, typename ArgT, typename = decltype(::new TypeT(declval<ArgT>()))>
        static yes_type test1(int);

        template <typename, typename>
        static no_type test1(...);

        template <typename TypeT>
        static yes_type ref_test(TypeT);

        template <typename TypeT>
        static no_type ref_test(...);
    };
} // namespace detail

template <typename TypeT, typename... ArgsT>
struct is_constructible
    : public bool_constant<sizeof(detail::is_constructible_imp::test<TypeT, ArgsT...>(0)) ==
                           detail::sizeof_yes_type>
{
    static_assert(is_complete<TypeT>::value || is_void<TypeT>::value,
                  "The target type must be complete in order to test for constructibility");
};

template <typename TypeT, typename ArgT>
struct is_constructible<TypeT, ArgT>
    : public bool_constant<is_destructible<TypeT>::value &&
                           sizeof(detail::is_constructible_imp::test1<TypeT, ArgT>(0)) ==
                                   detail::sizeof_yes_type>
{
    static_assert(is_complete<TypeT>::value || is_void<TypeT>::value,
                  "The target type must be complete in order to test for constructibility");
};

template <typename RefT, typename ArgT>
struct is_constructible<RefT&, ArgT>
    : public bool_constant<sizeof(detail::is_constructible_imp::ref_test<RefT&>(declval<ArgT>())) ==
                           detail::sizeof_yes_type>
{};

template <typename RefT, typename ArgT>
struct is_constructible<RefT&&, ArgT>
    : public bool_constant<sizeof(detail::is_constructible_imp::ref_test<RefT&&>(
                                   declval<ArgT>())) == detail::sizeof_yes_type>
{};

template <>
struct is_constructible<void> : public false_type
{};

template <>
struct is_constructible<void const> : public false_type
{};

template <>
struct is_constructible<void const volatile> : public false_type
{};

template <>
struct is_constructible<void volatile> : public false_type
{};

template <typename TypeT>
struct is_constructible<TypeT> : public is_default_constructible<TypeT>
{};

template <typename TypeT, typename... ArgsT>
struct is_not_constructible : public bool_constant<!is_constructible<TypeT, ArgsT...>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_constructible_v = is_constructible<TypeT, ArgsT...>::value;

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_not_constructible_v =
        is_not_constructible<TypeT, ArgsT...>::value;

#    endif

DETAIL_PHI_END_NAMESPACE()

#endif

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
