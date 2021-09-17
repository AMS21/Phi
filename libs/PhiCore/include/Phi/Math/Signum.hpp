#ifndef INCG_PHI_CORE_MATH_SIGNUM_HPP
#define INCG_PHI_CORE_MATH_SIGNUM_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/Inline.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_signed.hpp"
#include "Phi/TypeTraits/to_unsafe.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr i32 signum_impl(TypeT      value,
                                                              false_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_signed);

        return static_cast<std::int32_t>(TypeT(0) < value);
    }

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr i32 signum_impl(TypeT     value,
                                                              true_type is_signed) noexcept
    {
        PHI_UNUSED_PARAMETER(is_signed);

        return static_cast<std::int32_t>((TypeT(0) < value) - (value < TypeT(0)));
    }
} // namespace detail

template <typename TypeT>
PHI_NODISCARD PHI_ALWAYS_INLINE constexpr i32 signum(TypeT value) noexcept
{
    return detail::signum_impl(to_unsafe(value), is_signed<TypeT>());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_SIGNUM_HPP
