#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_swappable_with.hpp"
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, typename OtherT = TypeT,
              bool is_swappable = is_swappable_with<TypeT, OtherT>::value>
    struct is_nothrow_swappable_with_impl
    {
        static const bool value =
                noexcept(std::swap(std::declval<TypeT>(), std::declval<OtherT>()))&& noexcept(
                        std::swap(std::declval<OtherT>(), std::declval<TypeT>()));
    };

    template <typename TypeT, typename OtherT>
    struct is_nothrow_swappable_with_impl<TypeT, OtherT, false> : std::false_type
    {};
} // namespace detail

template <typename TypeT, typename OtherT>
struct is_nothrow_swappable_with
    : public std::integral_constant<bool,
                                    detail::is_nothrow_swappable_with_impl<TypeT, OtherT>::value>
{};

template <typename TypeT, typename OtherT>
constexpr PHI_INLINE_VARIABLE bool is_nothrow_swappable_with_v =
        is_nothrow_swappable_with<TypeT, OtherT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_SWAPPABLE_WITH_HPP
