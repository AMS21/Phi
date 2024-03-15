#ifndef INCG_PHI_CORE_TYPE_TRAITS_TO_SAFE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TO_SAFE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/type_traits/make_safe.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR make_safe_t<TypeT> to_safe(TypeT original) noexcept
{
    return static_cast<make_safe_t<TypeT>>(original);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_TO_SAFE_HPP
