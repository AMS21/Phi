#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SCALAR_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SCALAR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_scalar.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_scalar : public bool_constant<PHI_IS_SCALAR(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_scalar_v = PHI_IS_SCALAR(TypeT);

#    endif

#else

#    include "phi/type_traits/is_arithmetic.hpp"
#    include "phi/type_traits/is_enum.hpp"
#    include "phi/type_traits/is_member_pointer.hpp"
#    include "phi/type_traits/is_null_pointer.hpp"
#    include "phi/type_traits/is_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_scalar
    : public bool_constant<is_arithmetic<TypeT>::value || is_enum<TypeT>::value ||
                           is_pointer<TypeT>::value || is_member_pointer<TypeT>::value ||
                           is_null_pointer<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_scalar_v = is_scalar<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SCALAR_HPP
