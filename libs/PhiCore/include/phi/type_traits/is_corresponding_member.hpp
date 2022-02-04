#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CORRESPONDIG_MEMBER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CORRESPONDIG_MEMBER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/intrinsics/is_corresponding_member.hpp"
#include "phi/compiler_support/nodiscard.hpp"

#if PHI_SUPPORTS_IS_CORRESPONDIG_MEMBER()

#    define PHI_HAS_WORKING_IS_CORRESPONDIG_MEMBER() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT, typename LhsMemberT, typename RhsMemberT>
PHI_NODISCARD constexpr bool is_corresponding_member(LhsMemberT LhsT::*lhs,
                                                     RhsMemberT RhsT::*rhs) noexcept
{
    return __builtin_is_corresponding_member(lhs, rhs);
}

#else

#    include "phi/compiler_support/unused.hpp"
#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_CORRESPONDIG_MEMBER() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT, typename LhsMemberT, typename RhsMemberT>
PHI_NODISCARD constexpr bool is_corresponding_member(LhsMemberT LhsT::*lhs,
                                                     RhsMemberT RhsT::*rhs) noexcept
{
    static_assert(false_t<LhsT>::value, "phi::is_correspondig_member requires compiler support");
    PHI_UNUSED_PARAMETER(lhs);
    PHI_UNUSED_PARAMETER(rhs);

    return false;
}

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CORRESPONDIG_MEMBER_HPP
