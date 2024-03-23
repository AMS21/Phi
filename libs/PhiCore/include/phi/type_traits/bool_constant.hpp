#ifndef INCG_PHI_CORE_TYPE_TRAITS_BOOL_CONSTANT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_BOOL_CONSTANT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_FEATURE_ALIAS_TEMPLATES()

#    include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool BooleanValue>
using bool_constant = integral_constant<bool, BooleanValue>;

#else

#    include "phi/type_traits/false_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <bool BooleanValue>
struct bool_constant
{
    static_assert(false_t<decltype(BooleanValue)>::value,
                  "'phi::bool_constant' requires C++-11 alias templates. Checked with "
                  "'PHI_HAS_FEATURE_ALIAS_TEMPLATES'");
};

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_BOOL_CONSTANT_HPP
