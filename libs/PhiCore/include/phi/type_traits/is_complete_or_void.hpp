#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_OR_VOID_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_OR_VOID_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_complete.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_complete_or_void
    : public bool_constant<is_complete<TypeT>::value || is_void<TypeT>::value>
{};

template <typename TypeT>
struct is_not_complete_or_void : public bool_constant<!is_complete_or_void<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_complete_or_void_v = is_complete_or_void<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_complete_or_void_v =
        is_not_complete_or_void<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COMPLETE_OR_VOID_HPP
