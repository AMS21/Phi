#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_CONST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_CONST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct add_const
{
    using type = const TypeT;
};

template <typename TypeT>
using add_const_t = typename add_const<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_CONST_HPP
