#ifndef INCG_PHI_CORE_TYPE_TRAITS_ARRAY_SIZE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ARRAY_SIZE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/extent.hpp"
#include "phi/type_traits/is_array.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <unsigned Dimension = 0u, typename TypeT>
PHI_NODISCARD constexpr size_t array_size(TypeT& /*array*/) noexcept
{
    static_assert(is_array<TypeT>::value, "phi::array_size may only be used on array types");

    return extent<TypeT, Dimension>::value;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ARRAY_SIZE_HPP
