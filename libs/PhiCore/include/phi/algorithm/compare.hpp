#ifndef INCG_PHI_CORE_ALGORITHM_COMPARE_HPP
#define INCG_PHI_CORE_ALGORITHM_COMPARE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/compare_result.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT>
PHI_NODISCARD constexpr CompareResult compare(LhsT lhs,
                                              RhsT rhs) noexcept(noexcept(lhs == rhs && lhs < rhs))
{
    return (lhs == rhs) ? CompareResult::Equal :
           (lhs < rhs)  ? CompareResult::LessThan :
                          CompareResult::GreaterThan;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_COMPARE_HPP
