#ifndef INCG_PHI_CORE_ALGORITHM_MAX_HPP
#define INCG_PHI_CORE_ALGORITHM_MAX_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/forward.hpp"
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
PHI_NODISCARD constexpr TypeT max(TypeT&& value) noexcept
{
    return forward<TypeT>(value);
}

template <typename FirstT, typename SecondT, typename... RestT>
PHI_NODISCARD constexpr typename std::common_type<FirstT, SecondT, RestT...>::type max(
        FirstT&& first, SecondT&& second, RestT&&... rest) noexcept
{
    using common_t = typename std::common_type<FirstT, SecondT, RestT...>::type;

    return max(((static_cast<common_t>(first) < static_cast<common_t>(second)) ?
                        static_cast<common_t>(second) :
                        static_cast<common_t>(first)),
               forward<RestT>(rest)...);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_MAX_HPP
