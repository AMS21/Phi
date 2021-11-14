#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Config/Compiler.hpp"

#if PHI_HAS_INTRINSIC_IS_VOID() && PHI_HAS_KEYWORD(__is_void)

#    include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_void : public bool_constant<__is_void(TypeT)>
{};

template <typename TypeT>
struct is_not_void : public bool_constant<!__is_void(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_void_v = __is_void(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_void_v = !__is_void(TypeT);

#    endif

#else

#    include "Phi/TypeTraits/is_same.hpp"
#    include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_void : public is_same<void, typename remove_cv<TypeT>::type>
{};

template <typename TypeT>
struct is_not_void : public is_not_same<void, typename remove_cv<TypeT>::type>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_void_v = is_void<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_void_v = is_not_void<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
