#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_UNSIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_UNSIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_safe_arithmetic.hpp"
#include "phi/type_traits/remove_cv.hpp"

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4296) // warning C4296: '<': expression is always false

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_safe_arithmetic<TypeT>::value>
    struct is_safe_unsigned_impl
        : public integral_constant<bool,
                                   typename TypeT::value_type(0) < typename TypeT::value_type(-1)>
    {};

    template <typename TypeT>
    struct is_safe_unsigned_impl<TypeT, false> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_safe_unsigned : public detail::is_safe_unsigned_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
struct is_not_safe_unsigned : public integral_constant<bool, !is_safe_unsigned<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_safe_unsigned_v = is_safe_unsigned<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_safe_unsigned_v = is_not_safe_unsigned<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_UNSIGNED_HPP
