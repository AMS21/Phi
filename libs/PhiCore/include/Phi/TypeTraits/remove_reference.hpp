#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_REFERENCE_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_reference
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_reference<TypeT&>
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_reference<TypeT&&>
{
    using type = TypeT;
};

template <typename TypeT>
using remove_reference_t = typename remove_reference<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_REFERENCE_HPP
