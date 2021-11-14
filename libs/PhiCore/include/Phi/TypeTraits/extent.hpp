#ifndef INCG_PHI_CORE_TYPE_TRAITS_EXTENT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_EXTENT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/ArrayExtent.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_ARRAY_EXTENT()

template <typename TypeT, unsigned Dimension = 0u>
struct extent : public integral_constant<size_t, PHI_ARRAY_EXTENT(TypeT, Dimension)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, unsigned Dimension = 0u>
PHI_INLINE_VARIABLE constexpr size_t extent_v = PHI_ARRAY_EXTENT(TypeT, Dimension);

#    endif

#else

template <typename TypeT, unsigned Dimension = 0u>
struct extent : integral_constant<size_t, 0u>
{};

template <typename TypeT>
struct extent<TypeT[], 0u> : integral_constant<size_t, 0u>
{};

template <typename TypeT, unsigned Dimension>
struct extent<TypeT[], Dimension> : extent<TypeT, Dimension - 1u>
{};

template <typename TypeT, size_t Dimension>
struct extent<TypeT[Dimension], 0u> : integral_constant<size_t, Dimension>
{};

template <typename TypeT, size_t I, unsigned N>
struct extent<TypeT[I], N> : extent<TypeT, N - 1u>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT, unsigned Dimension = 0u>
PHI_INLINE_VARIABLE constexpr size_t extent_v = extent<TypeT, Dimension>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_EXTENT_HPP
