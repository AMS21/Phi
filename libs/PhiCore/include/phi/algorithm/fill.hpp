#ifndef INCG_PHI_CORE_ALGORITHM_FILL_HPP
#define INCG_PHI_CORE_ALGORITHM_FILL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/noexcept.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ForwardIteratorT, typename TypeT>
PHI_EXTENDED_CONSTEXPR void fill(ForwardIteratorT first, ForwardIteratorT last, const TypeT& value)
        PHI_NOEXCEPT_EXPR(noexcept(first != last) && noexcept(++first) && noexcept(*first = value))
{
    for (; first != last; ++first)
    {
        *first = value;
    }
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_FILL_HPP
