#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_TYPE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_safe_bool.hpp"
#include "Phi/TypeTraits/is_safe_floating_point.hpp"
#include "Phi/TypeTraits/is_safe_integer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_safe_type
    : public bool_constant<is_safe_bool_v<TypeT> || is_safe_floating_point_v<TypeT> ||
                           is_safe_integer_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_safe_type_v = is_safe_type<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_TYPE_HPP
