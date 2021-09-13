#ifndef INCG_PHI_CORE_TYPE_TRAITS_NEGATION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_NEGATION_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename BoolT>
struct negation : bool_constant<!bool(BoolT::value)>
{};

template <typename BoolT>
PHI_INLINE_VARIABLE constexpr bool negation_v = negation<BoolT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_NEGATION_HPP
