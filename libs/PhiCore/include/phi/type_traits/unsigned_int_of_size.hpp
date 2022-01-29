#ifndef INCG_PHI_CORE_TYPE_TRAITS_UNSIGNED_INT_OF_SIZE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_UNSIGNED_INT_OF_SIZE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/core/size_t.hpp"
#include "phi/core/sized_types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <size_t SizeInBytes>
struct unsigned_int_of_size
{
    static_assert(SizeInBytes < 0, "Size must be a power of 2 greater than 0");
};

template <>
struct unsigned_int_of_size<1>
{
    using type = uint8_t;
};

template <>
struct unsigned_int_of_size<2>
{
    using type = uint16_t;
};

template <>
struct unsigned_int_of_size<4>
{
    using type = uint32_t;
};

template <>
struct unsigned_int_of_size<8>
{
    using type = uint64_t;
};

template <size_t SizeInBytes>
using unsigned_int_of_size_t = typename unsigned_int_of_size<SizeInBytes>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_UNSIGNED_INT_OF_SIZE_HPP
