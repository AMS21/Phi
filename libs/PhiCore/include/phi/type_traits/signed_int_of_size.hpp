#ifndef INCG_PHI_CORE_TYPE_TRAITS_SIGNED_INT_OF_SIZE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_SIGNED_INT_OF_SIZE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/size_t.hpp"
#include "phi/core/sized_types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <size_t SizeInBytes>
struct signed_int_of_size
{
    static_assert(SizeInBytes < 0, "Size must be a power of 2 greater than 0");
};

template <>
struct signed_int_of_size<1>
{
    using type = int8_t;
};

template <>
struct signed_int_of_size<2>
{
    using type = int16_t;
};

template <>
struct signed_int_of_size<4>
{
    using type = int32_t;
};

template <>
struct signed_int_of_size<8>
{
    using type = int64_t;
};

template <size_t SizeInBytes>
using signed_int_of_size_t = typename signed_int_of_size<SizeInBytes>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_SIGNED_INT_OF_SIZE_HPP
