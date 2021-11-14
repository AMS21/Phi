#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsFinal.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_FINAL()

template <typename TypeT>
struct is_final : public bool_constant<PHI_IS_FINAL(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_final_v = PHI_IS_FINAL(TypeT);

#    endif

#else

template <typename TypeT>
struct is_final : public false_type
{
    static_assert(always_false<TypeT>,
                  "phi::is_final requires compiler support for intrinsic __is_final");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_final_v = is_final<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FINAL_HPP
