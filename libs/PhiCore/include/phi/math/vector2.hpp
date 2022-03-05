#ifndef INCG_PHI_CORE_MATH_VECTOR2_HPP
#define INCG_PHI_CORE_MATH_VECTOR2_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/move.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include "phi/type_traits/is_integer.hpp"
#include "phi/type_traits/is_signed.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class vector2
{
public:
    using this_type              = vector2<TypeT>;
    using value_type             = TypeT;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = value_type*;
    using const_iterator         = const value_type*;
    using reverse_iterator       = phi::reverse_iterator<iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;

    // Constructors
    constexpr vector2(TypeT val_x, TypeT val_y) noexcept
        : x(val_x)
        , y(val_y)
    {}

    constexpr explicit vector2(TypeT val_xy) noexcept
        : x(val_xy)
        , y(val_xy)
    {}

    constexpr vector2(const vector2<TypeT>& other) noexcept
        : x(other.x)
        , y(other.y)
    {}

    constexpr vector2(vector2<TypeT>&& other) noexcept
        : x(move(other.x))
        , y(move(other.y))
    {}

    template <typename OtherT>
    constexpr vector2(const vector2<OtherT>& other) noexcept
        : x(static_cast<TypeT>(other.x))
        , y(static_cast<TypeT>(other.y))
    {}

    template <typename OtherT>
    constexpr vector2(vector2<OtherT>&& other) noexcept
        : x(static_cast<TypeT>(move(other.x)))
        , y(static_cast<TypeT>(move(other.y)))
    {}

    ~vector2() = default;

    // Operators

    PHI_EXTENDED_CONSTEXPR vector2<TypeT>& operator=(const vector2<TypeT>& other) noexcept
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR vector2<TypeT>& operator=(vector2<TypeT>&& other) noexcept
    {
        x = move(other.x);
        y = move(other.y);

        return *this;
    }

public:
    TypeT x;
    TypeT y;
};

// Unary Operators

template <typename TypeT>
constexpr vector2<TypeT> operator+(const vector2<TypeT>& rhs) noexcept
{
    return rhs;
}

template <typename TypeT>
constexpr vector2<TypeT> operator-(const vector2<TypeT>& rhs) noexcept
{
    static_assert(!is_integer<TypeT>::value || is_signed<TypeT>::value,
                  "Cannot call unary minus on unsigned integer");

    return vector2<TypeT>(-rhs.x, -rhs.y);
}

// Binary Operators

template <typename LhsT, typename RhsT>
constexpr vector2<LhsT> operator+(const vector2<LhsT>& lhs, const vector2<RhsT>& rhs) noexcept
{
    return vector2<LhsT>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector2<LhsT>& operator+=(vector2<LhsT>&       lhs,
                                                 const vector2<RhsT>& rhs) noexcept
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr vector2<LhsT> operator-(const vector2<LhsT>& lhs, const vector2<RhsT>& rhs) noexcept
{
    return vector2<LhsT>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector2<LhsT>& operator-=(vector2<LhsT>&       lhs,
                                                 const vector2<RhsT>& rhs) noexcept
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr vector2<LhsT> operator*(const vector2<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return vector2<LhsT>(lhs.x * rhs, lhs.y * rhs);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector2<LhsT>& operator*=(vector2<LhsT>& lhs, const RhsT& rhs) noexcept
{
    lhs.x *= rhs;
    lhs.y *= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr vector2<LhsT> operator/(const vector2<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return vector2<LhsT>(lhs.x / rhs, lhs.y / rhs);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector2<LhsT>& operator/=(vector2<LhsT>& lhs, const RhsT& rhs) noexcept
{
    lhs.x /= rhs;
    lhs.y /= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr boolean operator==(const vector2<LhsT>& lhs, const vector2<RhsT>& rhs) noexcept
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename LhsT, typename RhsT>
constexpr boolean operator!=(const vector2<LhsT>& lhs, const vector2<RhsT>& rhs) noexcept
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

// Define the most common types
using vector2i8    = vector2<i8>;
using vector2u8    = vector2<u8>;
using vector2i16   = vector2<i16>;
using vector2u16   = vector2<u16>;
using vector2i32   = vector2<i32>;
using vector2u32   = vector2<u32>;
using vector2i64   = vector2<i64>;
using vector2u64   = vector2<u64>;
using vector2isize = vector2<isize>;
using vector2usize = vector2<usize>;

using vector2f32 = vector2<f32>;
using vector2f64 = vector2<f64>;

using vector2b = vector2<boolean>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_VECTOR2_HPP
