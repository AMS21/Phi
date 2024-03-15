#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_void : public false_type
{};

template <>
struct is_void<void> : public true_type
{};

template <>
struct is_void<const void> : public true_type
{};

template <>
struct is_void<volatile void> : public true_type
{};

template <>
struct is_void<const volatile void> : public true_type
{};

template <typename TypeT>
struct is_not_void : public bool_constant<!is_void<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_void_v = is_void<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_void_v = is_not_void<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
