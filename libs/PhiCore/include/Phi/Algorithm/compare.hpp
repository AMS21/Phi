#ifndef INCG_PHI_CORE_ALGORITHM_COMPARE_HPP
#define INCG_PHI_CORE_ALGORITHM_COMPARE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

enum class CompareResult
{
    Equal,
    LessThan,
    GreaterThan,
};

template <typename LhsT, typename RhsT>
PHI_NODISCARD constexpr CompareResult compare(LhsT lhs,
                                              RhsT rhs) noexcept(noexcept(lhs == rhs && lhs < rhs))
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    if (lhs == rhs)
    {
        return CompareResult::Equal;
    }
    if (lhs < rhs)
    {
        return CompareResult::LessThan;
    }

    return CompareResult::GreaterThan;
#else
    return lhs == rhs  ? CompareResult::Equal :
           (lhs < rhs) ? CompareResult::LessThan :
                         CompareResult::GreaterThan;
#endif
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_COMPARE_HPP
