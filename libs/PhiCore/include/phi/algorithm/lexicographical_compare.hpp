#ifndef INCG_PHI_CORE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define INCG_PHI_CORE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorLhsT, typename InputIteratorRhsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean lexicographical_compare(InputIteratorLhsT first_lhs,
                                                                     InputIteratorLhsT last_lhs,
                                                                     InputIteratorRhsT first_rhs,
                                                                     InputIteratorRhsT last_rhs)
{
    for (; (first_lhs != last_lhs) && (first_rhs != last_rhs); ++first_lhs, ++first_rhs)
    {
        if (*first_lhs < *first_rhs)
        {
            return true;
        }
        if (*first_rhs < *first_lhs)
        {
            return false;
        }
    }

    return (first_lhs == last_lhs) && (first_rhs != last_rhs);
}

// TODO: noexcept
template <typename InputIteratorLhsT, typename InputIteratorRhsT, typename BinaryPredicateT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean lexicographical_compare(InputIteratorLhsT first_lhs,
                                                                     InputIteratorLhsT last_lhs,
                                                                     InputIteratorRhsT first_rhs,
                                                                     InputIteratorRhsT last_rhs,
                                                                     BinaryPredicateT  predicate)
{
    for (; (first_lhs != last_lhs) && (first_rhs != last_rhs); ++first_lhs, ++first_rhs)
    {
        if (predicate(*first_lhs, *first_rhs))
        {
            return true;
        }
        if (predicate(*first_rhs, *first_lhs))
        {
            return false;
        }
    }

    return (first_lhs == last_lhs) && (first_rhs != last_rhs);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
