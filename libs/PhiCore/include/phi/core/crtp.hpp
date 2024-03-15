#ifndef INCG_PHI_CORE_CRTP_HPP
#define INCG_PHI_CORE_CRTP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, template <typename> class CRTPTypeT>
class crtp
{
public:
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& underlying() PHI_NOEXCEPT
    {
        return static_cast<TypeT&>(*this);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& underlying() const PHI_NOEXCEPT
    {
        return static_cast<const TypeT&>(*this);
    }
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CRTP_HPP
