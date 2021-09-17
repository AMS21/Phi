#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_null_pointer : public false_type
{};

template <>
struct is_null_pointer<decltype(nullptr)> : public true_type
{};

template <>
struct is_null_pointer<const decltype(nullptr)> : public true_type
{};

template <>
struct is_null_pointer<volatile decltype(nullptr)> : public true_type
{};

template <>
struct is_null_pointer<const volatile decltype(nullptr)> : public true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_null_pointer_v = is_null_pointer<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_HPP
