#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NONE_OF_RCV_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NONE_OF_RCV_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CheckT, typename FirstT, typename... RestT>
struct is_none_of_rcv;

template <typename CheckT, typename FirstT>
struct is_none_of_rcv<CheckT, FirstT> : public is_not_same_rcv<CheckT, FirstT>
{};

template <typename CheckT, typename FirstT, typename SecondT, typename... RestT>
struct is_none_of_rcv<CheckT, FirstT, SecondT, RestT...>
    : public integral_constant<bool, is_same_rcv<CheckT, FirstT>::value ?
                                             false :
                                             is_none_of_rcv<CheckT, SecondT, RestT...>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename CheckT, typename FirstT, typename... RestT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_none_of_rcv_v =
        is_none_of_rcv<CheckT, FirstT, RestT...>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NONE_OF_RCV_HPP
