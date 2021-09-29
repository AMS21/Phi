#ifndef INCG_PHI_CORE_ALGORITHM_SWAP_HPP
#define INCG_PHI_CORE_ALGORITHM_SWAP_HPP

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/Core/Move.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/is_move_assignable.hpp"
#include "Phi/TypeTraits/is_move_constructible.hpp"
#include "Phi/TypeTraits/is_nothrow_move_assignable.hpp"
#include "Phi/TypeTraits/is_nothrow_move_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    using swap_result_t = typename enable_if<is_move_constructible<TypeT>::value &&
                                             is_move_assignable<TypeT>::value>::type;
}

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

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_SWAP_HPP
