#ifndef INCG_PHI_CORE_ALGORITHM_NONE_OF_HPP
#define INCG_PHI_CORE_ALGORITHM_NONE_OF_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename PredicateT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR bool none_of(InputIteratorT first, InputIteratorT last,
                                                  PredicateT predicate)
{
    for (; first != last; ++first)
    {
        if (!(predicate(*first)))
        {
            return false;
        }
    }

    return true;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_NONE_OF_HPP
