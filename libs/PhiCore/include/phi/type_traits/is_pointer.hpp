#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/// \cond detail
namespace detail
{
    template <typename TypeT>
    struct is_pointer_impl : public false_type
    {};

    template <typename TypeT>
    struct is_pointer_impl<TypeT*> : public true_type
    {};
} // namespace detail
/// \endcond

template <typename TypeT>
struct is_pointer : public detail::is_pointer_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
struct is_not_pointer : public bool_constant<!is_pointer<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_pointer_v = is_pointer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_pointer_v = is_not_pointer<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_HPP
