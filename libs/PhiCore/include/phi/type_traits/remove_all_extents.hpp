#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/intrinsics/remove_all_extents.hpp"

#if PHI_SUPPORTS_REMOVE_ALL_EXTENTS()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_all_extents
{
    using type = PHI_REMOVE_ALL_EXTENTS(TypeT);
};

template <typename TypeT>
using remove_all_extents_t = PHI_REMOVE_ALL_EXTENTS(TypeT);

#else

#    include "phi/core/size_t.hpp"

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

template <typename TypeT, size_t Size>
struct remove_all_extents<TypeT[Size]>
{
    using type = typename remove_all_extents<TypeT>::type;
};

template <typename TypeT>
using remove_all_extents_t = typename remove_all_extents<TypeT>::type;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
