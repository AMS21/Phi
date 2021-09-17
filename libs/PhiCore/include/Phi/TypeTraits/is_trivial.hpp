#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_trivially_copyable.hpp"
#include "Phi/TypeTraits/is_trivially_default_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_TRIVIAL()

template <typename TypeT>
struct is_trivial : public bool_constant<__is_trivial(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivial_v = __is_trivial(TypeT);

#else

template <typename TypeT>
struct is_trivial : public bool_constant<is_trivially_copyable_v<TypeT> &&
                                         is_trivially_default_constructible_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivial_v = is_trivial<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP
