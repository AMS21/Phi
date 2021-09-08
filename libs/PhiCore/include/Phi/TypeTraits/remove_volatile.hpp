#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_VOLATILE_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_volatile
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_volatile<volatile TypeT>
{
    using type = TypeT;
};

template <typename TypeT>
using remove_volatile_t = typename remove_volatile<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_VOLATILE_HPP
