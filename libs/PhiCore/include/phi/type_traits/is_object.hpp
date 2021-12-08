#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_OBJECT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_OBJECT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_object.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_OBJECT()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_object : public bool_constant<PHI_IS_OBJECT(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_object_v = PHI_IS_OBJECT(TypeT);

#    endif

#else

#    include "phi/type_traits/is_array.hpp"
#    include "phi/type_traits/is_class.hpp"
#    include "phi/type_traits/is_scalar.hpp"
#    include "phi/type_traits/is_union.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_object : public bool_constant<is_scalar<TypeT>::value || is_array<TypeT>::value ||
                                        is_union<TypeT>::value || is_class<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_object_v = is_object<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_OBJECT_HPP
