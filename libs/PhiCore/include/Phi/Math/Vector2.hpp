#ifndef INCG_PHI_MATH_VECTOR2_HPP
#define INCG_PHI_MATH_VECTOR2_HPP

#include "Phi/PhiConfig.hpp"

#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class Vector2
{
public:
    using this_type = Vector2<TypeT>;
    using value_type = TypeT;

public:
    constexpr Vector2(TypeT val_x, TypeT val_y) noexcept :
        x(val_x),
        y(val_y)
    {}

    constexpr Vector2(TypeT val_xy) noexcept :
        x(val_xy),
        y(val_xy)
    {}

    constexpr Vector2(const Vector2<TypeT>& other) noexcept :
        x(other.x),
        y(other.y)
    {}

    constexpr Vector2(Vector2<TypeT>&& other) noexcept :
        x(std::move(other.x)),
        y(std::move(other.y))
    {}

    template <typename OtherT>
    constexpr Vector2(const Vector2<OtherT>& other) noexcept :
        x(static_cast<TypeT>(other.x)),
        y(static_cast<TypeT>(other.y))
    {}

    template <typename OtherT>
    constexpr Vector2(Vector2<OtherT>&& other) noexcept :
        x(static_cast<TypeT>(std::move(other.x))),
        y(static_cast<TypeT>(std::move(other.y)))
    {}

public:
    TypeT x;
    TypeT y;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_MATH_VECTOR2_HPP