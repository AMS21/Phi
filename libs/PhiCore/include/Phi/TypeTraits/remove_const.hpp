#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CONST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CONST_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_const
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_const<const TypeT>
{
    using type = TypeT;
};

template <typename TypeT>
using remove_const_t = typename remove_const<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CONST_HPP
