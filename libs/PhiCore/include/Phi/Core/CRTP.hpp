#ifndef INCG_PHI_CORE_CRTP_HPP
#define INCG_PHI_CORE_CRTP_HPP

#include "Phi/PhiConfig.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, template <typename> typename CRTPTypeT>
class CRTP
{
public:
    [[nodiscard]] constexpr TypeT& underlying() noexcept
    {
        return static_cast<TypeT&>(*this);
    }

    [[nodiscard]] constexpr TypeT const& underlying() const noexcept
    {
        return static_cast<TypeT const&>(*this);
    }
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CRTP_HPP
