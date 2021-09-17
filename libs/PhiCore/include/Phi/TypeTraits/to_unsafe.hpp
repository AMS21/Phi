#ifndef INCG_PHI_CORE_TYPE_TRAITS_TO_UNSAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TO_UNSAFE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/Inline.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/TypeTraits/is_safe_type.hpp"
#include "Phi/TypeTraits/make_unsafe.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsafe_t<TypeT> to_unsafe_impl(
            TypeT original, true_type is_safe_type) noexcept
    {
        PHI_UNUSED_PARAMETER(is_safe_type);

        return original.get();
    }

    template <typename TypeT>
    PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsafe_t<TypeT> to_unsafe_impl(
            TypeT original, false_type is_safe_type) noexcept
    {
        PHI_UNUSED_PARAMETER(is_safe_type);

        return original;
    }
} // namespace detail

template <typename TypeT>
PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_unsafe_t<TypeT> to_unsafe(TypeT original) noexcept
{
    return detail::to_unsafe_impl(original, is_safe_type<TypeT>{});
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_TO_UNSAFE_HPP
