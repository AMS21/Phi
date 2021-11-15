#ifndef INCG_PHI_MATH_CONSTANTS_HPP
#define INCG_PHI_MATH_CONSTANTS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/Glue.hpp"
#include "Phi/Config/Inline.hpp"
#include "Phi/Core/Conversion.hpp"
#include "Phi/Core/Types.hpp"

#define DETAIL_PHI_DECLARE_CONSTANT(name, value)                                                   \
    template <typename TypeT>                                                                      \
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr TypeT PHI_GLUE(name, _v)() noexcept                  \
    {                                                                                              \
        return ::phi::unsafe_cast<TypeT>(value);                                                   \
    }                                                                                              \
                                                                                                   \
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr ::phi::f64 name() noexcept                           \
    {                                                                                              \
        return ::phi::PHI_GLUE(name, _v)<f64>();                                                   \
    }                                                                                              \
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr ::phi::f64 PHI_GLUE(name, _64)() noexcept            \
    {                                                                                              \
        return ::phi::PHI_GLUE(name, _v)<f64>();                                                   \
    }                                                                                              \
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr ::phi::f32 PHI_GLUE(name, _32)() noexcept            \
    {                                                                                              \
        return ::phi::PHI_GLUE(name, _v)<f32>();                                                   \
    }

DETAIL_PHI_BEGIN_NAMESPACE()

// Euler's number (\a e)
DETAIL_PHI_DECLARE_CONSTANT(
        e,
        2.71828182845904523536028747135266249775724709369995957496696762772407663035354759457138217852516642742746L)

// Pi (π)
DETAIL_PHI_DECLARE_CONSTANT(
        pi,
        3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651L)

// 2 * π
DETAIL_PHI_DECLARE_CONSTANT(
        two_pi,
        6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068423413596429617303L)

// Square root of π
DETAIL_PHI_DECLARE_CONSTANT(
        sqrt_pi,
        1.77245385090551602729816748334114518279754945612238712821380778985291128459103218137495065673854466541622682362L)

// π / 2
DETAIL_PHI_DECLARE_CONSTANT(
        half_pi,
        1.57079632679489661923132169163975144209858469968755291048747229615390820314310449931401741267105853399107404326L)

// 3 / 2π
DETAIL_PHI_DECLARE_CONSTANT(three_over_two_pi, 4.71238898038468985769396507491925432L)

// π / 4
DETAIL_PHI_DECLARE_CONSTANT(quarter_pi, 0.785398163397448309615660845819875721L)

// 1 / π
DETAIL_PHI_DECLARE_CONSTANT(one_over_pi, 0.318309886183790671537767526745028724L)

// 1 / 2π
DETAIL_PHI_DECLARE_CONSTANT(one_over_two_pi, 0.159154943091895335768883763372514362L)

// 2 / π
DETAIL_PHI_DECLARE_CONSTANT(two_over_pi, 0.636619772367581343075535053490057448L)

// 4 / π
DETAIL_PHI_DECLARE_CONSTANT(four_over_pi, 1.273239544735162686151070106980114898L)

// 2 / sqrt(π)
DETAIL_PHI_DECLARE_CONSTANT(two_over_sqrt_pi, 1.12837916709551257389615890312154517L)

// 1 / sqrt(2)
DETAIL_PHI_DECLARE_CONSTANT(one_over_sqrt_two, 0.707106781186547524400844362104849039L)

// sqrt(π / 2)
DETAIL_PHI_DECLARE_CONSTANT(
        sqrt_half_pi,
        1.25331413731550025120788264240552262650349337030496915831496178817114682730392098747329791918902863305800498633L)

// sqrt(2π)
DETAIL_PHI_DECLARE_CONSTANT(
        sqrt_two_pi,
        2.50662827463100050241576528481104525300698674060993831662992357634229365460784197494659583837805726611600997267L)

// sqrt(2)
DETAIL_PHI_DECLARE_CONSTANT(
        sqrt_two,
        1.41421356237309504880168872420969807856967187537694807317667973799073247846210703885038753432764157L)

// sqrt(3)
DETAIL_PHI_DECLARE_CONSTANT(
        sqrt_three,
        1.7320508075688772935274463415058723669428052538103806280558069794519330169088000370811461867572485756756261414154L)

DETAIL_PHI_DECLARE_CONSTANT(
        deg2rad,
        0.017453292519943295769236907684886127134428718885417254560971914401710091146034494436822415696345095L)

DETAIL_PHI_DECLARE_CONSTANT(
        rad2deg,
        57.295779513082320876798154814105170332405472466564321549160243861202847148321552632440968995851111L)

// golden ratio (phi)
DETAIL_PHI_DECLARE_CONSTANT(golden_ratio,
                            1.6180339887498948482045868343656381177203091798057628621L)

// cos(1) / 2
DETAIL_PHI_DECLARE_CONSTANT(cos_one_over_two, 0.877582561890372716130286068203503191L)

DETAIL_PHI_END_NAMESPACE()

#undef DETAIL_PHI_DECLARE_CONSTANT

#endif // INCG_PHI_MATH_CONSTANTS_HPP
