#ifndef INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/bool_pack.hpp"
#include "Phi/TypeTraits/is_same.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool... Bs>
using conjunction = is_same<bool_pack<true, Bs...>, bool_pack<Bs..., true>>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP
