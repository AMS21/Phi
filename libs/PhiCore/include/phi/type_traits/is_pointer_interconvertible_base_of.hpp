#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_pointer_interconvertible_base_of.hpp"
#include "phi/type_traits/bool_constant.hpp"

#if PHI_SUPPORTS_IS_POINTER_INTERCONVERTIBLE_BASE_OF()

#    define PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_BASE_OF() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename BaseT, typename DerivedT>
struct is_pointer_interconvertible_base_of
    : public bool_constant<PHI_IS_POINTER_INTERCONVERTIBLE_BASE_OF(BaseT, DerivedT)>
{};

template <typename BaseT, typename DerivedT>
struct is_not_pointer_interconvertible_base_of
    : public bool_constant<!PHI_IS_POINTER_INTERCONVERTIBLE_BASE_OF(BaseT, DerivedT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename BaseT, typename DerivedT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_pointer_interconvertible_base_of_v =
        PHI_IS_POINTER_INTERCONVERTIBLE_BASE_OF(BaseT, DerivedT);

template <typename BaseT, typename DerivedT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_pointer_interconvertible_base_of_v =
        !PHI_IS_POINTER_INTERCONVERTIBLE_BASE_OF(BaseT, DerivedT);

#    endif

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_BASE_OF() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename BaseT, typename DerivedT>
struct is_pointer_interconvertible_base_of : public false_type
{
    static_assert(false_t<BaseT>::value,
                  "phi::is_pointer_interconvertible_base_of requires compiler support");
};

template <typename BaseT, typename DerivedT>
struct is_not_pointer_interconvertible_base_of
    : public bool_constant<!is_pointer_interconvertible_base_of<BaseT, DerivedT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename BaseT, typename DerivedT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_pointer_interconvertible_base_of_v =
        is_pointer_interconvertible_base_of<BaseT, DerivedT>::value;

template <typename BaseT, typename DerivedT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_pointer_interconvertible_base_of_v =
        is_not_pointer_interconvertible_base_of<BaseT, DerivedT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP
