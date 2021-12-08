#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_BOOL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_BOOL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/type_traits/is_same_rcv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

class boolean;

template <typename TypeT>
struct is_safe_bool : public is_same_rcv<TypeT, boolean>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_safe_bool_v = is_safe_bool<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_BOOL_HPP
