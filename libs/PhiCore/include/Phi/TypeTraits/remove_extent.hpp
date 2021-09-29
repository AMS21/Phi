#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_EXTEND_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_EXTEND_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Core/SizeT.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_extent
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_extent<TypeT[]>
{
    using type = TypeT;
};

template <typename TypeT, size_t Size>
struct remove_extent<TypeT[Size]>
{
    using type = TypeT;
};

template <typename TypeT>
using remove_extent_t = typename remove_extent<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_EXTEND_HPP
