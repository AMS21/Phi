#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FLOATING_POINT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FLOATING_POINT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    struct is_unsafe_floating_point_impl : public false_type
    {};

    // Standard C++ floating point types
    template <>
    struct is_unsafe_floating_point_impl<float> : public true_type
    {};

    template <>
    struct is_unsafe_floating_point_impl<double> : public true_type
    {};

    template <>
    struct is_unsafe_floating_point_impl<long double> : public true_type
    {};

#if 0 // TODO:
    // Extended floating point types
#    if PHI_HAS_EXTENSION_FLOAT16()
    template <>
    struct is_unsafe_floating_point_impl<_Float16> : public true_type
    {};
#    endif

#    if PHI_HAS_EXTENSION_FP16()
    template <>
    struct is_unsafe_floating_point_impl<__fp16> : public true_type
    {};
#    endif

#    if PHI_HAS_EXTENSION_FLOAT128()
    template <>
    struct is_unsafe_floating_point_impl<__float128> : public true_type
    {};
#    endif
#endif
} // namespace detail

template <typename TypeT>
struct is_unsafe_floating_point : public detail::is_unsafe_floating_point_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
struct is_not_unsafe_floating_point : public bool_constant<!is_unsafe_floating_point<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_floating_point_v =
        is_unsafe_floating_point<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_unsafe_floating_point_v =
        is_not_unsafe_floating_point<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_FLOATING_POINT_HPP
