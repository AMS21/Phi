#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP

#include "Phi/PhiConfig.hpp"

#include <cstdint>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_all_extents
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_all_extents<TypeT[]>
{
    using type = typename remove_all_extents<TypeT>::type;
};

template <typename TypeT, std::size_t Size>
struct remove_all_extents<TypeT[Size]>
{
    using type = typename remove_all_extents<TypeT>::type;
};

template <typename TypeT>
using remove_all_extents_t = typename remove_all_extents<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
