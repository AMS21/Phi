#ifndef INCG_PHI_MATH_VECTOR3_HPP
#define INCG_PHI_MATH_VECTOR3_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/Math/Vector2.hpp"
#include <iterator>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

/*!
 * \brief Utility template class for manipulating
 *        3-dimensional vectors.
 *
**/
template <typename TypeT>
class Vector3
{
public:
    using this_type              = Vector3<TypeT>;
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
    constexpr Vector3(TypeT val_x, TypeT val_y, TypeT val_z) noexcept
        : x(val_x)
        , y(val_y)
        , z(val_z)
    {}

    constexpr Vector3(TypeT val_xyz) noexcept
        : x(val_xyz)
        , y(val_xyz)
        , z(val_xyz)
    {}

    constexpr Vector3(const Vector2<TypeT>& vec2, TypeT val_z) noexcept
        : x(vec2.x)
        , y(vec2.y)
        , z(val_z)
    {}

    constexpr Vector3(Vector2<TypeT>&& vec2, TypeT val_z) noexcept
        : x(std::move(vec2.x))
        , y(std::move(vec2.y))
        , z(val_z)
    {}

    template <typename OtherT>
    constexpr Vector3(const Vector2<OtherT>& vec2, TypeT val_z) noexcept
        : x(static_cast<TypeT>(vec.x))
        , y(static_cast<TypeT>(vec.y))
        , z(val_z)
    {}

    template <typename OtherT>
    constexpr Vector3(Vector2<OtherT>&& vec2, TypeT val_z) noexcept
        : x(static_cast<TypeT>(std::move(vec2.x)))
        , y(static_cast<TypeT>(std::move(vec2.y)))
        , z(val_z)
    {}

    constexpr Vector3(const Vector3<TypeT>& other) noexcept
        : x(other.x)
        , y(other.y)
        , z(other.z)
    {}

    constexpr Vector3(Vector3<TypeT>&& other) noexcept
        : x(std::move(other.x))
        , y(std::move(other.y))
        , z(std::move(other.z))
    {}

    template <typename OtherT>
    constexpr Vector3(const Vector3<OtherT>& other) noexcept
        : x(static_cast<TypeT>(other.x))
        , y(static_cast<TypeT>(other.y))
        , z(static_cast<TypeT>(other.z))
    {}

    template <typename OtherT>
    constexpr Vector3(Vector3<OtherT>&& other) noexcept
        : x(static_cast<TypeT>(std::move(other.x)))
        , y(static_cast<TypeT>(std::move(other.y)))
        , z(static_cast<TypeT>(std::move(other.z)))
    {}

    // Operators

    constexpr Vector3<TypeT>& operator=(const Vector3<TypeT>& other) noexcept
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    constexpr Vector3<TypeT>& operator=(Vector3<TypeT>&& other) noexcept
    {
        x = std::move(other.x);
        y = std::move(other.y);
        z = std::move(other.z);

        return *this;
    }

public:
    TypeT x;
    TypeT y;
    TypeT z;
};

// Unary operators

template <typename TypeT>
constexpr Vector3<TypeT> operator+(const Vector3<TypeT>& rhs) noexcept
{
    return rhs;
}

template <typename TypeT>
constexpr Vector3<TypeT> operator-(const Vector3<TypeT>& rhs) noexcept
{
    return Vector3<TypeT>(-rhs.x, -rhs.y, -rhs.z);
}

// Binary Operators

template <typename LhsT, typename RhsT>
constexpr auto operator+(const Vector3<LhsT>& lhs, const Vector3<RhsT>& rhs) noexcept
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <typename LhsT, typename RhsT>
constexpr Vector3<LhsT>& operator+=(Vector3<LhsT>& lhs, const Vector3<RhsT>& rhs) noexcept
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr auto operator-(const Vector3<LhsT>& lhs, const Vector3<RhsT>& rhs) noexcept
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <typename LhsT, typename RhsT>
constexpr Vector3<LhsT>& operator-=(Vector3<LhsT>& lhs, const Vector3<RhsT>& rhs) noexcept
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr auto operator*(const Vector3<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

template <typename LhsT, typename RhsT>
constexpr Vector3<LhsT>& operator*=(Vector3<LhsT>& lhs, const RhsT& rhs) noexcept
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr auto operator/(const Vector3<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

template <typename LhsT, typename RhsT>
constexpr Vector3<LhsT>& operator/=(Vector3<LhsT>& lhs, const RhsT& rhs) noexcept
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(const Vector3<LhsT>& lhs, const Vector3<RhsT>& rhs) noexcept
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(const Vector3<LhsT>& lhs, const Vector3<RhsT>& rhs) noexcept
{
    return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
}

// Define the most common types
using Vector3i8    = Vector3<i8>;
using Vector3u8    = Vector3<u8>;
using Vector3i16   = Vector3<i16>;
using Vector3u16   = Vector3<u16>;
using Vector3i32   = Vector3<i32>;
using Vector3u32   = Vector3<u32>;
using Vector3i64   = Vector3<i64>;
using Vector3u64   = Vector3<u64>;
using Vector3imax  = Vector3<imax>;
using Vector3umax  = Vector3<umax>;
using Vector3isize = Vector3<isize>;
using Vector3usize = Vector3<usize>;

using Vector3f32  = Vector3<f32>;
using Vector3f64  = Vector3<f64>;
using Vector3fmax = Vector3<fmax>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_MATH_VECTOR3_HPP