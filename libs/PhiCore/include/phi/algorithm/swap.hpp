#ifndef INCG_PHI_CORE_ALGORITHM_SWAP_HPP
#define INCG_PHI_CORE_ALGORITHM_SWAP_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/move.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_move_assignable.hpp"
#include "phi/type_traits/is_move_constructible.hpp"
#include "phi/type_traits/is_nothrow_move_assignable.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    using swap_result_t = typename enable_if<is_move_constructible<TypeT>::value &&
                                             is_move_assignable<TypeT>::value>::type;
}

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

template <typename TypeT>
inline PHI_EXTENDED_CONSTEXPR detail::swap_result_t<TypeT> swap(TypeT& lhs, TypeT& rhs) noexcept(
        is_nothrow_move_constructible<TypeT>::value&& is_nothrow_move_assignable<TypeT>::value)
{
    TypeT temp(phi::move(lhs));
    lhs = phi::move(rhs);
    rhs = phi::move(temp);
}

template <typename TypeT, size_t Dimension>
inline PHI_EXTENDED_CONSTEXPR detail::swap_result_t<TypeT> swap(
        TypeT (&lhs)[Dimension], TypeT (&rhs)[Dimension]) noexcept(noexcept(swap(*lhs, *rhs)))
{
    for (size_t i = 0u; i != Dimension; ++i)
    {
        swap(lhs[i], rhs[i]);
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_SWAP_HPP
