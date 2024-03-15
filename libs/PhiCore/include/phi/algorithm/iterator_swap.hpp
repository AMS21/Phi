#ifndef INCG_PHI_CORE_ALGORITHM_ITERATOR_SWAP_HPP
#define INCG_PHI_CORE_ALGORITHM_ITERATOR_SWAP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/declval.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsIteratorT, typename RhsIteratorT>
PHI_EXTENDED_CONSTEXPR void iterator_swap(LhsIteratorT lhs, RhsIteratorT rhs)
        PHI_NOEXCEPT_EXPR(noexcept(swap(*declval<LhsIteratorT>(), *declval<RhsIteratorT>())))
{
    swap(*lhs, *rhs);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_ITERATOR_SWAP_HPP
