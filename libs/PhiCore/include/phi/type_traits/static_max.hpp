#ifndef INCG_PHI_CORE_TYPE_TRAITS_STATIC_MAX_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_STATIC_MAX_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/core/size_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <size_t FirstT, size_t... RestT>
struct static_max;

template <size_t FirstT>
struct static_max<FirstT>
{
    static PHI_CONSTEXPR_AND_CONST size_t value = FirstT;
};

template <size_t FirstT, size_t SecondT, size_t... RestT>
struct static_max<FirstT, SecondT, RestT...>
{
    static const size_t value = FirstT >= SecondT ? static_max<FirstT, RestT...>::value :
                                                    static_max<SecondT, RestT...>::value;
};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <size_t FirstT, size_t... RestT>
PHI_INLINE_VARIABLE constexpr bool static_max_v = static_max<FirstT, RestT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_STATIC_MAX_HPP
