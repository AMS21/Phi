#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsTriviallyDestructible.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_destructible.hpp"
#include "Phi/TypeTraits/is_reference.hpp"
#include "Phi/TypeTraits/is_scalar.hpp"
#include "Phi/TypeTraits/remove_all_extents.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_TRIVIALLY_DESTRUCTIBLE()

template <typename TypeT>
struct is_trivially_destructible : public bool_constant<PHI_IS_TRIVIALLY_DESTRUCTIBLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_destructible_v =
        PHI_IS_TRIVIALLY_DESTRUCTIBLE(TypeT);

#    endif

#elif PHI_HAS_INTRINSIC_HAS_TRIVIAL_DESTRUCTOR()

template <typename TypeT>
struct is_trivially_destructible
    : public bool_constant<is_destructible_v<TypeT>&& __has_trivial_destructor(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_destructible_v =
        is_trivially_destructible<TypeT>::value;

#    endif

#else

namespace detail
{
    template <typename TypeT>
    struct is_trivially_destructible_impl
        : bool_constant<is_scalar_v<TypeT> || is_reference_v<TypeT>>
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
