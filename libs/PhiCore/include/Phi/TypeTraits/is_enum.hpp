#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ENUM_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ENUM_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_array.hpp"
#include "Phi/TypeTraits/is_class.hpp"
#include "Phi/TypeTraits/is_floating_point.hpp"
#include "Phi/TypeTraits/is_function.hpp"
#include "Phi/TypeTraits/is_integral.hpp"
#include "Phi/TypeTraits/is_member_pointer.hpp"
#include "Phi/TypeTraits/is_pointer.hpp"
#include "Phi/TypeTraits/is_reference.hpp"
#include "Phi/TypeTraits/is_union.hpp"
#include "Phi/TypeTraits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_ENUM()

template <typename TypeT>
struct is_enum : bool_constant<__is_enum(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_enum_v = __is_enum(TypeT);

#else

template <typename TypeT>
struct is_enum : public bool_constant<!is_void_v<TypeT> && !is_integral_v<TypeT> &&
                                      !is_floating_point_v<TypeT> && !is_array<TypeT> &&
                                      !is_pointer_v<TypeT> && !is_reference_v<TypeT> &&
                                      !is_member_pointer_v<TypeT> && !is_union_v<TypeT> &&
                                      !is_class_v<TypeT> && !is_function_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_enum_v = is_enum<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ENUM_HPP
