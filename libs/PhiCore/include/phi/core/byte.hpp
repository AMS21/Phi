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

// NOLINTNEXTLINE(readability-identifier-naming)
enum class byte : unsigned char
{
};

PHI_CONSTEXPR byte operator|(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) |
                                                        static_cast<unsigned int>(rhs)));
}

PHI_EXTENDED_CONSTEXPR
byte& operator|=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs | rhs;
}

PHI_CONSTEXPR byte operator&(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) &
                                                        static_cast<unsigned int>(rhs)));
}

PHI_EXTENDED_CONSTEXPR
byte& operator&=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs & rhs;
}

PHI_CONSTEXPR byte operator^(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) ^
                                                        static_cast<unsigned int>(rhs)));
}

PHI_EXTENDED_CONSTEXPR
byte& operator^=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs ^ rhs;
}

PHI_CONSTEXPR byte operator~(byte value) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(~static_cast<unsigned int>(value)));
}

template <typename IntegerT>
PHI_CONSTEXPR typename enable_if<is_unsafe_integral<IntegerT>::value, byte>::type& operator<<=(
        byte& lhs, IntegerT shift) noexcept
{
    return lhs = lhs << shift;
}

template <typename IntegerT>
PHI_CONSTEXPR typename enable_if<is_unsafe_integral<IntegerT>::value, byte>::type operator<<(
        byte lhs, IntegerT shift) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) << shift));
}

template <typename IntegerT>
PHI_CONSTEXPR typename enable_if<is_unsafe_integral<IntegerT>::value, byte>::type& operator>>=(
        byte& lhs, IntegerT shift) noexcept
{
    return lhs = lhs >> shift;
}

template <typename IntegerT>
PHI_CONSTEXPR typename enable_if<is_unsafe_integral<IntegerT>::value, byte>::type operator>>(
        byte lhs, IntegerT shift) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) >> shift));
}

template <typename IntegerT>
PHI_CONSTEXPR typename enable_if<is_unsafe_integral<IntegerT>::value, IntegerT>::type to_integer(
        byte value) noexcept
{
    return static_cast<IntegerT>(value);
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_BYTE_HPP
