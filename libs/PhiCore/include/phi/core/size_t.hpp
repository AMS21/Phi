#ifndef INCG_PHI_CORE_SIZE_T_HPP
#define INCG_PHI_CORE_SIZE_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

// Some compilers like gcc and clang support '__SIZE_TYPE__' which should be the exact type we need
// without a call to decltype.
#if defined(__SIZE_TYPE__)

using size_t = __SIZE_TYPE__;

#else

using size_t = decltype(sizeof(int));

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SIZE_T_HPP
