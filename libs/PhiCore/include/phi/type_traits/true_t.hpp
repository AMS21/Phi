#ifndef INCG_PHI_CORE_TYPE_TRAITS_TRUE_T_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TRUE_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/features.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/bool_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_FEATURE_VARIADIC_TEMPLATES()

template <typename... TypesT>
struct true_t : public bool_constant<true>
{};

#else

template <typename Type0T = void, typename Type1T = void, typename Type2T = void,
          typename Type3T = void, typename Type4T = void, typename Type5T = void,
          typename Type6T = void, typename Type7T = void, typename Type8T = void,
          typename Type9T = void>
struct true_t : public bool_constant<true>
{};

#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename... TypesT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool true_v = true;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_TRUE_T_HPP
