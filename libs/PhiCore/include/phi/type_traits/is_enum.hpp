#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ENUM_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ENUM_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_enum.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_ENUM()

#    define PHI_HAS_WORKING_IS_ENUM() 1

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

#    include "phi/type_traits/is_array.hpp"
#    include "phi/type_traits/is_class.hpp"
#    include "phi/type_traits/is_function.hpp"
#    include "phi/type_traits/is_member_pointer.hpp"
#    include "phi/type_traits/is_null_pointer.hpp"
#    include "phi/type_traits/is_pointer.hpp"
#    include "phi/type_traits/is_reference.hpp"
#    include "phi/type_traits/is_union.hpp"
#    include "phi/type_traits/is_unsafe_floating_point.hpp"
#    include "phi/type_traits/is_unsafe_integral.hpp"
#    include "phi/type_traits/is_void.hpp"

#    if PHI_HAS_WORKING_IS_UNION()
#        define PHI_HAS_WORKING_IS_ENUM() 1
#    else
#        define PHI_HAS_WORKING_IS_ENUM() 0
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_enum
    : public bool_constant<is_not_array<TypeT>::value && is_not_class<TypeT>::value &&
                           is_not_function<TypeT>::value && is_not_member_pointer<TypeT>::value &&
                           is_not_null_pointer<TypeT>::value && is_not_pointer<TypeT>::value &&
                           is_not_reference<TypeT>::value && is_not_union<TypeT>::value &&
                           is_not_unsafe_floating_point<TypeT>::value &&
                           is_not_unsafe_integral<TypeT>::value && is_not_void<TypeT>::value>
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
