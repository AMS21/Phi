#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_null_pointer.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_NULL_POINTER()

template <typename TypeT>
struct is_null_pointer : public integral_constant<bool, PHI_IS_NULL_POINTER(TypeT)>
{};

template <typename TypeT>
struct is_not_null_pointer : public integral_constant<bool, !PHI_IS_NULL_POINTER(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_null_pointer_v = PHI_IS_NULL_POINTER(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_null_pointer_v = !PHI_IS_NULL_POINTER(TypeT);

#    endif

#else

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
struct is_not_null_pointer : public integral_constant<bool, !is_null_pointer<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_null_pointer_v = is_null_pointer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_null_pointer_v = is_not_null_pointer<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_HPP
