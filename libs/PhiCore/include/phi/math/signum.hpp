#ifndef INCG_PHI_CORE_MATH_SIGNUM_HPP
#define INCG_PHI_CORE_MATH_SIGNUM_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/types.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_signed.hpp"
#include "phi/type_traits/to_unsafe.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR i32
    signum_impl(TypeT value, false_type /*is_signed*/) PHI_NOEXCEPT
    {
        return static_cast<int32_t>(TypeT(0) < value);
    }

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR i32
    signum_impl(TypeT value, true_type /*is_signed*/) PHI_NOEXCEPT
    {
        return static_cast<int32_t>((TypeT(0) < value) - (value < TypeT(0)));
    }
} // namespace detail

template <typename TypeT>
PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR i32 signum(TypeT value) PHI_NOEXCEPT
{
    return detail::signum_impl(to_unsafe(value), is_signed<TypeT>());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_SIGNUM_HPP
