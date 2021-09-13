#ifndef INCG_PHI_CORE_TYPE_TRAITS_TO_UNDERLYING_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_TO_UNDERLYING_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/TypeTraits/underlying_type.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename EnumT>
constexpr underlying_type_t<EnumT> to_underlying(EnumT val) noexcept
{
    return static_cast<underlying_type_t<EnumT>>(val);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_TO_UNDERLYING_HPP
