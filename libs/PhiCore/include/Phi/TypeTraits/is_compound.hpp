#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsCompound.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_COMPOUND()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_compound : public bool_constant<PHI_IS_COMPOUND(TypeT)>
{};

template <typename TypeT>
struct is_not_compound : public bool_constant<!PHI_IS_COMPOUND(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_compound_v = PHI_IS_COMPOUND(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_compound_v = !PHI_IS_COMPOUND(TypeT);

#    endif

#else

#    include "Phi/TypeTraits/is_unsafe_fundamental.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_compound : public bool_constant<!is_unsafe_fundamental<TypeT>::value>
{};

template <typename TypeT>
struct is_not_compound : public bool_constant<is_unsafe_fundamental<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_compound_v = is_compound<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_compound_v = is_not_compound<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COMPOUND_HPP
