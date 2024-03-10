#ifndef INCG_PHI_CORE_ALGORITHM_COPY_N_HPP
#define INCG_PHI_CORE_ALGORITHM_COPY_N_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename InputIteratorT, typename SizeT, typename OutputIteratorT>
PHI_EXTENDED_CONSTEXPR OutputIteratorT
copy_n(InputIteratorT first, SizeT count,
       OutputIteratorT result) noexcept(noexcept(count > 0) && noexcept(*result = *first) &&
                                        noexcept(++result) && noexcept(count == SizeT(1)) &&
                                        noexcept(count != SizeT(1)) && noexcept(++count) &&
                                        noexcept(++first))
{
    if (count > 0)
    {
        *result = *first;
        ++result;

        for (SizeT i = 1; i != count; ++i, ++result)
        {
            *result = *++first;
        }
    }

    return result;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_COPY_N_HPP
