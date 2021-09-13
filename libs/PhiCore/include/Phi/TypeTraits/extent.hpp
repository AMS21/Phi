#ifndef INCG_PHI_CORE_TYPE_TRAITS_EXTENT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_EXTENT_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include <cstdint>

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_ARRAY_EXTENT()

template <typename TypeT, unsigned Dimension = 0u>
struct extent : public integral_constant<std::size_t, __array_extent(TypeT, Dimension)>
{};

template <typename TypeT, unsigned Dimension = 0u>
PHI_INLINE_VARIABLE constexpr std::size_t extent_v = __array_extent(TypeT, Dimension);

#else

template <typename TypeT, unsigned Dimension = 0u>
struct extent : integral_constant<std::size_t, 0u>
{};

template <typename TypeT>
struct extent<TypeT[], 0u> : integral_constant<std::size_t, 0u>
{};

template <typename TypeT, unsigned Dimension>
struct extent<TypeT[], Dimension> : extent<TypeT, Dimension - 1u>
{};

template <typename TypeT, std::size_t Dimension>
struct extent<TypeT[Dimension], 0u> : integral_constant<std::size_t, Dimension>
{};

template <typename TypeT, std::size_t I, unsigned N>
struct extent<TypeT[I], N> : extent<TypeT, N - 1u>
{};

template <typename TypeT, unsigned Dimension = 0u>
PHI_INLINE_VARIABLE constexpr std::size_t extent_v = extent<TypeT, Dimension>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_EXTENT_HPP
