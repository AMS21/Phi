#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_SIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_SIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_unsafe_arithmetic.hpp"

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4296) // warning C4296: '<': expression is always false

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_unsafe_arithmetic<TypeT>::value>
    struct is_unsafe_signed_impl : public bool_constant<TypeT(-1) < TypeT(0)>
    {};

    template <typename TypeT>
    struct is_unsafe_signed_impl<TypeT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_unsafe_signed : public detail::is_unsafe_signed_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
struct is_not_unsafe_signed : public bool_constant<!is_unsafe_signed<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_unsafe_signed_v = is_unsafe_signed<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_unsafe_signed_v = is_not_unsafe_signed<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_SIGNED_HPP
