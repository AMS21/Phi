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
    PHI_CLANG_SUPPRESS_WARNING_PUSH()
    PHI_CLANG_SUPPRESS_WARNING("-Wunused-paramter")

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr i32 signum_impl(TypeT      value,
                                                              false_type is_signed) noexcept
    {
        return static_cast<std::int32_t>(TypeT(0) < value);
    }

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr i32 signum_impl(TypeT     value,
                                                              true_type is_signed) noexcept
    {
        return static_cast<std::int32_t>((TypeT(0) < value) - (value < TypeT(0)));
    }

    PHI_CLANG_SUPPRESS_WARNING_POP()
} // namespace detail

template <typename TypeT>
PHI_NODISCARD PHI_ALWAYS_INLINE constexpr i32 signum(TypeT value) noexcept
{
    return detail::signum_impl(to_unsafe(value), is_signed<TypeT>());
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_SIGNUM_HPP
