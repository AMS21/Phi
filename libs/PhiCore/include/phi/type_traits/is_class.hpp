#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CLASS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CLASS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_class.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_CLASS()

#    define PHI_HAS_WORKING_IS_CLASS() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_class : public bool_constant<PHI_IS_CLASS(TypeT)>
{};

template <typename TypeT>
struct is_not_class : public bool_constant<!PHI_IS_CLASS(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_class_v = PHI_IS_CLASS(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_class_v = !PHI_IS_CLASS(TypeT);

#    endif

#else

#    include "phi/compiler_support/warning.hpp"
#    include "phi/type_traits/detail/yes_no_type.hpp"
#    include "phi/type_traits/is_union.hpp"

#    if PHI_HAS_WORKING_IS_UNION()
#        define PHI_HAS_WORKING_IS_CLASS() 1
#    else
#        define PHI_HAS_WORKING_IS_CLASS() 0
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    yes_type is_class_test(int TypeT::*);

    template <typename TypeT>
    no_type is_class_test(...);
} // namespace detail

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wzero-as-null-pointer-constant")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(5243) // 'x': using incomplete class 'y' can cause potential one definition rule violation due to ABI limitation

template <typename TypeT>
struct is_class
    : public bool_constant<sizeof(detail::is_class_test<TypeT>(0)) == detail::sizeof_yes_type &&
                           is_not_union<TypeT>::value>
{};

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename TypeT>
struct is_not_class : public bool_constant<!is_class<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_class_v = is_class<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_class_v = is_not_class<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CLASS_HPP
