#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unsafe_bool : public is_same_rcv<TypeT, bool>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_bool_v = is_unsafe_bool<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_BOOL_HPP
