#ifndef INCG_PHI_CORE_UNSAFE_CAST_HPP
#define INCG_PHI_CORE_UNSAFE_CAST_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/forward.hpp"
#include "phi/type_traits/is_safe_type.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TargetT, typename SourceT>
    PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast_impl(const SourceT& source,
                                                         true_type /*target_safe*/,
                                                         true_type /*source_safe*/) PHI_NOEXCEPT
    {
        return static_cast<typename TargetT::value_type>(
                forward<const typename remove_reference_t<SourceT>::value_type>(source.unsafe()));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast_impl(SourceT&& source,
                                                         true_type /* target_safe*/,
                                                         true_type /*source_safe*/) PHI_NOEXCEPT
    {
        return static_cast<typename TargetT::value_type>(
                forward<typename remove_reference_t<SourceT>::value_type>(source.unsafe()));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast_impl(const SourceT& source,
                                                         true_type /*target_safe*/,
                                                         false_type /*source_safe*/) PHI_NOEXCEPT
    {
        return static_cast<typename remove_reference_t<TargetT>::value_type>(
                forward<const SourceT>(source));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast_impl(SourceT&& source, true_type /*target_safe*/
                                                         ,
                                                         false_type /*source_safe*/) PHI_NOEXCEPT
    {
        return static_cast<typename remove_reference_t<TargetT>::value_type>(
                forward<SourceT>(source));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast_impl(const SourceT& source,
                                                         false_type /*target_safe*/,
                                                         true_type /*source_safe*/) PHI_NOEXCEPT
    {
        return static_cast<TargetT>(
                forward<const typename remove_reference_t<SourceT>::value_type>(source.unsafe()));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast_impl(SourceT&& source,
                                                         false_type /*target_safe*/,
                                                         true_type /*source_safe*/) PHI_NOEXCEPT
    {
        return static_cast<TargetT>(
                forward<typename remove_reference_t<SourceT>::value_type>(source.unsafe()));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast_impl(const SourceT& source,
                                                         false_type /*target_safe*/,
                                                         false_type /*source_safe*/) PHI_NOEXCEPT
    {
        return static_cast<TargetT>(forward<const SourceT>(source));
    }

    template <typename TargetT, typename SourceT>
    PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast_impl(SourceT&& source,
                                                         false_type /*target_safe*/,
                                                         false_type /*source_safe*/) PHI_NOEXCEPT
    {
        return static_cast<TargetT>(forward<SourceT>(source));
    }
} // namespace detail
/// \endcond

// unsafe_cast base
template <typename TargetT, typename SourceT>
PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast(const SourceT& source) PHI_NOEXCEPT
{
    return detail::unsafe_cast_impl<TargetT, SourceT>(forward<const SourceT>(source),
                                                      is_safe_type<remove_reference_t<TargetT>>{},
                                                      is_safe_type<remove_reference_t<SourceT>>{});
}

template <typename TargetT, typename SourceT>
PHI_NODISCARD PHI_CONSTEXPR TargetT unsafe_cast(SourceT&& source) PHI_NOEXCEPT
{
    return detail::unsafe_cast_impl<TargetT, SourceT>(forward<SourceT>(source),
                                                      is_safe_type<remove_reference_t<TargetT>>{},
                                                      is_safe_type<remove_reference_t<SourceT>>{});
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_UNSAFE_CAST_HPP
