#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_OBJECT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_OBJECT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if !PHI_HAS_INTRINSIC_IS_OBJECT()
#    include "Phi/TypeTraits/is_array.hpp"
#    include "Phi/TypeTraits/is_class.hpp"
#    include "Phi/TypeTraits/is_scalar.hpp"
#    include "Phi/TypeTraits/is_union.hpp"
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_OBJECT()

template <typename TypeT>
struct is_object : public bool_constant<__is_object(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_object_v = __is_object(TypeT);

#    endif

#else

template <typename TypeT>
struct is_object : public bool_constant<is_scalar_v<TypeT> || is_array_v<TypeT> ||
                                        is_union_v<TypeT> || is_class_v<TypeT>>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_object_v = is_object<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_OBJECT_HPP
