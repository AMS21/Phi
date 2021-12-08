#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_VOID_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_void.hpp"

#if PHI_SUPPORTS_IS_VOID()

#    include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_void : public bool_constant<PHI_IS_VOID(TypeT)>
{};

template <typename TypeT>
struct is_not_void : public bool_constant<!PHI_IS_VOID(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_void_v = PHI_IS_VOID(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_void_v = !PHI_IS_VOID(TypeT);

#    endif

#else

#    include "phi/type_traits/is_same.hpp"
#    include "phi/type_traits/remove_cv.hpp"

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
