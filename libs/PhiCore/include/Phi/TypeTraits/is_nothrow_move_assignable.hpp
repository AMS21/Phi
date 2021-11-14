#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/CompilerSupport/Intrinsics/IsNothrowMoveAssignable.hpp"

#if PHI_SUPPORTS_IS_NOTHROW_MOVE_ASSIGNABLE()

#    include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_move_assignable : public bool_constant<PHI_IS_NOTHROW_MOVE_ASSIGNABLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_move_assignable_v =
        PHI_IS_NOTHROW_MOVE_ASSIGNABLE(TypeT);

#    endif

#else

#    include "Phi/TypeTraits/add_lvalue_reference.hpp"
#    include "Phi/TypeTraits/add_rvalue_reference.hpp"
#    include "Phi/TypeTraits/is_nothrow_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_move_assignable
    : public is_nothrow_assignable<add_lvalue_reference_t<TypeT>, add_rvalue_reference_t<TypeT>>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_move_assignable_v =
        is_nothrow_move_assignable<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP
