#ifndef INCG_PHI_CORE_MATH_COMMON_HPP
#define INCG_PHI_CORE_MATH_COMMON_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include <limits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_CONSTEXPR PHI_ALWAYS_INLINE TypeT square(const TypeT value) PHI_NOEXCEPT
{
    return value * value;
}

template <typename TypeT>
PHI_CONSTEXPR PHI_ALWAYS_INLINE TypeT cube(const TypeT value) PHI_NOEXCEPT
{
    return value * value * value;
}

// Credits: https://gist.github.com/alexshtf/eb5128b3e3e143187794
/// \cond detail
namespace detail
{
    template <typename TypeT>
    PHI_CONSTEXPR TypeT sqrtNewtonRaphson(const TypeT value, const TypeT curr,
                                          const TypeT prev) PHI_NOEXCEPT
    {
        return curr == prev ? curr : sqrtNewtonRaphson(value, 0.5 * (curr + value / curr), curr);
    }
} // namespace detail
/// \endcond

/*!
 * \brief Constexpr version of the square root function
 *
 * \param value Value to calculate the square root of.
 *
 * \return For a finite and non-negative value of "value", returns an approximation for the square root of "value"
 *         Otherwise, returns NaN.
 *
**/
template <typename TypeT>
PHI_CONSTEXPR TypeT sqrt(const TypeT value) PHI_NOEXCEPT
{
    return value >= 0 && value < std::numeric_limits<TypeT>::infinity() ?
                   detail::sqrtNewtonRaphson(value, value, 0) :
                   std::numeric_limits<TypeT>::quiet_NaN();
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_COMMON_HPP
