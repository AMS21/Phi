#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CLASS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CLASS_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsClass.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_CLASS()

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

#    include "Phi/TypeTraits/detail/yes_no_type.hpp"
#    include "Phi/TypeTraits/is_union.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    yes_type is_class_test(int TypeT::*);

    template <typename TypeT>
    no_type is_class_test(...);
} // namespace detail

template <typename TypeT>
struct is_class
    : public bool_constant<sizeof(detail::is_class_test<TypeT>(0)) == detail::sizeof_yes_type &&
                           is_not_union<TypeT>::value>
{};

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
