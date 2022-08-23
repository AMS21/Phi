#ifndef INCG_PHI_CORE_TYPE_TRAITS_STATIC_CLAMP_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_STATIC_CLAMP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4296) // 'op' expression is always false/true

template <size_t Value, size_t MinValue, size_t MaxValue>
struct static_clamp
    : integral_constant<size_t,
                        (Value < MinValue) ? MinValue : ((Value > MaxValue) ? MaxValue : Value)>
{
    static_assert(MinValue <= MaxValue,
                  "[phi::static_clamp]: MinValue must be less than or equal to MaxValue");
};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <size_t Value, size_t MinValue, size_t MaxValue>
PHI_INLINE_VARIABLE constexpr size_t static_clamp_v =
        static_clamp<Value, MinValue, MaxValue>::value;

#endif

PHI_MSVC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_STATIC_CLAMP_HPP
