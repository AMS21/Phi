#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RC_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RC_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/remove_const.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT>
struct is_same_rc : public is_same<remove_const_t<LhsT>, remove_const_t<RhsT>>
{};

template <typename LhsT, typename RhsT>
struct is_not_same_rc : public is_not_same<remove_const_t<LhsT>, remove_const_t<RhsT>>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE constexpr bool is_same_rc_v = is_same_rc<LhsT, RhsT>::value;

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE constexpr bool is_not_same_rc_v = is_not_same_rc<LhsT, RhsT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RC_HPP
