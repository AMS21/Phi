#ifndef INCG_PHI_CORE_ALGORITHM_FIND_HPP
#define INCG_PHI_CORE_ALGORITHM_FIND_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename TypeT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR InputIteratorT find(InputIteratorT first, InputIteratorT last,
                                                         const TypeT& value)
{
    for (; first != last; ++first)
    {
        if (*first == value)
        {
            return first;
        }
    }

    return last;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_FIND_HPP
