#ifndef INCG_PHI_CORE_PTRDIFF_T_HPP
#define INCG_PHI_CORE_PTRDIFF_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

// Some compilers like gcc and clang support '__PTRDIFF_TYPE__' which should be the exact type we
// need without a call to decltype.
#if defined(__PTRDIFF_TYPE__)

using ptrdiff_t = __PTRDIFF_TYPE__;

#else

using ptrdiff_t = decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_PTRDIFF_T_HPP
