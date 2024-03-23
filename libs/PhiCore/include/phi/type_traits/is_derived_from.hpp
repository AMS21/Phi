#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_DERIVED_FROM_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_DERIVED_FROM_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_base_of.hpp"
#include "phi/type_traits/is_convertible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_WORKING_IS_BASE_OF()
#    define PHI_HAS_WORKING_IS_DERIVED_FROM() 1
#else
#    define PHI_HAS_WORKING_IS_DERIVED_FROM() 0
#endif

template <typename DerivedT, typename BaseT>
struct is_derived_from
    : public integral_constant<
              bool, is_base_of<BaseT, DerivedT>::value &&
                            is_convertible<const volatile DerivedT*, const volatile BaseT*>::value>
{};

template <typename DerivedT, typename BaseT>
struct is_not_derived_from
    : public integral_constant<bool, !is_derived_from<DerivedT, BaseT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename DerivedT, typename BaseT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_derived_from_v = is_derived_from<DerivedT, BaseT>::value;

template <typename DerivedT, typename BaseT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_derived_from_v =
        is_not_derived_from<DerivedT, BaseT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_DERIVED_FROM_HPP
