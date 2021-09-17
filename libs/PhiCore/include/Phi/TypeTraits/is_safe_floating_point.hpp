#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_FLOATING_POINT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_FLOATING_POINT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class FloatingPoint;

namespace detail
{
    template <typename TypeT>
    struct is_safe_floating_point_impl : public false_type
    {};

    template <typename TypeT>
    struct is_safe_floating_point_impl<FloatingPoint<TypeT>> : public true_type
    {};
} // namespace detail

template <typename TypeT>
struct is_safe_floating_point : public detail::is_safe_floating_point_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_safe_floating_point_v = is_safe_floating_point<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_FLOATING_POINT_HPP
