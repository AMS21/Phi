#ifndef INCG_PHI_CORE_VOIDIFY_HPP
#define INCG_PHI_CORE_VOIDIFY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/address_of.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_NODISCARD PHI_ALWAYS_INLINE constexpr void* voidify(TypeT& from) noexcept
{
    // Cast away cv-qualifiers to allow modifying elements of a range through const iterators.
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<void*>(static_cast<const volatile void*>(address_of(from)));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_VOIDIFY_HPP
