#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_nothrow_move_assignable.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_NOTHROW_MOVE_ASSIGNABLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_move_assignable : public bool_constant<PHI_IS_NOTHROW_MOVE_ASSIGNABLE(TypeT)>
{};

template <typename TypeT>
struct is_not_nothrow_move_assignable : public bool_constant<!PHI_IS_NOTHROW_MOVE_ASSIGNABLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_move_assignable_v =
        PHI_IS_NOTHROW_MOVE_ASSIGNABLE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_nothrow_move_assignable_v =
        !PHI_IS_NOTHROW_MOVE_ASSIGNABLE(TypeT);

#    endif

#else

#    include "phi/type_traits/add_lvalue_reference.hpp"
#    include "phi/type_traits/add_rvalue_reference.hpp"
#    include "phi/type_traits/is_nothrow_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_move_assignable
    : public is_nothrow_assignable<add_lvalue_reference_t<TypeT>, add_rvalue_reference_t<TypeT>>
{};

template <typename TypeT>
struct is_not_nothrow_move_assignable
    : public bool_constant<!is_nothrow_move_assignable<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_move_assignable_v =
        is_nothrow_move_assignable<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_nothrow_move_assignable_v =
        is_not_nothrow_move_assignable<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_MOVE_ASSIGNABLE_HPP
