#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_compound.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_COMPOUND()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_compound : public integral_constant<bool, PHI_IS_COMPOUND(TypeT)>
{};

template <typename TypeT>
struct is_not_compound : public integral_constant<bool, !PHI_IS_COMPOUND(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_compound_v = PHI_IS_COMPOUND(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_compound_v = !PHI_IS_COMPOUND(TypeT);

#    endif

#else

#    include "phi/type_traits/is_unsafe_fundamental.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_compound : public integral_constant<bool, !is_unsafe_fundamental<TypeT>::value>
{};

template <typename TypeT>
struct is_not_compound : public integral_constant<bool, is_unsafe_fundamental<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_compound_v = is_compound<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_compound_v = is_not_compound<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP
