#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsTriviallyCopyable.hpp"
#include "Phi/TypeTraits/false_t.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_TRIVIALLY_COPYABLE()

template <typename TypeT>
struct is_trivially_copyable : public bool_constant<PHI_IS_TRIVIALLY_COPYABLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copyable_v = PHI_IS_TRIVIALLY_COPYABLE(TypeT);

#    endif

#else

template <typename TypeT>
struct is_trivially_copyable : public false_type
{
    static_assert(false_t<TypeT>::value, "phi::is_trivially_copyable requires compiler support for "
                                         "instrincic __is_trivilly_copyable");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copyable_v = is_trivially_copyable<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
