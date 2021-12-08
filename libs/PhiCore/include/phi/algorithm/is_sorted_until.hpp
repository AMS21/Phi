#ifndef INCG_PHI_CORE_ALGORITHM_IS_SORTED_UNTIL_HPP
#define INCG_PHI_CORE_ALGORITHM_IS_SORTED_UNTIL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ForwardIteratorT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR ForwardIteratorT
is_sorted_until(ForwardIteratorT first,
                ForwardIteratorT last) // TODO: noexcept
{
    if (first != last)
    {
        ForwardIteratorT next = first;
        while (++next != last)
        {
            if (*next < *first)
            {
                return next;
            }

            first = next;
        }
    }

    return last;
}

template <typename ForwardIteratorT, typename CompareT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR ForwardIteratorT
is_sorted_until(ForwardIteratorT first, ForwardIteratorT last, CompareT comp) // TODO: noexcept
{
    if (first != last)
    {
        ForwardIteratorT next = first;
        while (++next != last)
        {
            if (comp(*next, *first))
            {
                return next;
            }

            first = next;
        }
    }

    return last;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_IS_SORTED_UNTIL_HPP
