#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_trivially_destructible.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_HAS_INTRINSIC_IS_TRIVIALLY_DESTRUCTIBLE()

#    define PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_trivially_destructible : public bool_constant<__is_trivially_destructible(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_destructible_v = __is_trivially_destructible(TypeT);

#    endif

#elif PHI_HAS_INTRINSIC_HAS_TRIVIAL_DESTRUCTOR()

#    include "phi/type_traits/is_destructible.hpp"

#    define PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_trivially_destructible
    : public bool_constant<is_destructible<TypeT>::value&& __has_trivial_destructor(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_destructible_v =
        is_trivially_destructible<TypeT>::value;

#    endif

#else

#    include "phi/type_traits/is_reference.hpp"
#    include "phi/type_traits/is_scalar.hpp"
#    include "phi/type_traits/remove_all_extents.hpp"

#    define PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE() PHI_HAS_WORKING_IS_SCALAR()

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    struct is_trivially_destructible_impl
        : bool_constant<is_scalar<TypeT>::value || is_reference<TypeT>::value>
    {};
} // namespace detail

template <typename TypeT>
struct is_trivially_destructible
    : public detail::is_trivially_destructible_impl<remove_all_extents_t<TypeT>>
{};

template <typename TypeT>
struct is_trivially_destructible<TypeT[]> : public false_type
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_destructible_v =
        is_trivially_destructible<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
