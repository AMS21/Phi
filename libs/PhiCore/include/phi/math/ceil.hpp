#ifndef INCG_PHI_CORE_MATH_CEIL_HPP
#define INCG_PHI_CORE_MATH_CEIL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/sized_types.hpp"
#include "phi/type_traits/is_floating_point.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FloatT>
class floating_point;

template <typename FloatT>
PHI_NODISCARD PHI_CONSTEXPR int64_t ceil(FloatT value) noexcept
{
    static_assert(is_floating_point<FloatT>::value, "phi::ceil requires a floating point type");

    return (value > static_cast<FloatT>(static_cast<int64_t>(value))) ?
                   static_cast<int64_t>(value) + 1 :
                   static_cast<int64_t>(value);
}

template <typename FloatT>
PHI_NODISCARD PHI_CONSTEXPR int64_t ceil(floating_point<FloatT> value) noexcept
{
    return ceil(value.unsafe());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_CEIL_HPP
