#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsNothrowDefaultConstructible.hpp"

#if PHI_SUPPORTS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE()

#    include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_default_constructible
    : public bool_constant<PHI_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_default_constructible_v =
        PHI_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE(TypeT);

#    endif

#else

#    include "Phi/TypeTraits/is_nothrow_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_default_constructible : public is_nothrow_constructible<TypeT>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_default_constructible_v =
        is_nothrow_default_constructible<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
