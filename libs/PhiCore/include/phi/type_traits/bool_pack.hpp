#ifndef INCG_PHI_CORE_TYPE_TRAITS_BOOL_PACK_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_BOOL_PACK_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool...>
struct bool_pack
{};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_BOOL_PACK_HPP
