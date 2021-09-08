#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include <cstdint>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_array : public false_type
{};

template <typename TypeT>
struct is_array<TypeT[]> : public true_type
{};

template <typename TypeT, std::size_t Size>
struct is_array<TypeT[Size]> : public true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_array_v = is_array<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ARRAY_HPP
