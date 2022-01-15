#ifndef INCG_PHI_CORE_TYPE_TRAITS_RANK_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_RANK_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/array_rank.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_ARRAY_RANK()

template <typename TypeT>
struct rank : public integral_constant<size_t, PHI_ARRAY_RANK(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr size_t rank_v = PHI_ARRAY_RANK(TypeT);

#    endif

#else

template <typename TypeT>
struct rank : public integral_constant<size_t, 0u>
{};

template <typename TypeT>
struct rank<TypeT[]> : public integral_constant<size_t, rank<TypeT>::value + 1>
{};

template <typename TypeT, size_t Dimension>
struct rank<TypeT[Dimension]> : public integral_constant<size_t, rank<TypeT>::value + 1>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr size_t rank_v = rank<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_RANK_HPP
