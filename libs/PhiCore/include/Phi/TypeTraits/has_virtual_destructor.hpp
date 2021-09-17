#ifndef INCG_PHI_CORE_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_HAS_VIRTUAL_DESTRUCTOR()

template <typename TypeT>
struct has_virtual_destructor : public bool_constant<__has_virtual_destructor(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool has_virtual_destructor_v = __has_virtual_destructor(TypeT);

#else

template <typename TypeT>
struct has_virtual_destructor : public false_type
{
    static_assert(always_false<TypeT>, "phi::has_virtual_destructor requires compiler support for "
                                       "intrinsic has_virtual_destructor");
};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool has_virtual_destructor_v = has_virtual_destructor<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_HAS_VIRTUAL_DESTRUCTOR_HPP
