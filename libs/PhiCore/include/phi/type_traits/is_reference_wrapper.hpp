#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/remove_cv.hpp"
#include <functional>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    struct is_reference_wrapper_impl : public false_type
    {};

    template <typename TypeT>
    struct is_reference_wrapper_impl<std::reference_wrapper<TypeT>> : public true_type
    {};
} // namespace detail

template <typename TypeT>
struct is_reference_wrapper
    : public detail::is_reference_wrapper_impl<typename remove_cv<TypeT>::type>
{};

template <typename TypeT>
struct is_not_reference_wrapper : public bool_constant<!is_reference_wrapper<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_reference_wrapper_v = is_reference_wrapper<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_reference_wrapper_v =
        is_not_reference_wrapper<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_REFERENCE_WRAPPER_HPP
