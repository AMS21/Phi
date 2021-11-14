#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CONST_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CONST_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Features.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_REMOVE_CONST()

template <typename TypeT>
struct remove_const
{
    using type = __remove_const(TypeT);
};

template <typename TypeT>
using remove_const_t = __remove_const(TypeT);

#else

template <typename TypeT>
struct remove_const
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_const<const TypeT>
{
    using type = TypeT;
};

template <typename TypeT>
using remove_const_t = typename remove_const<TypeT>::type;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_CONST_HPP
