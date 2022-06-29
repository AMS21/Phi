#ifndef INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP
#define INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/move.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename TypeT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT accumulate(InputIteratorT first, InputIteratorT last,
                                                      TypeT init)
{
    for (; first != last; ++first)
    {
        init = move(init) + *first;
    }

    return init;
}

// TODO: noexcept
template <typename InputIteratorT, typename TypeT, typename BinaryOperationT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT accumulate(InputIteratorT first, InputIteratorT last,
                                                      TypeT init, BinaryOperationT binary_operator)
{
    for (; first != last; ++first)
    {
        init = binary_operator(move(init), *first);
    }

    return init;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_ACCUMULATE_HPP
