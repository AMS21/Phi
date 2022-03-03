#ifndef INCG_PHI_CORE_TYPE_TRAITS_STATIC_MIN_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_STATIC_MIN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4296) // 'op' expression is always false/true

template <size_t FirstV, size_t... RestVs>
struct static_min;

template <size_t FirstV>
struct static_min<FirstV> : public integral_constant<size_t, FirstV>
{};

template <size_t FirstV, size_t SecondT, size_t... RestVs>
struct static_min<FirstV, SecondT, RestVs...>
    : public integral_constant<size_t, FirstV <= SecondT ? static_min<FirstV, RestVs...>::value :
                                                           static_min<SecondT, RestVs...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <size_t FirstV, size_t... RestVs>
PHI_INLINE_VARIABLE constexpr size_t static_min_v = static_min<FirstV, RestVs...>::value;

#endif

PHI_MSVC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_STATIC_MIN_HPP
