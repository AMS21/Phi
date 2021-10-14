#ifndef INCG_PHI_CORE_MATH_ABS_HPP
#define INCG_PHI_CORE_MATH_ABS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/CompilerSupport/Unused.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Inline.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_enum.hpp"
#include "Phi/TypeTraits/is_floating_point.hpp"
#include "Phi/TypeTraits/is_integral.hpp"
#include "Phi/TypeTraits/is_signed.hpp"
#include "Phi/TypeTraits/make_unsigned.hpp"
#include "Phi/TypeTraits/to_unsafe.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename SignedNumericT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsigned_t<SignedNumericT> abs_impl(
            const SignedNumericT signed_numeric, PHI_UNUSED false_type is_floating_point,
            PHI_UNUSED true_type is_signed) noexcept
    {
        using unsigned_t = make_unsigned_t<SignedNumericT>;

        return (signed_numeric > 0) ? static_cast<unsigned_t>(signed_numeric) :
                                      (-static_cast<unsigned_t>(signed_numeric));
    }

    template <typename UnsignedNumericT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr UnsignedNumericT abs_impl(
            const UnsignedNumericT unsigned_numeric, PHI_UNUSED false_type is_floating_point,
            PHI_UNUSED false_type is_signed) noexcept
    {
        return unsigned_numeric;
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr float abs_impl(
            const float floating_point_numeric, PHI_UNUSED true_type is_floating_point,
            PHI_UNUSED true_type is_signed) noexcept
    {
#if PHI_HAS_INTRINSIC_BUILTIN_FABSF()
        return __builtin_fabsf(floating_point_numeric);
#else
        return (floating_point_numeric > 0) ? floating_point_numeric : -floating_point_numeric;
#endif
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr double abs_impl(
            const double floating_point_numeric, PHI_UNUSED true_type is_floating_point,
            PHI_UNUSED true_type is_signed) noexcept
    {
#if PHI_HAS_INTRINSIC_BUILTIN_FABS()
        return __builtin_fabs(floating_point_numeric);
#else
        return (floating_point_numeric > 0) ? floating_point_numeric : -floating_point_numeric;
#endif
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr long double abs_impl(
            const long double floating_point_numeric, PHI_UNUSED true_type is_floating_point,
            PHI_UNUSED true_type is_signed) noexcept
    {
#if PHI_HAS_INTRINSIC_BUILTIN_FABSL()
        return __builtin_fabsl(floating_point_numeric);
#else
        return (floating_point_numeric > 0) ? floating_point_numeric : -floating_point_numeric;
#endif
    }
} // namespace detail
/// \endcond

/*!
 * \brief Calculates the absolute value of a given number
 *
 * The mathematical equivalent to |x|. This version of abs also supports
 * unsigned values and can be used in a constexpr context unlike the version
 * from the standard.
 *
 * \param numeric Numeric value to calculate the absolute value of.
 *
 * \return Absolute value of \a numeric
 *
**/
template <typename NumericT>
PHI_NODISCARD constexpr make_unsigned_t<NumericT> abs(NumericT numeric) noexcept
{
    return detail::abs_impl(to_unsafe(numeric), is_floating_point<NumericT>(),
                            is_signed<NumericT>());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_ABS_HPP
