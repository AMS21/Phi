#ifndef INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP
#define INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/Core/Move.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename TypeT>
PHI_EXTENDED_CONSTEXPR TypeT accumulate(InputIteratorT first, InputIteratorT last, TypeT init)
{
    for (; first != last; ++first)
    {
        init = move(init) + *first;
    }

    return init;
}

// TODO: noexcept
template <typename InputIteratorT, typename TypeT, typename BinaryOperationT>
PHI_EXTENDED_CONSTEXPR TypeT accumulate(InputIteratorT first, InputIteratorT last, TypeT init,
                                        BinaryOperationT op)
{
    for (; first != last; ++first)
    {
        init = op(move(init), *first);
    }

    return init;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP
