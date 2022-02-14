#ifndef INCG_PHI_CORE_TYPE_TRAITS_BOOL_CONSTANT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_BOOL_CONSTANT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool BooleanValue>
using bool_constant = integral_constant<bool, BooleanValue>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_BOOL_CONSTANT_HPP
