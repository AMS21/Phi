#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ENUM_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ENUM_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsEnum.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_ENUM()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_enum : public bool_constant<PHI_IS_ENUM(TypeT)>
{};

template <typename TypeT>
struct is_not_enum : public bool_constant<!PHI_IS_ENUM(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_enum_v = PHI_IS_ENUM(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_enum_v = !PHI_IS_ENUM(TypeT);

#    endif

#else

#    include "Phi/TypeTraits/is_array.hpp"
#    include "Phi/TypeTraits/is_class.hpp"
#    include "Phi/TypeTraits/is_floating_point.hpp"
#    include "Phi/TypeTraits/is_function.hpp"
#    include "Phi/TypeTraits/is_integral.hpp"
#    include "Phi/TypeTraits/is_member_pointer.hpp"
#    include "Phi/TypeTraits/is_pointer.hpp"
#    include "Phi/TypeTraits/is_reference.hpp"
#    include "Phi/TypeTraits/is_union.hpp"
#    include "Phi/TypeTraits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_enum : public bool_constant<!is_void<TypeT>::value && !is_integral<TypeT>::value &&
                                      !is_floating_point<TypeT>::value && !is_array<TypeT>::value &&
                                      !is_pointer<TypeT>::value && !is_reference<TypeT>::value &&
                                      !is_member_pointer<TypeT>::value && !is_union<TypeT>::value &&
                                      !is_class<TypeT>::value && !is_function<TypeT>::value>
{};

template <typename TypeT>
struct is_not_enum : public bool_constant<!is_enum<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_enum_v = is_enum<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_enum_v = is_not_enum<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ENUM_HPP
