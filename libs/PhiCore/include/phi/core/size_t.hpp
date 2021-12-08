#ifndef INCG_PHI_CORE_SIZE_T_HPP
#define INCG_PHI_CORE_SIZE_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

using size_t = decltype(sizeof(int));

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SIZE_T_HPP
