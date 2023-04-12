/**
 * @file all_of.hpp
 * @brief Contains the implementation of the all_of algorithm from the C++ standard library.
 *
 * @see https://en.cppreference.com/w/cpp/algorithm/all_of
 */
#ifndef INCG_PHI_CORE_ALGORITHM_ALL_OF_HPP
#define INCG_PHI_CORE_ALGORITHM_ALL_OF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
/**
 * @brief Returns true if all elements in the range [first, last) satisfy the predicate.
 *
 * @tparam InputIteratorT The iterator type of the input range.
 * @tparam PredicateT The type of the predicate function.
 * @param first The first iterator of the input range.
 * @param last The end iterator of the input range.
 * @param predicate The unary predicate function which should return true for the elements to be included in the result.
 * @return `true` if the predicate returns `true` for all elements in the range, `false` otherwise.
 *
 * @see https://en.cppreference.com/w/cpp/algorithm/all_of
 */
template <typename InputIteratorT, typename PredicateT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR bool all_of(InputIteratorT first, InputIteratorT last,
                                                 PredicateT predicate)
{
    for (; first != last; ++first)
    {
        if (!predicate(*first))
        {
            return false;
        }
    }

    return true;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_ALL_OF_HPP
