#ifndef INCG_PHI_CORE_WINT_T_HPP
#define INCG_PHI_CORE_WINT_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/platform.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// GCC and Clang provide the '__WINT_TYPE__' macro which is the exakt type we need
#if defined(__WINT_TYPE__)

using wint_t = __WINT_TYPE__;

// On Apple and Web platform 'wint_t' is 'int'
#elif PHI_PLATFORM_IS(APPLE) || PHI_PLATFORM_IS(WEB)

using wint_t = int;

// On Linux 'wint_t' is 'unsigned int'
#elif PHI_PLATFORM_IS(UNIX)

using wint_t = unsigned int;

// On windows platform 'wint_t' is 'unsigned short'
#elif PHI_PLATFORM_IS(WINDOWS)

using wint_t = unsigned short;

#else

// Otherwise fallback to using 'unsigned int' same as libc
// https://github.com/bminor/glibc/blob/master/wcsmbs/bits/types/wint_t.h#L17
using wint_t = unsigned int;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_WINT_T_HPP
