#ifndef INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/conjunction.hpp"
#include "phi/type_traits/integral_constant.hpp"

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4800) // Implicit conversion from 'x' to bool. Possible information loss

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename...>
struct disjunction : public false_type
{};

template <typename Boolean1T>
struct disjunction<Boolean1T> : public Boolean1T
{};

template <typename Boolean1T, typename... BooleanNT>
struct disjunction<Boolean1T, BooleanNT...>
    : public conditional_t<bool(Boolean1T::value), Boolean1T, disjunction<BooleanNT...>>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename... BooleansT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool disjunction_v = disjunction<BooleansT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DISJUNCTION_HPP
