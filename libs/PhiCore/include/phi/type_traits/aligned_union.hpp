#ifndef INCG_PHI_CORE_TYPE_TRAITS_ALIGNED_UNION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ALIGNED_UNION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/aligned_storage.hpp"
#include "phi/type_traits/static_max.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <size_t Length, typename TypeT, typename... TypesT>
struct aligned_union
{
    static PHI_CONSTEXPR_AND_CONST size_t alignment_value =
            static_max<alignof(TypeT), alignof(TypesT)...>::value;
    static PHI_CONSTEXPR_AND_CONST size_t length =
            static_max<Length, sizeof(TypeT), sizeof(TypesT)...>::value;

    using type = typename aligned_storage<Length, alignment_value>::type;
};

template <size_t Length, typename... TypesT>
using aligned_union_t = typename aligned_union<Length, TypesT...>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ALIGNED_UNION_HPP
