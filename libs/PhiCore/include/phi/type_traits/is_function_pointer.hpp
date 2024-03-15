#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_POINTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_function.hpp"
#include "phi/type_traits/remove_pointer.hpp"

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
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_function_pointer_v = is_function_pointer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_function_pointer_v =
        is_not_function_pointer<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_POINTER_HPP
