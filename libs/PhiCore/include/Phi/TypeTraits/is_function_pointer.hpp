#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_function.hpp"
#include "Phi/TypeTraits/remove_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_function_pointer
    : public bool_constant<is_not_function<TypeT>::value &&
                           is_function<typename remove_pointer<TypeT>::type>::value>
{};

template <typename TypeT>
struct is_not_function_pointer : public bool_constant<!is_function_pointer<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_function_pointer_v = is_function_pointer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_function_pointer_v =
        is_not_function_pointer<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_POINTER_HPP
