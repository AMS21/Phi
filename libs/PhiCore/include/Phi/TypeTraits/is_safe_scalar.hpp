#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_SCALAR_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_SCALAR_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_enum.hpp"
#include "Phi/TypeTraits/is_member_pointer.hpp"
#include "Phi/TypeTraits/is_null_pointer.hpp"
#include "Phi/TypeTraits/is_pointer.hpp"
#include "Phi/TypeTraits/is_safe_arithmetic.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_safe_scalar
    : public bool_constant<is_safe_arithmetic<TypeT>::value || is_enum<TypeT>::value ||
                           is_pointer<TypeT>::value || is_member_pointer<TypeT>::value ||
                           is_null_pointer<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_safe_scalar_v = is_safe_scalar<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_SCALAR_HPP
