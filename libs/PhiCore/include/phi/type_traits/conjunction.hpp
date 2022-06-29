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

template <typename Bool1T>
struct conjunction<Bool1T> : public Bool1T
{};

template <typename Bool1T, typename... BoolsT>
struct conjunction<Bool1T, BoolsT...>
    : public conditional_t<bool(Bool1T::value), conjunction<BoolsT...>, Bool1T>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename... BoolsT>
PHI_INLINE_VARIABLE constexpr bool conjunction_v = conjunction<BoolsT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPE_TRAITS_CONJUNCTION_HPP
