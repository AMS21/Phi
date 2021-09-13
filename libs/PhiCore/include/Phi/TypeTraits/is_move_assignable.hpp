#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/add_lvalue_reference.hpp"
#include "Phi/TypeTraits/add_rvalue_reference.hpp"
#include "Phi/TypeTraits/is_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_move_assignable
    : public is_assignable<add_lvalue_reference_t<TypeT>, add_rvalue_reference_t<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_move_assignable_v = is_move_assignable<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_MOVE_ASSIGNABLE_HPP
