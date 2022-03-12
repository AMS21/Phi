#ifndef INCG_PHI_CORE_TYPE_TRAITS_TO_UNSAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TO_UNSAFE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/unused.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/forward.hpp"
#include "phi/type_traits/is_safe_type.hpp"
#include "phi/type_traits/make_unsafe.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    PHI_CLANG_SUPPRESS_WARNING_PUSH()
    PHI_CLANG_SUPPRESS_WARNING("-Wunused-parameter")

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsafe_t<TypeT> to_unsafe_impl(
            TypeT original, true_type /*is_safe_type*/) noexcept
    {
        return original.get();
    }

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsafe_t<TypeT> to_unsafe_impl(
            TypeT original, false_type /*is_safe_type*/) noexcept
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
