#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_OR_UNBOUNDED_VOID_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_OR_UNBOUNDED_VOID_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_complete.hpp"
#include "phi/type_traits/is_unbounded_array.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_complete_or_unbounded_void
    : public bool_constant<is_complete<TypeT>::value || is_void<TypeT>::value ||
                           is_unbounded_array<TypeT>::value>
{};

template <typename TypeT>
struct is_not_complete_or_unbounded_void
    : public bool_constant<!is_complete_or_unbounded_void<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_complete_or_unbounded_void_v =
        is_complete_or_unbounded_void<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_complete_or_unbounded_void_v =
        is_not_complete_or_unbounded_void<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_OR_UNBOUNDED_VOID_HPP
