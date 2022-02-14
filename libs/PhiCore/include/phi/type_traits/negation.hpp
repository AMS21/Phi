#ifndef INCG_PHI_CORE_TYPE_TRAITS_NEGATION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_NEGATION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/type_traits/bool_constant.hpp"

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4800) // Implicit conversion from 'x' to bool. Possible information loss

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename BoolT>
struct negation : public bool_constant<!bool(BoolT::value)>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename BoolT>
PHI_INLINE_VARIABLE constexpr bool negation_v = negation<BoolT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_TYPE_TRAITS_NEGATION_HPP
