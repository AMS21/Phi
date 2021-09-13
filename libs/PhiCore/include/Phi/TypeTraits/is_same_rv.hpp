#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RV_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RV_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/remove_volatile.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT>
struct is_same_rv : public is_same<remove_volatile_t<LhsT>, remove_volatile_t<RhsT>>
{};

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE constexpr bool is_same_rv_v = is_same_rv<LhsT, RhsT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RV_HPP
