#ifndef INCG_PHI_CORE_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TYPE_IDENTITY_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct type_identity
{
    using type = TypeT;
};

template <typename TypeT>
using type_identity_t = typename type_identity<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_TYPE_IDENTITY_HPP
