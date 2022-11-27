#ifndef INCG_PHI_CORE_CONTAINER_BITVIEW_HPP
#define INCG_PHI_CORE_CONTAINER_BITVIEW_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/move.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/disable_if.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_copy_assignable.hpp"
#include "phi/type_traits/is_copy_constructible.hpp"
#include "phi/type_traits/is_default_constructible.hpp"
#include "phi/type_traits/is_move_assignable.hpp"
#include "phi/type_traits/is_move_constructible.hpp"
#include "phi/type_traits/is_nothrow_copy_assignable.hpp"
#include "phi/type_traits/is_nothrow_copy_constructible.hpp"
#include "phi/type_traits/is_nothrow_default_constructible.hpp"
#include "phi/type_traits/is_nothrow_move_assignable.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"

PHI_EXTERNAL_HEADERS_BEGIN()
#include <bitset>
PHI_EXTERNAL_HEADERS_END()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class PHI_ATTRIBUTE_POINTER bit_view
{
public:
    using this_type  = bit_view<TypeT>;
    using value_type = TypeT;
    using bit_type   = std::bitset<sizeof(TypeT)>;

    static_assert(sizeof(TypeT) != 0,
                  "phi::bit_view: Cannot create a bit_view with type of size 0");

    template <typename = enable_if_t<is_default_constructible<TypeT>::value>>
    constexpr bit_view() noexcept(is_nothrow_default_constructible<TypeT>::value)
        : m_Value{}
    {}

    ~bit_view() = default;

    template <typename = enable_if_t<is_copy_constructible<TypeT>::value>>
    constexpr bit_view(const TypeT& other) noexcept(is_nothrow_copy_constructible<TypeT>::value)
        : m_Value{other}
    {}

    constexpr bit_view(const bit_type& other) noexcept
        : m_Bits{other}
    {}

    constexpr bit_view(const bit_view& other) noexcept
        : m_Bits(other.m_Bits)
    {}

    template <typename = enable_if_t<is_move_constructible<TypeT>::value>>
    constexpr bit_view(TypeT&& other) noexcept(is_nothrow_move_constructible<TypeT>::value)
        : m_Value{other}
    {}

    constexpr bit_view(bit_type&& other) noexcept
        : m_Bits{other}
    {}

    constexpr bit_view(bit_view&& other) noexcept
        : m_Bits{other.m_Bits}
    {}

    template <typename = enable_if_t<is_copy_assignable<TypeT>::value>>
    constexpr bit_view& operator=(const TypeT& other) noexcept(
            is_nothrow_copy_assignable<TypeT>::value)
    {
        m_Value = other;

        return *this;
    }

    constexpr bit_view& operator=(const bit_type& other) noexcept
    {
        m_Bits = other;
    }

    bit_view& operator=(const bit_view& other) = default;

    template <typename = enable_if_t<is_move_assignable<TypeT>::value>>
    constexpr bit_view& operator=(TypeT&& other) noexcept(is_nothrow_move_assignable<TypeT>::value)
    {
        m_Value = other;

        return *this;
    }

    constexpr bit_view& operator=(bit_type&& other) noexcept
    {
        m_Bits = other;

        return *this;
    }

    constexpr bit_view& operator=(bit_view&& other) noexcept
    {
        m_Bits = other.m_Bits;

        return *this;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& get_value() noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& get_value() const noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR bit_type& get_bits() noexcept
    {
        return m_Bits;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const bit_type& get_bits() const noexcept
    {
        return m_Bits;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean operator[](size_t pos) const noexcept
    {
        PHI_ASSERT(pos < sizeof(TypeT), "Access out of bounds");

        return m_Bits[pos];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR typename bit_type::reference operator[](
            size_t pos) noexcept
    {
        PHI_ASSERT(pos < sizeof(TypeT), "Access out of bounds");

        return m_Bits[pos];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR bool at(size_t pos) const noexcept
    {
        PHI_ASSERT(pos < sizeof(TypeT), "Access out of bounds");

        return m_Bits[pos];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR typename bit_type::reference at(size_t pos) noexcept
    {
        PHI_ASSERT(pos < sizeof(TypeT), "Access out of bounds");

        return m_Bits[pos];
    }

    constexpr bit_view& set_all() noexcept
    {
        m_Bits.set();

        return *this;
    }

    constexpr bit_view& reset_all() noexcept
    {
        m_Bits.reset();

        return *this;
    }

    constexpr bit_view& flip_all() noexcept
    {
        m_Bits.flip();

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR bit_view& set(size_t pos) noexcept
    {
        PHI_ASSERT(pos < m_Bits.size(), "Access out of bounds");

        m_Bits.set(pos);

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR bit_view& reset(size_t pos) noexcept
    {
        PHI_ASSERT(pos < m_Bits.size(), "Access out of bounds");

        m_Bits.reset(pos);

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR bit_view& flip(size_t pos) noexcept
    {
        PHI_ASSERT(pos < m_Bits.size(), "Access out of bounds");

        m_Bits.flip(pos);

        return *this;
    }

    PHI_NODISCARD constexpr bool all() const noexcept
    {
        return m_Bits.all();
    }

    PHI_NODISCARD constexpr bool any() const noexcept
    {
        return m_Bits.any();
    }

    PHI_NODISCARD constexpr bool none() const noexcept
    {
        return m_Bits.none();
    }

    PHI_NODISCARD constexpr size_t count() const noexcept
    {
        return m_Bits.count();
    }

private:
    union
    {
        std::bitset<sizeof(TypeT)> m_Bits;  // NOLINT(readability-identifier-naming)
        TypeT                      m_Value; // NOLINT(readability-identifier-naming)
    };
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_BITVIEW_HPP
