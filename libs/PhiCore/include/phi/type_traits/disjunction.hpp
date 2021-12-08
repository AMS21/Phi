#ifndef INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/conjunction.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename...>
struct disjunction : public false_type
{};

template <typename B1>
struct disjunction<B1> : B1
{};

template <typename B1, typename... Bn>
struct disjunction<B1, Bn...> : conditional_t<bool(B1::value), B1, disjunction<Bn...>>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename... B>
PHI_INLINE_VARIABLE constexpr bool disjunction_v = disjunction<B...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP
