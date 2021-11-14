#ifndef INCG_PHI_CORE_ALGORITHM_COUNT_IF_HPP
#define INCG_PHI_CORE_ALGORITHM_COUNT_IF_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include <iterator>

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename UnaryPredicateT>
PHI_NODISCARD typename std::iterator_traits<InputIteratorT>::difference_type PHI_EXTENDED_CONSTEXPR
count_if(InputIteratorT first, InputIteratorT last, UnaryPredicateT predicate)
{
    typename std::iterator_traits<InputIteratorT>::difference_type ret = 0;

    for (; first != last; ++first)
    {
        if (predicate(*first))
        {
            ++ret;
        }
    }

    return ret;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_COUNT_IF_HPP
