#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_function.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_FUNCTION()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_function : public bool_constant<PHI_IS_FUNCTION(TypeT)>
{};

template <typename TypeT>
struct is_not_function : public bool_constant<!PHI_IS_FUNCTION(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_function_v = PHI_IS_FUNCTION(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_function_v = !PHI_IS_FUNCTION(TypeT);

#    endif

#else

#    include "phi/type_traits/is_const.hpp"
#    include "phi/type_traits/is_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_function
    : public bool_constant<!is_const<const TypeT>::value && !is_reference<TypeT>::value>
{};

template <typename TypeT>
struct is_not_function : public bool_constant<!is_function<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_function_v = is_function<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_function_v = is_not_function<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_HPP
