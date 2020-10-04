#ifndef INCG_PHI_UTILITY_CONVERSION_HPP
#define INCG_PHI_UTILITY_CONVERSION_HPP

#include "Phi/PhiConfig.hpp"
#include "Phi/Utility/Assert.hpp"
#include "Phi/Utility/FloatingPoint.hpp"
#include "Phi/Utility/Integer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename>
    struct is_floatingpoint_specialization : std::false_type
    {};

    template <typename FloatT>
    struct is_floatingpoint_specialization<FloatingPoint<FloatT>> : std::true_type
    {};

    template <typename>
    struct is_integer_specilization : std::false_type
    {};

    template <typename IntegerT>
    struct is_integer_specilization<Integer<IntegerT>> : std::true_type
    {};
} // namespace detail
/// \endcond

// unsafe_cast base
template <typename TargetT, typename SourceT>
[[nodiscard]] constexpr TargetT unsafe_cast(SourceT&& source) noexcept
{
    if constexpr (detail::is_floatingpoint_specialization<TargetT>::value ||
                  detail::is_integer_specilization<TargetT>::value ||
                  std::is_same_v<std::remove_reference_t<std::remove_cv_t<SourceT>>, Boolean>)
    {
        return static_cast<typename TargetT::value_type>(std::forward<SourceT>(source));
    }
    else
    {
        return static_cast<TargetT>(std::forward<SourceT>(source));
    }
}

// Floating Point
template <typename TargetT, typename SourceT>
[[nodiscard]] constexpr TargetT unsafe_cast(FloatingPoint<SourceT>&& source) noexcept
{
    return unsafe_cast<TargetT>(source.get());
}

// Integer
template <typename TargetT, typename SourceT>
[[nodiscard]] constexpr TargetT unsafe_cast(Integer<SourceT>&& source) noexcept
{
    return unsafe_cast<TargetT>(source.get());
}

// Narrow cast
template <typename TargetT, typename SourceT>
[[nodiscard]] constexpr TargetT narrow_cast(SourceT&& source) noexcept
{
#if defined(PHI_DEBUG)
    constexpr const bool is_different_signedness =
            (std::is_signed<TargetT>::value != std::is_signed<SourceT>::value);

    const TargetT target = unsafe_cast<TargetT>(source);

    // TODO: Remove once asserts are usable inside a constexpr context
    if (!std::is_constant_evaluated())
    {
        PHI_DBG_ASSERT(
                unsafe_cast<SourceT>(target) == source &&
                        (is_different_signedness || ((target < TargetT{}) == (source < SourceT{}))),
                "Invalid narrowing conversion. Source {}. Converted {}.");
    }
    else
    {
        if (!(unsafe_cast<SourceT>(target) == source &&
              (is_different_signedness || ((target < TargetT{}) == (source < SourceT{})))))
        {
            throw "Invalid narrowing conversion";
        }
    }

    return target;
#else
    return unsafe_cast<TargetT>(source);
#endif
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_UTILITY_CONVERSION_HPP
