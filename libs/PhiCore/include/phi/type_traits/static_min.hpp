#ifndef INCG_PHI_CORE_TYPE_TRAITS_STATIC_MIN_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_STATIC_MIN_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <size_t FirstT, size_t... RestT>
struct static_min;

template <size_t FirstT>
struct static_min<FirstT>
{
    static PHI_CONSTEXPR_AND_CONST size_t value = FirstT;
};

template <size_t FirstT, size_t SecondT, size_t... RestT>
struct static_min<FirstT, SecondT, RestT...>
{
    static const size_t value = FirstT <= SecondT ? static_min<FirstT, RestT...>::value :
                                                    static_min<SecondT, RestT...>::value;
};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <size_t FirstT, size_t... RestT>
PHI_INLINE_VARIABLE constexpr bool static_min_v = static_min<FirstT, RestT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_STATIC_MIN_HPP
