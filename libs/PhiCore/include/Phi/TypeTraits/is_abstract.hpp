#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsAbstract.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_ABSTRACT()

template <typename TypeT>
struct is_abstract : public bool_constant<PHI_IS_ABSTRACT(TypeT)>
{};

template <typename TypeT>
struct is_not_abstract : public bool_constant<!PHI_IS_ABSTRACT(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_abstract_v = PHI_IS_ABSTRACT(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_abstract_v = !PHI_IS_ABSTRACT(TypeT);

#    endif
#else

template <typename TypeT>
struct is_abstract : public false_type
{
    static_assert(always_false<TypeT>::value, "phi::is_abstract requires compiler support");
};

template <typename TypeT>
struct is_not_abstract : public false_type
{
    static_assert(always_false<TypeT>::value, "phi::is_not_abstract requires compiler support");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_abstract_v = is_abstract<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_abstract_v = is_not_abstract<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP
