#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_unbounded_array.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_UNBOUNDED_ARRAY()

template <typename TypeT>
struct is_unbounded_array : public integral_constant<bool, PHI_IS_UNBOUNDED_ARRAY(TypeT)>
{};

template <typename TypeT>
struct is_not_unbounded_array : public integral_constant<bool, !PHI_IS_UNBOUNDED_ARRAY(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_unbounded_array_v = PHI_IS_UNBOUNDED_ARRAY(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_unbounded_array_v = !PHI_IS_UNBOUNDED_ARRAY(TypeT);

#    endif

#else

template <typename TypeT>
struct is_unbounded_array : public false_type
{};

template <typename TypeT>
struct is_unbounded_array<TypeT[]> : public true_type
{};

template <typename TypeT>
struct is_not_unbounded_array : public integral_constant<bool, !is_unbounded_array<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_unbounded_array_v = is_unbounded_array<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_unbounded_array_v =
        is_not_unbounded_array<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
