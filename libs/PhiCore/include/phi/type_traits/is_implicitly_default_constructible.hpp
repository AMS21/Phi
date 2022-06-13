#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_default_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    void test_implicit_default_constructible(TypeT);
}

template <typename TypeT, class = void, typename = typename is_default_constructible<TypeT>::type>
struct is_implicitly_default_constructible : public false_type
{};

template <typename TypeT>
struct is_implicitly_default_constructible<
        TypeT, decltype(detail::test_implicit_default_constructible<TypeT const&>({})), true_type>
    : public true_type
{};

template <typename TypeT>
struct is_implicitly_default_constructible<
        TypeT, decltype(detail::test_implicit_default_constructible<TypeT const&>({})), false_type>
    : public false_type
{};

template <typename TypeT>
struct is_not_implicitly_default_constructible
    : public bool_constant<!is_implicitly_default_constructible<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_implicitly_default_constructible_v =
        is_implicitly_default_constructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_implicitly_default_constructible_v =
        is_not_implicitly_default_constructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_HPP
