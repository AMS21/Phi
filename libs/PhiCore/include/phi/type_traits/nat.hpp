#ifndef INCG_PHI_CORE_TYPE_TRAITS_NAT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_NAT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

struct nat
{
    nat()           = delete;
    nat(const nat&) = delete;
    nat& operator=(const nat&) = delete;
    ~nat()                     = delete;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_NAT_HPP
