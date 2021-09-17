#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_safe_integer.hpp"
#include "Phi/TypeTraits/is_unsafe_integer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_integer : public bool_constant<is_safe_integer_v<TypeT> || is_unsafe_integer_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_integer_v = is_integer<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_INTEGER_HPP
