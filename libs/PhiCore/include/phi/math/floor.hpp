#ifndef INCG_PHI_CORE_MATH_FLOOR_HPP
#define INCG_PHI_CORE_MATH_FLOOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/type_traits/is_floating_point.hpp"

// godbolt link: https://godbolt.org/z/64asPzfW6

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FloatT>
class floating_point;

template <typename FloatT>
PHI_NODISCARD constexpr FloatT floor(FloatT value) noexcept
{
    static_assert(is_floating_point<FloatT>::value, "phi::floor requires a floating point type");

    return static_cast<FloatT>(static_cast<int>(value));
}

template <typename FloatT>
PHI_NODISCARD constexpr floating_point<FloatT> floor(floating_point<FloatT> value) noexcept
{
    return floor(value.unsafe());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_FLOOR_HPP
