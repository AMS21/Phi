#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_ARRAY()

template <typename TypeT>
struct is_array : public bool_constant<__is_array(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_array_v = __is_array(TypeT);

#    endif

#else

template <typename TypeT>
struct is_array : public false_type
{};

template <typename TypeT>
struct is_array<TypeT[]> : public true_type
{};

template <typename TypeT, size_t Size>
struct is_array<TypeT[Size]> : public true_type
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_array_v = is_array<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP
