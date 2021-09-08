#ifndef INCG_PHI_CORE_TYPE_TRAITS_DISABLE_IF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DISABLE_IF_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool Boolean, typename TypeT = void>
struct disable_if
{
    using type = TypeT;
};

template <typename TypeT>
struct disable_if<true, TypeT>
{};

template <bool Boolean, typename TypeT = void>
using disable_if_t = typename disable_if<Boolean, TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DISABLE_IF_HPP
