#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/TypeTraits/always_false.hpp"
#include "Phi/TypeTraits/detail/yes_no_type.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// GCCs implementation of of __is_constructible is bugged
// See: TODO insert link
#if PHI_HAS_INTRINSIC_IS_CONSTRUCTIBLE() && PHI_COMPILER_IS_NOT(GCC)

template <typename TypeT, typename... ArgsT>
struct is_constructible : public bool_constant<__is_constructible(TypeT, ArgsT...)>
{};

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_constructible_v = __is_constructible(TypeT, ArgsT...);

#else

template <typename TypeT, typename... ArgsT>
PHI_INLINE_VARIABLE constexpr bool is_constructible_v = is_constructible<TypeT, ArgsT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
