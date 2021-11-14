#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsMemberObjectPointer.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_member_function_pointer.hpp"
#include "Phi/TypeTraits/is_member_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_MEMBER_OBJECT_POINTER()

template <typename TypeT>
struct is_member_object_pointer : public bool_constant<PHI_IS_MEMBER_OBJECT_POINTER(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_member_object_pointer_v = PHI_IS_MEMBER_OBJECT_POINTER(TypeT);

#    endif

#else

template <typename TypeT>
struct is_member_object_pointer
    : bool_constant<is_member_pointer_v<TypeT> && !is_member_function_pointer_v<TypeT>>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_member_object_pointer_v =
        is_member_object_pointer<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
