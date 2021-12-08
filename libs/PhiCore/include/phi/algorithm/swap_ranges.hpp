#ifndef INCG_PHI_CORE_ALGORITHM_SWAP_RANGES_HPP
#define INCG_PHI_CORE_ALGORITHM_SWAP_RANGES_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/core/declval.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsIteratorT, typename RhsIteratorT>
PHI_EXTENDED_CONSTEXPR RhsIteratorT swap_ranges(
        LhsIteratorT lhs_first, LhsIteratorT lhs_last,
        RhsIteratorT rhs_first) noexcept(swap(*declval<LhsIteratorT>(), *declval<RhsIteratorT>()))
{
    for (; lhs_first != lhs_last; ++lhs_first, (void)++rhs_first)
    {
        swap(*lhs_first, *rhs_first);
    }

    return rhs_first;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_SWAP_RANGES_HPP
