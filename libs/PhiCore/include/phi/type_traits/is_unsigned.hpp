#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSIGNED_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSIGNED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_unsafe_arithmetic.hpp"
#include "phi/type_traits/make_unsafe.hpp"
#include "phi/type_traits/remove_cv.hpp"

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4296) // warning C4296: '<': expression is always false

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TypeT, bool = is_unsafe_arithmetic<TypeT>::value>
    struct is_unsigned_impl : public integral_constant<bool, TypeT(0) < TypeT(-1)>
    {};

    template <typename TypeT>
    struct is_unsigned_impl<TypeT, false> : public false_type
    {};
} // namespace detail
/// \endcond

template <typename TypeT>
struct is_unsigned : public detail::is_unsigned_impl<remove_cv_t<make_unsafe_t<TypeT>>>
{};

template <typename TypeT>
struct is_not_unsigned : public integral_constant<bool, !is_unsigned<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_unsigned_v = is_unsigned<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_unsigned_v = is_not_unsigned<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSIGNED_HPP
