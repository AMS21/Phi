#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_VOID() && PHI_HAS_KEYWORD(__is_void)

template <typename TypeT>
struct is_void : public bool_constant<__is_void(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_void_v = __is_void(TypeT);

#else

template <typename TypeT>
struct is_void : public is_same<void, typename remove_cv<TypeT>::type>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_void_v = is_void<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
