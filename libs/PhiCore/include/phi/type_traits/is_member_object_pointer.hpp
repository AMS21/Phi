#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_member_object_pointer.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_MEMBER_OBJECT_POINTER()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_member_object_pointer : public bool_constant<PHI_IS_MEMBER_OBJECT_POINTER(TypeT)>
{};

template <typename TypeT>
struct is_not_member_object_pointer : public bool_constant<!PHI_IS_MEMBER_OBJECT_POINTER(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_member_object_pointer_v = PHI_IS_MEMBER_OBJECT_POINTER(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_member_object_pointer_v =
        !PHI_IS_MEMBER_OBJECT_POINTER(TypeT);

#    endif

#else

#    include "phi/type_traits/is_member_function_pointer.hpp"
#    include "phi/type_traits/is_member_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_member_object_pointer : public bool_constant<is_member_pointer<TypeT>::value &&
                                                       !is_member_function_pointer<TypeT>::value>
{};

template <typename TypeT>
struct is_not_member_object_pointer : public bool_constant<!is_member_object_pointer<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_member_object_pointer_v =
        is_member_object_pointer<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_member_object_pointer_v =
        is_not_member_object_pointer<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
