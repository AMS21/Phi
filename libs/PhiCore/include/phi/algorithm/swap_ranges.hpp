#ifndef INCG_PHI_CORE_ALGORITHM_SWAP_RANGES_HPP
#define INCG_PHI_CORE_ALGORITHM_SWAP_RANGES_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/core/declval.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsIteratorT, typename RhsIteratorT>
PHI_EXTENDED_CONSTEXPR RhsIteratorT swap_ranges(LhsIteratorT lhs_first, LhsIteratorT lhs_last,
                                                RhsIteratorT rhs_first)
// TODO: This noexcept expression seems to not work on gcc-8
#if PHI_COMPILER_IS_NOT(GCC) || PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0)
        noexcept(noexcept(swap(*declval<LhsIteratorT>(), *declval<RhsIteratorT>())))
#endif
{
    for (; lhs_first != lhs_last; ++lhs_first, (void)++rhs_first)
    {
        swap(*lhs_first, *rhs_first);
    }

    return rhs_first;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_SWAP_RANGES_HPP
