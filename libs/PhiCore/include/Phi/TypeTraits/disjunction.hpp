#ifndef INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/conjunction.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool... Bs>
struct disjunction : bool_constant<!conjunction<!Bs...>::value>
{};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP
