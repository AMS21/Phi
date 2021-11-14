#ifndef INCG_PHI_CORE_CRTP_HPP
#define INCG_PHI_CORE_CRTP_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, template <typename> class CRTPTypeT>
class CRTP
{
public:
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& underlying() noexcept
    {
        return static_cast<TypeT&>(*this);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& underlying() const noexcept
    {
        return static_cast<const TypeT&>(*this);
    }
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CRTP_HPP
