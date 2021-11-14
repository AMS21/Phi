#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_HAS_INTRINSIC_IS_ARRAY()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_array : public bool_constant<__is_array(TypeT)>
{};

template <typename TypeT>
struct is_not_array : public bool_constant<!__is_array(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_array_v = __is_array(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_array_v = !__is_array(TypeT);

#    endif

#else

#    include "Phi/Core/SizeT.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_array : public false_type
{};

template <typename TypeT>
struct is_array<TypeT[]> : public true_type
{};

template <typename TypeT, size_t Size>
struct is_array<TypeT[Size]> : public true_type
{};

template <typename TypeT>
struct is_not_array : public bool_constant<!is_array<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_array_v = is_array<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_array_v = is_not_array<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP
