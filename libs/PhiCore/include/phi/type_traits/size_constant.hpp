#ifndef INCG_PHI_CORE_TYPE_TRAITS_SIZE_CONSTANT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_SIZE_CONSTANT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/size_t.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <size_t Value>
using size_constant = integral_constant<size_t, Value>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_SIZE_CONSTANT_HPP
