#ifndef INCG_PHI_CORE_TYPE_TRAITS_ENABLE_IF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ENABLE_IF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool booleanValue, typename TypeT = void>
struct enable_if
{};

template <typename TypeT>
struct enable_if<true, TypeT>
{
    using type = TypeT;
};

template <bool booleanValue, typename TypeT = void>
using enable_if_t = typename enable_if<booleanValue, TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ENABLE_IF_HPP
