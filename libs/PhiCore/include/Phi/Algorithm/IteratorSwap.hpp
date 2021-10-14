#ifndef INCG_PHI_CORE_ALGORITHM_ITERATOR_SWAP_HPP
#define INCG_PHI_CORE_ALGORITHM_ITERATOR_SWAP_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Algorithm/Swap.hpp"
#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/Core/Declval.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsIteratorT, typename RhsIteratorT>
PHI_EXTENDED_CONSTEXPR void iterator_swap(LhsIteratorT lhs, RhsIteratorT rhs) noexcept(
        noexcept(swap(*declval<LhsIteratorT>(), *declval<RhsIteratorT>())))
{
    swap(*lhs, *rhs);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_ITERATOR_SWAP_HPP
