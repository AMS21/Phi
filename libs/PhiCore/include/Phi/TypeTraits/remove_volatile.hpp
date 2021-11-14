#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_VOLATILE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Intrinsics/RemoveVolatile.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_REMOVE_VOLATILE()

template <typename TypeT>
struct remove_volatile
{
    using type = PHI_REMOVE_VOLATILE(TypeT);
}

template <typename TypeT>
using remove_volatile_t = PHI_REMOVE_VOLATILE(TypeT);

#else

template <typename TypeT>
struct remove_volatile
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_volatile<volatile TypeT>
{
    using type = TypeT;
};

template <typename TypeT>
using remove_volatile_t = typename remove_volatile<TypeT>::type;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_VOLATILE_HPP
