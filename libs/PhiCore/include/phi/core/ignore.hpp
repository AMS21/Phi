#ifndef INCG_PHI_CORE_IGNORE_HPP
#define INCG_PHI_CORE_IGNORE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/noexcept.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct ignore_t
{
    template <typename OtherT>
    // NOLINTNEXTLINE(misc-unconventional-assign-operator,cppcoreguidelines-missing-std-forward)
    PHI_ALWAYS_INLINE PHI_CONSTEXPR_AND_CONST ignore_t<TypeT>& operator=(OtherT&& /*other*/) const
            PHI_NOEXCEPT
    {
        return *this;
    }
};

PHI_INLINE_VARIABLE PHI_CONSTEXPR ignore_t<unsigned char> ignore = ignore_t<unsigned char>{};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_IGNORE_HPP
