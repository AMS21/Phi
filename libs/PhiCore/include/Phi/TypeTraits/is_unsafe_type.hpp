#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_TYPE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_unsafe_bool.hpp"
#include "Phi/TypeTraits/is_unsafe_floating_point.hpp"
#include "Phi/TypeTraits/is_unsafe_integer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_type
    : public bool_constant<is_unsafe_bool_v<TypeT> || is_unsafe_floating_point_v<TypeT> ||
                           is_unsafe_integer_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_type_v = is_unsafe_type<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_TYPE_HPP
