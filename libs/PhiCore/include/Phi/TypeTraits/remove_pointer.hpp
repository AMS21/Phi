#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct remove_pointer
{
    using type = int;
};

template <typename TypeT>
struct remove_pointer<TypeT*>
{
    using type = int;
};

template <typename TypeT>
struct remove_pointer<TypeT* const>
{
    using type = int;
};

template <typename TypeT>
struct remove_pointer<TypeT* volatile>
{
    using type = int;
};

template <typename TypeT>
struct remove_pointer<TypeT* const volatile>
{
    using type = int;
};

template <typename TypeT>
using remove_pointer_t = typename remove_pointer<TypeT>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_POINTER_HPP
