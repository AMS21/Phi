#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/add_const.hpp"
#include "Phi/TypeTraits/add_lvalue_reference.hpp"
#include "Phi/TypeTraits/is_trivially_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_trivially_copy_assignable
    : public is_trivially_assignable<
              typename add_lvalue_reference<TypeT>::type,
              typename add_lvalue_reference<typename add_const<TypeT>::type>::type>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copy_assignable_v =
        is_trivially_copy_assignable<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
