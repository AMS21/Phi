#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_default_constructible : public is_constructible<TypeT>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_default_constructible_v =
        is_default_constructible<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
