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
PHI_NODISCARD constexpr compare_result compare(LhsT lhs,
                                               RhsT rhs) noexcept(noexcept(lhs == rhs && lhs < rhs))
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    if (lhs == rhs)
    {
        return compare_result::Equal;
    }
    if (lhs < rhs)
    {
        return compare_result::LessThan;
    }

    return compare_result::GreaterThan;
#else
    return (lhs == rhs) ? compare_result::Equal :
           (lhs < rhs)  ? compare_result::LessThan :
                          compare_result::GreaterThan;
#endif
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_COMPARE_HPP
