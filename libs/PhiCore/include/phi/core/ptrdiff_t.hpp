#ifndef INCG_PHI_CORE_PTRDIFF_T_HPP
#define INCG_PHI_CORE_PTRDIFF_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

using ptrdiff_t = decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_PTRDIFF_T_HPP
