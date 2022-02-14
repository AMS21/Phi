#ifndef INCG_PHI_CORE_TYPE_TRAITS_DISABLE_IF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DISABLE_IF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool BooleanValue, typename TypeT = void>
struct disable_if
{
    using type = TypeT;
};

template <typename TypeT>
struct disable_if<true, TypeT>
{};

template <bool BooleanValue, typename TypeT = void>
using disable_if_t = typename disable_if<BooleanValue, TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DISABLE_IF_HPP
