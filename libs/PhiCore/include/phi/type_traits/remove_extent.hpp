#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_EXTEND_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_EXTEND_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/intrinsics/remove_extent.hpp"

#if PHI_SUPPORTS_REMOVE_EXTENT()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_extent
{
    using type = PHI_REMOVE_EXTENT(TypeT);
};

template <typename TypeT>
using remove_extent_t = PHI_REMOVE_EXTENT(TypeT);

#else

#    include "phi/core/size_t.hpp"

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

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_EXTEND_HPP
