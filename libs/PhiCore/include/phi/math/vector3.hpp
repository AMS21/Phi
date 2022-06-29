#ifndef INCG_PHI_CORE_MATH_VECTOR3_HPP
#define INCG_PHI_CORE_MATH_VECTOR3_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/move.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include "phi/math/vector2.hpp"
#include "phi/type_traits/is_integer.hpp"
#include "phi/type_traits/is_signed.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

/*!
 * \brief Utility template class for manipulating
 *        3-dimensional vectors.
 *
**/
template <typename TypeT>
class vector3
{
public:
    using this_type              = vector3<TypeT>;
    using value_type             = TypeT;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = value_type*;
    using const_iterator         = const value_type*;
    using reverse_iterator       = phi::reverse_iterator<iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;

    ~vector3() = default;

    constexpr vector3(TypeT val_x, TypeT val_y, TypeT val_z) noexcept
        : x(val_x)
        , y(val_y)
        , z(val_z)
    {}

    constexpr explicit vector3(TypeT val_xyz) noexcept
        : x(val_xyz)
        , y(val_xyz)
        , z(val_xyz)
    {}

    constexpr vector3(const vector2<TypeT>& vec2, TypeT val_z) noexcept
        : x(vec2.x)
        , y(vec2.y)
        , z(val_z)
    {}

    constexpr vector3(vector2<TypeT>&& vec2, TypeT val_z) noexcept
        : x(phi::move(vec2.x))
        , y(phi::move(vec2.y))
        , z(val_z)
    {}

    template <typename OtherT>
    constexpr vector3(const vector2<OtherT>& vec2, TypeT val_z) noexcept
        : x(static_cast<TypeT>(vec2.x))
        , y(static_cast<TypeT>(vec2.y))
        , z(val_z)
    {}

    template <typename OtherT>
    constexpr vector3(vector2<OtherT>&& vec2, TypeT val_z) noexcept
        : x(static_cast<TypeT>(phi::move(vec2.x)))
        , y(static_cast<TypeT>(phi::move(vec2.y)))
        , z(val_z)
    {}

    constexpr vector3(const vector3<TypeT>& other) noexcept
        : x(other.x)
        , y(other.y)
        , z(other.z)
    {}

    constexpr vector3(vector3<TypeT>&& other) noexcept
        : x(phi::move(other.x))
        , y(phi::move(other.y))
        , z(phi::move(other.z))
    {}

    template <typename OtherT>
    constexpr vector3(const vector3<OtherT>& other) noexcept
        : x(static_cast<TypeT>(other.x))
        , y(static_cast<TypeT>(other.y))
        , z(static_cast<TypeT>(other.z))
    {}

    template <typename OtherT>
    constexpr vector3(vector3<OtherT>&& other) noexcept
        : x(static_cast<TypeT>(phi::move(other.x)))
        , y(static_cast<TypeT>(phi::move(other.y)))
        , z(static_cast<TypeT>(phi::move(other.z)))
    {}

    // Operators

    vector3<TypeT>& operator=(const vector3<TypeT>& other) = default;

    // NOLINTNEXTLINE(performance-noexcept-move-constructor)
    vector3<TypeT>& operator=(vector3<TypeT>&& other) = default;

    TypeT x;
    TypeT y;
    TypeT z;
};

// Unary operators

template <typename TypeT>
constexpr vector3<TypeT> operator+(const vector3<TypeT>& rhs) noexcept
{
    return rhs;
}

template <typename TypeT>
constexpr vector3<TypeT> operator-(const vector3<TypeT>& rhs) noexcept
{
    static_assert(!is_integer<TypeT>::value || is_signed<TypeT>::value,
                  "Cannot call unary minus on unsigned integer");

    return vector3<TypeT>(-rhs.x, -rhs.y, -rhs.z);
}

// Binary Operators

template <typename LhsT, typename RhsT>
constexpr vector3<LhsT> operator+(const vector3<LhsT>& lhs, const vector3<RhsT>& rhs) noexcept
{
    return vector3<LhsT>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector3<LhsT>& operator+=(vector3<LhsT>&       lhs,
                                                 const vector3<RhsT>& rhs) noexcept
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr vector3<LhsT> operator-(const vector3<LhsT>& lhs, const vector3<RhsT>& rhs) noexcept
{
    return vector3<LhsT>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector3<LhsT>& operator-=(vector3<LhsT>&       lhs,
                                                 const vector3<RhsT>& rhs) noexcept
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr vector3<LhsT> operator*(const vector3<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return vector3<LhsT>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector3<LhsT>& operator*=(vector3<LhsT>& lhs, const RhsT& rhs) noexcept
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr vector3<LhsT> operator/(const vector3<LhsT>& lhs, const RhsT& rhs) noexcept
{
    return vector3<LhsT>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector3<LhsT>& operator/=(vector3<LhsT>& lhs, const RhsT& rhs) noexcept
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
constexpr boolean operator==(const vector3<LhsT>& lhs, const vector3<RhsT>& rhs) noexcept
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <typename LhsT, typename RhsT>
constexpr boolean operator!=(const vector3<LhsT>& lhs, const vector3<RhsT>& rhs) noexcept
{
    return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
}

// Define the most common types
using vector3i8    = vector3<i8>;
using vector3u8    = vector3<u8>;
using vector3i16   = vector3<i16>;
using vector3u16   = vector3<u16>;
using vector3i32   = vector3<i32>;
using vector3u32   = vector3<u32>;
using vector3i64   = vector3<i64>;
using vector3u64   = vector3<u64>;
using vector3isize = vector3<isize>;
using vector3usize = vector3<usize>;

using vector3f32 = vector3<f32>;
using vector3f64 = vector3<f64>;

using vector3b = vector3<boolean>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_VECTOR3_HPP
