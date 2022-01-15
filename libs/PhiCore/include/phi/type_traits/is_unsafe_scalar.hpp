#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_SCALAR_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_SCALAR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_enum.hpp"
#include "phi/type_traits/is_member_pointer.hpp"
#include "phi/type_traits/is_null_pointer.hpp"
#include "phi/type_traits/is_pointer.hpp"
#include "phi/type_traits/is_unsafe_arithmetic.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_WORKING_IS_ENUM()
#    define PHI_HAS_WORKING_IS_UNSAFE_SCALAR() 1
#else
#    define PHI_HAS_WORKING_IS_UNSAFE_SCALAR() 0
#endif

template <typename TypeT>
struct is_unsafe_scalar
    : public bool_constant<is_unsafe_arithmetic<TypeT>::value || is_enum<TypeT>::value ||
                           is_pointer<TypeT>::value || is_member_pointer<TypeT>::value ||
                           is_null_pointer<TypeT>::value>
{};

template <typename TypeT>
struct is_not_unsafe_scalar : public bool_constant<!is_unsafe_scalar<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unsafe_scalar_v = is_unsafe_scalar<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_unsafe_scalar_v = is_not_unsafe_scalar<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNSAFE_SCALAR_HPP
