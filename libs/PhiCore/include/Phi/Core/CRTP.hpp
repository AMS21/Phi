#ifndef INCG_PHI_CORE_CRTP_HPP
#define INCG_PHI_CORE_CRTP_HPP

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, template <typename> typename CRTPTypeT>
class CRTP
{
public:
    PHI_NODISCARD constexpr TypeT& underlying() noexcept
    {
        return static_cast<TypeT&>(*this);
    }

    PHI_NODISCARD constexpr TypeT const& underlying() const noexcept
    {
        return static_cast<TypeT const&>(*this);
    }
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CRTP_HPP
