#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SIGNED_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_arithmetic.hpp"
#include "Phi/TypeTraits/make_unsafe.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_arithmetic<TypeT>::value>
    struct is_signed_impl : public bool_constant<TypeT(-1) < TypeT(0)>
    {};

    template <typename TypeT>
    struct is_signed_impl<TypeT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_signed : public detail::is_signed_impl<remove_cv_t<make_unsafe_t<TypeT>>>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_signed_v = is_signed<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SIGNED_HPP
