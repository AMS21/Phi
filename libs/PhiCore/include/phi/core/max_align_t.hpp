#ifndef INCG_PHI_CORE_MAX_ALIGN_T_HPP
#define INCG_PHI_CORE_MAX_ALIGN_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/platform.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_COMPILER_IS(MSVC)

using max_align_t = double;

#elif PHI_PLATFORM_IS(APPLE)

using max_align_t = long double;

#else

// Define 'max_align_t' to match the GCC definition.
using max_align_t = struct
{
    long long   max_align_nonce1 alignas(alignof(long long));
    long double max_align_nonce2 alignas(alignof(long double));
};

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MAX_ALIGN_T_HPP
