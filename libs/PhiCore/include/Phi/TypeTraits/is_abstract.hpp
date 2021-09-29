#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_ABSTRACT()

template <typename TypeT>
struct is_abstract : public bool_constant<__is_abstract(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_abstract_v = __is_abstract(TypeT);

#    endif
#else

template <typename TypeT>
struct is_abstract : public false_type
{
    static_assert(always_false<TypeT>, "phi::is_abstract requires compiler support");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_abstract_v = is_abstract<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_ABSTRACT_HPP
