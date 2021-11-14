#ifndef INCG_PHI_CORE_TYPE_TRAITS_TO_SAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TO_SAFE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/Inline.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/TypeTraits/make_safe.hpp"
#include "Phi/TypeTraits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_NODISCARD PHI_ALWAYS_INLINE constexpr make_safe_t<TypeT> to_safe(TypeT original) noexcept
{
    return static_cast<make_safe_t<TypeT>>(original);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_TO_SAFE_HPP
