#ifndef INCG_PHI_CORE_ALGORITHM_CLAMP_HPP
#define INCG_PHI_CORE_ALGORITHM_CLAMP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_NODISCARD PHI_CONSTEXPR const TypeT& clamp(const TypeT& value, const TypeT& low_bound,
                                               const TypeT& high_bound) PHI_NOEXCEPT
{
    return value < low_bound ? low_bound : high_bound < value ? high_bound : value;
}

template <typename TypeT, typename CompareT>
PHI_NODISCARD PHI_CONSTEXPR const TypeT& clamp(const TypeT& value, const TypeT& low_bound,
                                               const TypeT& high_bound,
                                               CompareT     compare) PHI_NOEXCEPT
{
    return compare(value, low_bound) ? low_bound : compare(high_bound, value) ? high_bound : value;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_CLAMP_HPP
