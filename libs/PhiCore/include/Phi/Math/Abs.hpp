#ifndef INCG_PHI_CORE_MATH_ABS_HPP
#define INCG_PHI_CORE_MATH_ABS_HPP

#include "Phi/Config/Compiler.hpp"
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
    template <typename TypeT>
    struct make_unsigned_abs
    {
        using type = TypeT;
    };

    template <>
    struct make_unsigned_abs<signed short>
    {
        using type = unsigned short;
    };

    template <>
    struct make_unsigned_abs<unsigned short>
    {
        using type = unsigned short;
    };

    template <>
    struct make_unsigned_abs<signed int>
    {
        using type = unsigned int;
    };

    template <>
    struct make_unsigned_abs<unsigned int>
    {
        using type = unsigned int;
    };

    template <>
    struct make_unsigned_abs<signed long>
    {
        using type = unsigned long;
    };

    template <>
    struct make_unsigned_abs<unsigned long>
    {
        using type = unsigned long;
    };

    template <>
    struct make_unsigned_abs<signed long long>
    {
        using type = unsigned long long;
    };

    template <>
    struct make_unsigned_abs<unsigned long long>
    {
        using type = unsigned long long;
    };

    template <typename SignedNumericT>
    [[nodiscard]] PHI_ALWAYS_INLINE constexpr typename make_unsigned_abs<SignedNumericT>::type
    abs_impl(const SignedNumericT signed_numeric, std::false_type is_floating_point,
             std::true_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_floating_point);
        PHI_UNUSED_PARAMETER(is_signed);

        using unsigned_t = typename make_unsigned_abs<SignedNumericT>::type;

        return static_cast<unsigned_t>((signed_numeric > 0) ? signed_numeric : -signed_numeric);
    }

    template <typename UnsignedNumericT>
    [[nodiscard]] PHI_ALWAYS_INLINE constexpr UnsignedNumericT abs_impl(
            const UnsignedNumericT unsigned_numeric, std::false_type is_floating_point,
            std::false_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_floating_point);
        PHI_UNUSED_PARAMETER(is_signed);

        return unsigned_numeric;
    }

    [[nodiscard]] PHI_ALWAYS_INLINE constexpr float abs_impl(const float    floating_point_numeric,
                                                             std::true_type is_floating_point,
                                                             std::true_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_floating_point);
        PHI_UNUSED_PARAMETER(is_signed);

#if PHI_COMPILER_IS(MSVC)
        return fabsf(floating_point_numeric);
#else
        return __builtin_fabsf(floating_point_numeric);
#endif
    }

    [[nodiscard]] PHI_ALWAYS_INLINE constexpr double abs_impl(const double   floating_point_numeric,
                                                              std::true_type is_floating_point,
                                                              std::true_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_floating_point);
        PHI_UNUSED_PARAMETER(is_signed);

#if PHI_COMPILER_IS(MSVC)
        return fabs(floating_point_numeric);
#else
        return __builtin_fabs(floating_point_numeric);
#endif
    }

    [[nodiscard]] PHI_ALWAYS_INLINE constexpr long double abs_impl(
            const long double floating_point_numeric, std::true_type is_floating_point,
            std::true_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_floating_point);
        PHI_UNUSED_PARAMETER(is_signed);

#if PHI_COMPILER_IS(MSVC)
        return fabsl(floating_point_numeric);
#else
        return __builtin_fabsl(floating_point_numeric);
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
[[nodiscard]] constexpr typename detail::make_unsigned_abs<NumericT>::type abs(
        NumericT numeric) noexcept
{
    return detail::abs_impl(numeric, std::is_floating_point<NumericT>(),
                            std::is_signed<NumericT>());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_ABS_HPP
