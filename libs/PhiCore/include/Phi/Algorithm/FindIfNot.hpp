#ifndef INCG_PHI_CORE_ALGORITHM_FIND_IF_NOT_HPP
#define INCG_PHI_CORE_ALGORITHM_FIND_IF_NOT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename UnaryPredicateT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR InputIteratorT find_if_not(InputIteratorT  first,
                                                                InputIteratorT  last,
                                                                UnaryPredicateT predicate)
{
    for (; first != last; ++first)
    {
        if (!predicate(*first))
        {
            return first;
        }
    }

    return last;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_FIND_IF_NOT_HPP
