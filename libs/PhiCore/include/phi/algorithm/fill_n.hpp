#ifndef INCG_PHI_CORE_ALGORITHM_FILL_N_HPP
#define INCG_PHI_CORE_ALGORITHM_FILL_N_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename OutputIteratorT, typename SizeT, typename TypeT>
PHI_EXTENDED_CONSTEXPR OutputIteratorT fill_n(OutputIteratorT first, SizeT count,
                                              const TypeT& value)
{
    for (; count > 0; ++first, --count)
    {
        *first++ = value;
    }

    return first;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_FILL_N_HPP
