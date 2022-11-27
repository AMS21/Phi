#ifndef INCG_PHI_CORE_ALGORITHM_FOR_EACH_HPP
#define INCG_PHI_CORE_ALGORITHM_FOR_EACH_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename UnaryFunctionT>
PHI_EXTENDED_CONSTEXPR UnaryFunctionT for_each(InputIteratorT first, InputIteratorT last,
                                               UnaryFunctionT func)
{
    for (; first != last; ++first)
    {
        func(*first);
    }

    return func;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_FOR_EACH_HPP
