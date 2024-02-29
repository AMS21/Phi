#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_BUGS_GCC_102305_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_BUGS_GCC_102305_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305
// NOTE: This bug only affects the gcc compiler and is fixed in all major releases starting with gcc-12
//       Also the fix was backported to gcc-11.3, gcc-10.4 and gcc-9.5
//       The intrinsic '__is_constructible' is first available with gcc-8
#if PHI_COMPILER_IS_ATLEAST(GCC, 8, 0, 0) &&                                                       \
        (PHI_COMPILER_IS_BELOW(GCC, 9, 5, 0) /* gcc-8.0 - gcc-9.4 */ ||                            \
         (PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0) &&                                                \
          PHI_COMPILER_IS_BELOW(GCC, 10, 4, 0)) /* gcc-10.0 - gcc-10.4 */                          \
         || (PHI_COMPILER_IS_ATLEAST(GCC, 11, 0, 0) &&                                             \
             PHI_COMPILER_IS_BELOW(GCC, 11, 3, 0)) /* gcc-11.0 - gcc-11.2 */)

#    define PHI_HAS_BUG_GCC_102305() 1

#else

#    define PHI_HAS_BUG_GCC_102305() 0

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_BUGS_GCC_102305_HPP
