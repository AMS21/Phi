#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsConstructible.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()

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

#    include "Phi/Core/Declval.hpp"
#    include "Phi/TypeTraits/detail/yes_no_type.hpp"
#    include "Phi/TypeTraits/is_complete.hpp"
#    include "Phi/TypeTraits/is_default_constructible.hpp"
#    include "Phi/TypeTraits/is_destructible.hpp"
#    include "Phi/TypeTraits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    struct is_constructible_imp
    {
        template <typename T, typename... TheArgs, typename = decltype(T(declval<TheArgs>()...))>

        static yes_type test(int);
        template <typename, typename...>

        static no_type test(...);

        template <typename T, typename Arg, typename = decltype(::new T(declval<Arg>()))>
        static yes_type test1(int);

        template <typename, typename>
        static no_type test1(...);

        template <typename T>
        static yes_type ref_test(T);

        template <typename T>
        static no_type ref_test(...);
    };
} // namespace detail

template <typename T, typename... ArgsT>
struct is_constructible
    : public bool_constant<sizeof(detail::is_constructible_imp::test<T, ArgsT...>(0)) ==
                           detail::sizeof_yes_type>
{
    static_assert(is_complete<T>::value || is_void<T>::value,
                  "The target type must be complete in order to test for constructibility");
};

template <typename T, typename ArgT>
struct is_constructible<T, ArgT>
    : public bool_constant<is_destructible<T>::value &&
                           sizeof(detail::is_constructible_imp::test1<T, ArgT>(0)) ==
                                   detail::sizeof_yes_type>
{
    static_assert(is_complete<T>::value || is_void<T>::value,
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

template <typename T, typename... ArgsT>
struct is_not_constructible<T> : public boolbool_constant<!is_constructible<TypeT, ArgsT...>::value>
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
