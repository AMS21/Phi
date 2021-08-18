#ifndef INCG_PHI_CORE_MATH_ABS_HPP
#define INCG_PHI_CORE_MATH_ABS_HPP

#include "Phi/Config/Inline.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/PhiConfig.hpp"
#include <limits>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename UnsignedNumericT>
    [[nodiscard]] PHI_ALWAYS_INLINE constexpr UnsignedNumericT abs(
            const UnsignedNumericT unsigned_numeric, std::false_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_signed);

        return unsigned_numeric;
    }

    template <typename SignedNumericT>
    [[nodiscard]] PHI_ALWAYS_INLINE constexpr SignedNumericT abs(
            const SignedNumericT signed_numeric, std::true_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_signed);
        PHI_DBG_ASSERT(
                signed_numeric > std::numeric_limits<SignedNumericT>::min(),
                "Calling abs on the minium value of a signed integer will cause an underflow");

        return (signed_numeric > 0) ? signed_numeric : -signed_numeric;
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
[[nodiscard]] PHI_ALWAYS_INLINE constexpr NumericT abs(NumericT numeric) noexcept
{
    return detail::abs(numeric, std::is_signed<NumericT>());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_ABS_HPP
