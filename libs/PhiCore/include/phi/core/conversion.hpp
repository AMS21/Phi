#ifndef INCG_PHI_CORE_CONVERSION_HPP
#define INCG_PHI_CORE_CONVERSION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/unused.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/floating_point.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/integer.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_safe_type.hpp"
#include "phi/type_traits/is_signed.hpp"
#include "phi/type_traits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(const SourceT&       source,
                                                     true_type /*target_safe*/,
                                                     true_type /*source_safe*/) noexcept
    {
        return static_cast<typename TargetT::value_type>(
                phi::forward<const typename remove_reference_t<SourceT>::value_type>(source.get()));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(SourceT&&            source, true_type /* target_safe*/,
                                                     true_type /*source_safe*/) noexcept
    {
        return static_cast<typename TargetT::value_type>(
                phi::forward<typename remove_reference_t<SourceT>::value_type>(source.get()));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(const SourceT&        source,
                                                     true_type /*target_safe*/,
            false_type /*source_safe*/) noexcept
    {
        return static_cast<typename remove_reference_t<TargetT>::value_type>(
                phi::forward<const SourceT>(source));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(SourceT&& source, true_type /*target_safe*/
                                                     ,
                                                     false_type /*source_safe*/) noexcept
    {
        return static_cast<typename remove_reference_t<TargetT>::value_type>(
                phi::forward<SourceT>(source));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(const SourceT&        source,
                                                     false_type /*target_safe*/,
                                                     true_type /*source_safe*/) noexcept
    {
        return static_cast<TargetT>(
                phi::forward<const typename remove_reference_t<SourceT>::value_type>(source.get()));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(SourceT&&             source,
                                                     false_type /*target_safe*/,
                                                     true_type /*source_safe*/) noexcept
    {
        return static_cast<TargetT>(
                phi::forward<typename remove_reference_t<SourceT>::value_type>(source.get()));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(const SourceT&        source,
                                                     false_type /*target_safe*/,
                                                     false_type /*source_safe*/) noexcept
    {
        return static_cast<TargetT>(phi::forward<const SourceT>(source));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD constexpr TargetT unsafe_cast_impl(SourceT&&             source, false_type /*target_safe*/,
                                                     false_type /*source_safe*/) noexcept
    {
        return static_cast<TargetT>(phi::forward<SourceT>(source));
    }
} // namespace detail
/// \endcond

// unsafe_cast base
template <typename TargetT, typename SourceT>
PHI_NODISCARD constexpr TargetT unsafe_cast(const SourceT& source) noexcept
{
    return detail::unsafe_cast_impl<TargetT, SourceT>(phi::forward<const SourceT>(source),
                                                      is_safe_type<remove_reference_t<TargetT>>{},
                                                      is_safe_type<remove_reference_t<SourceT>>{});
}

template <typename TargetT, typename SourceT>
PHI_NODISCARD constexpr TargetT unsafe_cast(SourceT&& source) noexcept
{
    return detail::unsafe_cast_impl<TargetT, SourceT>(phi::forward<SourceT>(source),
                                                      is_safe_type<remove_reference_t<TargetT>>{},
                                                      is_safe_type<remove_reference_t<SourceT>>{});
}

// Narrow cast
template <typename TargetT, typename SourceT>
PHI_NODISCARD
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() || !defined(PHI_DEBUG)
        constexpr
#endif
        TargetT
        narrow_cast(SourceT&& source) noexcept
{
#if defined(PHI_DEBUG)
    constexpr const bool is_different_signedness =
            (is_signed<TargetT>::value != is_signed<SourceT>::value);

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

#endif // INCG_PHI_CORE_CONVERSION_HPP
