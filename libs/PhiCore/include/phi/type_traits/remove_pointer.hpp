#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_POINTER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/intrinsics/remove_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_REMOVE_POINTER()

template <typename TypeT>
struct remove_pointer
{
    using type = PHI_REMOVE_POINTER(TypeT);
};

template <typename TypeT>
using remove_pointer_t = PHI_REMOVE_POINTER(TypeT);

#else

template <typename TypeT>
struct remove_pointer
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_pointer<TypeT*>
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_pointer<TypeT* const>
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_pointer<TypeT* volatile>
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_pointer<TypeT* const volatile>
{
    using type = TypeT;
};

template <typename TypeT>
using remove_pointer_t = typename remove_pointer<TypeT>::type;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_POINTER_HPP
