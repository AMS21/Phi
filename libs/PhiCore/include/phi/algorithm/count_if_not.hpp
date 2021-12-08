#ifndef INCG_PHI_CORE_ALGORITHM_COUNT_IF_NOT_HPP
#define INCG_PHI_CORE_ALGORITHM_COUNT_IF_NOT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include <iterator>

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename UnaryPredicateT>
PHI_NODISCARD typename std::iterator_traits<InputIteratorT>::difference_type PHI_EXTENDED_CONSTEXPR
count_if_not(InputIteratorT first, InputIteratorT last, UnaryPredicateT predicate)
{
    typename std::iterator_traits<InputIteratorT>::difference_type ret = 0;

    for (; first != last; ++first)
    {
        if (!predicate(*first))
        {
            ++ret;
        }
    }

    return ret;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_COUNT_IF_NOT_HPP
