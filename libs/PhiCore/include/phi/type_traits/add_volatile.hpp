#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_VOLATILE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_VOLATILE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct add_volatile
{
    using type = volatile TypeT;
};

template <typename TypeT>
using add_volatile_t = typename add_volatile<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_VOLATILE_HPP
