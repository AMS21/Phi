#ifndef INCG_PHI_CORE_TYPE_TRAITS_RANK_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_RANK_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include <cstdint>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct rank : public integral_constant<std::size_t, 0u>
{};

template <typename TypeT>
struct rank<TypeT[]> : public integral_constant<std::size_t, rank<TypeT>::value + 1>
{};

template <typename TypeT, std::size_t Dimension>
struct rank<TypeT[Dimension]> : public integral_constant<std::size_t, rank<TypeT>::value + 1>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr std::size_t rank_v = rank<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_RANK_HPP
