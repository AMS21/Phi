#ifndef INCG_PHI_CORE_ALGORITHM_IS_SORTED_HPP
#define INCG_PHI_CORE_ALGORITHM_IS_SORTED_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core/Boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ForwardIteratorT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR Boolean is_sorted(ForwardIteratorT first,
                                                       ForwardIteratorT last) // TODO: noexcept
{
    if (first != last)
    {
        ForwardIteratorT next = first;
        while (++next != last)
        {
            if (*next < *first)
            {
                return false;
            }

            first = next;
        }
    }

    return true;
}

template <typename ForwardIteratorT, typename CompareT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR Boolean is_sorted(ForwardIteratorT first,
                                                       ForwardIteratorT last,
                                                       CompareT         comp) // TODO: noexcept
{
    if (first != last)
    {
        ForwardIteratorT next = first;
        while (++next != last)
        {
            if (comp(*next, *first))
            {
                return false;
            }

            first = next;
        }
    }

    return true;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_IS_SORTED_HPP
