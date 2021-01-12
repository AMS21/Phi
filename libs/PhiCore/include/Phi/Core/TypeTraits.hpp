#ifndef INCG_PHI_CORE_TYPETRAITS_HPP
#define INCG_PHI_CORE_TYPETRAITS_HPP

#include "Phi/PhiConfig.hpp"

#include <cstddef>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

// is_bounded_array
template <typename TypeT>
struct is_bounded_array : std::false_type
{};

template <typename TypeT, std::size_t SizeT>
struct is_bounded_array<TypeT[SizeT]> : std::true_type
{};

template <typename TypeT>
inline constexpr bool is_bounded_array_v = is_bounded_array<TypeT>::value;

// is_unbounded_array
template <typename TypeT>
struct is_unbounded_array : std::false_type
{};

template <typename TypeT>
struct is_unbounded_array<TypeT[]> : std::true_type
{};

template <typename TypeT>
inline constexpr bool is_unbounded_array_v = is_unbounded_array<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPETRAITS_HPP
