#ifndef INCG_PHI_UTILITY_CONVERSION_HPP
#define INCG_PHI_UTILITY_CONVERSION_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/FloatingPoint.hpp"
#include "Phi/Core/Integer.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"
#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename>
    struct is_floatingpoint_specialization : public false_type
    {};

    template <typename FloatT>
    struct is_floatingpoint_specialization<FloatingPoint<FloatT>> : public true_type
    {};

    template <typename>
    struct is_integer_specilization : public false_type
    {};

    template <typename IntegerT>
    struct is_integer_specilization<Integer<IntegerT>> : public true_type
    {};

    template <typename TypeT>
    struct is_boolean_specilization
        : bool_constant<is_same_v<
                  typename std::remove_reference<typename remove_cv<TypeT>::type>::type, Boolean>>
    {};

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(SourceT&&      source,
                                                     std::true_type is_safe_type) noexcept
    {
        PHI_UNUSED_PARAMETER(is_safe_type);

        return static_cast<typename TargetT::value_type>(std::forward<SourceT>(source));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(SourceT&&       source,
                                                     std::false_type is_safe_type) noexcept
    {
        PHI_UNUSED_PARAMETER(is_safe_type);

        return static_cast<TargetT>(std::forward<SourceT>(source));
    }
} // namespace detail
/// \endcond

// unsafe_cast base
template <typename TargetT, typename SourceT>
PHI_NODISCARD constexpr TargetT unsafe_cast(SourceT&& source) noexcept
{
    using is_safe_type_t = typename std::integral_constant<
            bool, detail::is_floatingpoint_specialization<TargetT>::value ||
                          detail::is_integer_specilization<TargetT>::value ||
                          detail::is_boolean_specilization<TargetT>::value>;

    return detail::unsafe_cast_impl<TargetT, SourceT>(std::forward<SourceT>(source),
                                                      is_safe_type_t{});
}

// Floating Point
template <typename TargetT, typename SourceT>
PHI_NODISCARD constexpr TargetT unsafe_cast(FloatingPoint<SourceT>&& source) noexcept
{
    return unsafe_cast<TargetT>(source.get());
}

// Integer
template <typename TargetT, typename SourceT>
PHI_NODISCARD constexpr TargetT unsafe_cast(Integer<SourceT>&& source) noexcept
{
    return unsafe_cast<TargetT>(source.get());
}

// Narrow cast
template <typename TargetT, typename SourceT>
PHI_NODISCARD constexpr TargetT narrow_cast(SourceT&& source) noexcept
{
#if defined(PHI_DEBUG)
    constexpr const bool is_different_signedness =
            (std::is_signed<TargetT>::value != std::is_signed<SourceT>::value);

    const TargetT target = unsafe_cast<TargetT>(source);

    PHI_DBG_ASSERT(
            unsafe_cast<SourceT>(target) == source &&
                    (is_different_signedness || ((target < TargetT{}) == (source < SourceT{}))),
            "Invalid narrowing conversion. Source {}. Converted {}.");

    return target;
#else
    return unsafe_cast<TargetT>(source);
#endif
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_UTILITY_CONVERSION_HPP
