#ifndef INCG_PHI_CORE_WINT_T_HPP
#define INCG_PHI_CORE_WINT_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

// GCC and Clang provide the '__WINT_TYPE__' macro which is the exakt type we need
#if defined(__WINT_TYPE__)

using wint_t = __WINT_TYPE__;

#else

// Otherwise fallback to using 'unsigned int' same as libc
// https://github.com/bminor/glibc/blob/master/wcsmbs/bits/types/wint_t.h#L17
using wint_t = unsigned int;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_WINT_T_HPP
