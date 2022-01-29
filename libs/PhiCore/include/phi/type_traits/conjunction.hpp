#ifndef INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/integral_constant.hpp"

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4800) // Implicit conversion from 'x' to bool. Possible information loss

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename...>
struct conjunction : public true_type
{};

template <typename B1>
struct conjunction<B1> : public B1
{};

template <typename B1, typename... Bn>
struct conjunction<B1, Bn...> : public conditional_t<bool(B1::value), conjunction<Bn...>, B1>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename... B>
PHI_INLINE_VARIABLE constexpr bool conjunction_v = conjunction<B...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP
