#ifndef INCG_PHI_CORE_ALGORITHM_FOR_EACH_N_HPP
#define INCG_PHI_CORE_ALGORITHM_FOR_EACH_N_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename SizeT, typename UnaryFunctionT>
PHI_EXTENDED_CONSTEXPR InputIteratorT for_each_n(InputIteratorT first, SizeT n, UnaryFunctionT func)
{
    while (n > 0)
    {
        func(*first);
        ++first;
        --n;
    }

    return first;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_FOR_EACH_N_HPP
