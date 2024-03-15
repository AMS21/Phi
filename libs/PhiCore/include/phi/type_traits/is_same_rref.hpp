#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RREF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RREF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT>
struct is_same_rref : public is_same<remove_reference_t<LhsT>, remove_reference_t<RhsT>>
{};

template <typename LhsT, typename RhsT>
struct is_not_same_rref : public bool_constant<!is_same_rref<LhsT, RhsT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_same_rref_v = is_same_rref<LhsT, RhsT>::value;

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_same_rref_v = is_not_same_rref<LhsT, RhsT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RREF_HPP
