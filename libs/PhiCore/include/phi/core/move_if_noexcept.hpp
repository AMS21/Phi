#ifndef INCG_PHI_CORE_MOVE_IF_NOEXCEPT_HPP
#define INCG_PHI_CORE_MOVE_IF_NOEXCEPT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/move.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/is_copy_constructible.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    using move_if_noexcept_result_t =
            conditional_t<is_not_nothrow_move_constructible<TypeT>::value &&
                                  is_copy_constructible<TypeT>::value,
                          const TypeT&, TypeT&&>;
}

template <typename TypeT>
PHI_NODISCARD inline PHI_CONSTEXPR typename detail::move_if_noexcept_result_t<TypeT>
move_if_noexcept(TypeT& arg) noexcept
{
    return move(arg);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MOVE_IF_NOEXCEPT_HPP
