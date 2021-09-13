#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FUNDAMENTAL_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_arithmetic.hpp"
#include "Phi/TypeTraits/is_null_pointer.hpp"
#include "Phi/TypeTraits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_fundamental
    : public bool_constant<is_void_v<TypeT> || is_null_pointer_v<TypeT> || is_arithmetic_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_fundamental_v = is_fundamental<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
