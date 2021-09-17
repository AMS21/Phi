#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/add_lvalue_reference.hpp"
#include "Phi/TypeTraits/conditional.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_referenceable.hpp"
#include "Phi/TypeTraits/is_swappable_with.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_swappable
    : public conditional<is_referenceable<TypeT>::value,
                         is_swappable_with<typename add_lvalue_reference<TypeT>::type,
                                           typename add_lvalue_reference<TypeT>::type>,
                         false_type>::type
{};

template <typename TypeT>
constexpr PHI_INLINE_VARIABLE bool is_swappable_v = is_swappable<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SWAPPABLE_HPP
