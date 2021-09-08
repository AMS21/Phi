#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/add_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct add_rvalue_reference
{
    using type = TypeT&&;
};

template <typename TypeT>
struct add_rvalue_reference<TypeT&>
{
    using type = TypeT&&;
};

template <typename TypeT>
using add_rvalue_reference_t = typename add_rvalue_reference<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
