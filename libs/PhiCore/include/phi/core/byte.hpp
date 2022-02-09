#ifndef INCG_PHI_CORE_BYTE_HPP
#define INCG_PHI_CORE_BYTE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_unsafe_integral.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

enum class byte : unsigned char
{
};


constexpr byte operator|(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) |
                                                        static_cast<unsigned int>(rhs)));
}

PHI_EXTENDED_CONSTEXPR
byte& operator|=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs | rhs;
}

constexpr byte operator&(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) &
                                                        static_cast<unsigned int>(rhs)));
}

PHI_EXTENDED_CONSTEXPR
byte& operator&=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs & rhs;
}

constexpr byte operator^(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) ^
                                                        static_cast<unsigned int>(rhs)));
}

PHI_EXTENDED_CONSTEXPR
byte& operator^=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs ^ rhs;
}

constexpr byte operator~(byte b) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(~static_cast<unsigned int>(b)));
}

template <typename IntegerT>
constexpr typename enable_if<is_unsafe_integral<IntegerT>::value, byte>::type& operator<<=(
        byte& lhs, IntegerT shift) noexcept
{
    return lhs = lhs << shift;
}

template <typename IntegerT>
constexpr typename enable_if<is_unsafe_integral<IntegerT>::value, byte>::type operator<<(
        byte lhs, IntegerT shift) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) << shift));
}

template <typename IntegerT>
constexpr typename enable_if<is_unsafe_integral<IntegerT>::value, byte>::type& operator>>=(
        byte& lhs, IntegerT shift) noexcept
{
    return lhs = lhs >> shift;
}

template <typename IntegerT>
constexpr typename enable_if<is_unsafe_integral<IntegerT>::value, byte>::type operator>>(
        byte lhs, IntegerT shift) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) >> shift));
}

template <typename IntegerT>
constexpr typename enable_if<is_unsafe_integral<IntegerT>::value, IntegerT>::type to_integer(
        byte b) noexcept
{
    return static_cast<IntegerT>(b);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_BYTE_HPP
