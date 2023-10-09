#ifndef INCG_PHI_CORE_IGNORE_HPP
#define INCG_PHI_CORE_IGNORE_HPP

#include "phi/phi_config.hpp"

#include "phi/compiler_support/inline_variables.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct ignore_t
{
    template <typename OtherT>
    // NOLINTNEXTLINE(misc-unconventional-assign-operator,cppcoreguidelines-missing-std-forward)
    const inline constexpr ignore_t<TypeT>& operator=(OtherT&& /*other*/) const noexcept
    {
        return *this;
    }
};

PHI_INLINE_VARIABLE constexpr ignore_t<unsigned char> ignore = ignore_t<unsigned char>{};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_IGNORE_HPP
