#ifndef INCG_PHI_CORE_TYPE_TRAITS_TO_UNSAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TO_UNSAFE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/CompilerSupport/Unused.hpp"
#include "Phi/Config/Inline.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/TypeTraits/is_safe_type.hpp"
#include "Phi/TypeTraits/make_unsafe.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    PHI_CLANG_SUPPRESS_WARNING_PUSH()
    PHI_CLANG_SUPPRESS_WARNING("-Wunused-parameter")

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsafe_t<TypeT> to_unsafe_impl(
            TypeT original, PHI_UNUSED true_type is_safe_type) noexcept
    {
        return original.get();
    }

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsafe_t<TypeT> to_unsafe_impl(
            TypeT original, PHI_UNUSED false_type is_safe_type) noexcept
    {
        return original;
    }

    PHI_CLANG_SUPPRESS_WARNING_POP()
} // namespace detail

template <typename TypeT>
PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsafe_t<TypeT> to_unsafe(TypeT original) noexcept
{
    return detail::to_unsafe_impl(original, is_safe_type<TypeT>{});
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_TO_UNSAFE_HPP
