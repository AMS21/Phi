#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/detail/intrinsics.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_TYPE_TRAITS_USE_INTRINSIC_IS_CONSTRUCTIBLE()

#    include "Phi/Config/Warning.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wignored-qualifiers")

template <typename TypeT>
struct is_default_constructible : public bool_constant<PHI_IS_CONSTRUCTIBLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_default_constructible_v = PHI_IS_CONSTRUCTIBLE(TypeT);

#    endif

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#else

#    include "Phi/Core/SizeT.hpp"
#    include "Phi/TypeTraits/detail/yes_no_type.hpp"
#    include "Phi/TypeTraits/is_abstract.hpp"
#    include "Phi/TypeTraits/is_complete.hpp"
#    include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    struct is_default_constructible_imp
    {
        template <typename TypeT, typename = decltype(TypeT())>
        static yes_type test(int);

        template <typename>
        static no_type test(...);
    };

    template <typename T, bool b>
    struct is_default_constructible_abstract_filter
    {
        static const bool value =
                sizeof(is_default_constructible_imp::test<T>(0)) == detail::sizeof_yes_type;
    };

    template <typename T>
    struct is_default_constructible_abstract_filter<T, true>
    {
        static const bool value = false;
    };
} // namespace detail

template <typename T>
struct is_default_constructible
    : public bool_constant<
              detail::is_default_constructible_abstract_filter<T, is_abstract<T>::value>::value>
{
    static_assert(is_complete<T>::value,
                  "Arguments to is_default_constructible must be complete types");
};

template <typename T, size_t N>
struct is_default_constructible<T[N]> : public is_default_constructible<T>
{};

template <typename T>
struct is_default_constructible<T[]> : public is_default_constructible<T>
{};

template <typename T>
struct is_default_constructible<T&> : public false_type
{};

template <typename T, typename U>
struct is_default_constructible<std::pair<T, U>>
    : public integral_constant<bool, is_default_constructible<T>::value &&
                                             is_default_constructible<U>::value>
{};

template <typename T>
struct is_default_constructible<T&&> : public false_type
{};

template <>
struct is_default_constructible<void> : public false_type
{};

template <>
struct is_default_constructible<void const> : public false_type
{};

template <>
struct is_default_constructible<void volatile> : public false_type
{};

template <>
struct is_default_constructible<void const volatile> : public false_type
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_default_constructible_v =
        is_default_constructible<TypeT>::value;

#    endif

DETAIL_PHI_END_NAMESPACE()

#endif

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
