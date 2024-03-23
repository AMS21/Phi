#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_unsafe_arithmetic.hpp"
#include "phi/type_traits/make_unsafe.hpp"
#include "phi/type_traits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4296) // warning C4296: '<': expression is always false

namespace detail
{
    template <typename TypeT, bool = is_unsafe_arithmetic<TypeT>::value>
    struct is_signed_impl : public integral_constant<bool, TypeT(-1) < TypeT(0)>
    {};

    template <typename TypeT>
    struct is_signed_impl<TypeT, false> : public false_type
    {};
} // namespace detail

PHI_MSVC_SUPPRESS_WARNING_POP()

template <typename TypeT>
struct is_signed : public detail::is_signed_impl<remove_cv_t<make_unsafe_t<TypeT>>>
{};

template <typename TypeT>
struct is_not_signed : public integral_constant<bool, !is_signed<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_signed_v = is_signed<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_signed_v = is_not_signed<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SIGNED_HPP
