#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_OR_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_OR_POINTER_HPP

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_null_pointer.hpp"
#include "Phi/TypeTraits/is_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_null_pointer_or_pointer
    : public bool_constant<is_null_pointer<TypeT>::value || is_pointer<TypeT>::value>
{};

template <typename TypeT>
struct is_not_null_pointer_or_pointer
    : public bool_constant<!is_null_pointer_or_pointer<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_null_pointer_or_pointer_v =
        is_null_pointer_or_pointer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_null_pointer_or_pointer_v =
        is_not_null_pointer_or_pointer<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NULL_POINTER_OR_POINTER_HPP
