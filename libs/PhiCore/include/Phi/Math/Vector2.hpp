#ifndef INCG_PHI_MATH_VECTOR2_HPP
#define INCG_PHI_MATH_VECTOR2_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/Types.hpp"
#include <iterator>
#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class Vector2
{
public:
    using this_type              = Vector2<TypeT>;
    using value_type             = TypeT;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = value_type*;
    using const_iterator         = const value_type*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
    // Constructors
    constexpr Vector2(TypeT val_x, TypeT val_y) noexcept
        : x(val_x)
        , y(val_y)
    {}

    constexpr explicit Vector2(TypeT val_xy) noexcept
        : x(val_xy)
        , y(val_xy)
    {}

    constexpr Vector2(const Vector2<TypeT>& other) noexcept
        : x(other.x)
        , y(other.y)
    {}

    constexpr Vector2(Vector2<TypeT>&& other) noexcept
        : x(std::move(other.x))
        , y(std::move(other.y))
    {}

    template <typename OtherT>
    constexpr Vector2(const Vector2<OtherT>& other) noexcept
        : x(static_cast<TypeT>(other.x))
        , y(static_cast<TypeT>(other.y))
    {}

    template <typename OtherT>
    constexpr Vector2(Vector2<OtherT>&& other) noexcept
        : x(static_cast<TypeT>(std::move(other.x)))
        , y(static_cast<TypeT>(std::move(other.y)))
    {}

    // Operators

    constexpr Vector2<TypeT>& operator=(const Vector2<TypeT>& other) noexcept
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    constexpr Vector2<TypeT>& operator=(Vector2<TypeT>&& other) noexcept
    {
        x = std::move(other.x);
        y = std::move(other.y);

        return *this;
    }

public:
    TypeT x;
    TypeT y;
};

// Unary Operators

template <typename TypeT>
constexpr Vector2<TypeT> operator+(const Vector2<TypeT>& rhs) noexcept
{
    return rhs;
}

template <typename TypeT>
constexpr Vector2<TypeT> operator-(const Vector2<TypeT>& rhs) noexcept
{
    static_assert(!detail::is_integer<TypeT>::value || std::is_signed_v<TypeT>,
                  "Cannot call unary minus on unsigned integer");

    return Vector2<TypeT>(-rhs.x, -rhs.y);
}

// Binary Operators

template <typename LhsT, typename RhsT>
constexpr auto operator+(const Vector2<LhsT>& lhs, const Vector2<RhsT>& rhs) noexcept
{
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename LhsT, typename RhsT>
constexpr Vector2<LhsT>& operator+=(Vector2<LhsT>& lhs, const Vector2<RhsT>& rhs) noexcept
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr auto operator-(const Vector2<LhsT>& lhs, const Vector2<RhsT>& rhs) noexcept
{
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename LhsT, typename RhsT>
constexpr Vector2<LhsT>& operator-=(Vector2<LhsT>& lhs, const Vector2<RhsT>& rhs) noexcept
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr auto operator*(const Vector2<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return Vector2(lhs.x * rhs, lhs.y * rhs);
}

template <typename LhsT, typename RhsT>
constexpr Vector2<LhsT>& operator*=(Vector2<LhsT>& lhs, const RhsT& rhs) noexcept
{
    lhs.x *= rhs;
    lhs.y *= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr auto operator/(const Vector2<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return Vector2(lhs.x / rhs, lhs.y / rhs);
}

template <typename LhsT, typename RhsT>
constexpr Vector2<LhsT>& operator/=(Vector2<LhsT>& lhs, const RhsT& rhs) noexcept
{
    lhs.x /= rhs;
    lhs.y /= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(const Vector2<LhsT>& lhs, const Vector2<RhsT>& rhs) noexcept
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(const Vector2<LhsT>& lhs, const Vector2<RhsT>& rhs) noexcept
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

// Define the most common types
using Vector2i8    = Vector2<i8>;
using Vector2u8    = Vector2<u8>;
using Vector2i16   = Vector2<i16>;
using Vector2u16   = Vector2<u16>;
using Vector2i32   = Vector2<i32>;
using Vector2u32   = Vector2<u32>;
using Vector2i64   = Vector2<i64>;
using Vector2u64   = Vector2<u64>;
using Vector2isize = Vector2<isize>;
using Vector2usize = Vector2<usize>;

using Vector2f32 = Vector2<f32>;
using Vector2f64 = Vector2<f64>;

using Vector2b = Vector2<Boolean>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_MATH_VECTOR2_HPP
