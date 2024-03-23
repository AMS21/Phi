#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_rvalue_reference.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_RVALUE_REFERENCE()

template <typename TypeT>
struct is_rvalue_reference : public integral_constant<bool, PHI_IS_RVALUE_REFERENCE(TypeT)>
{};

template <typename TypeT>
struct is_not_rvalue_reference : public integral_constant<bool, !PHI_IS_RVALUE_REFERENCE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_rvalue_reference_v = PHI_IS_RVALUE_REFERENCE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_rvalue_reference_v = !PHI_IS_RVALUE_REFERENCE(TypeT);

#    endif

#else

template <typename TypeT>
struct is_rvalue_reference : public false_type
{};

template <typename TypeT>
struct is_rvalue_reference<TypeT&&> : public true_type
{};

template <typename TypeT>
struct is_not_rvalue_reference : public integral_constant<bool, !is_rvalue_reference<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_rvalue_reference_v = is_rvalue_reference<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_rvalue_reference_v =
        is_not_rvalue_reference<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
