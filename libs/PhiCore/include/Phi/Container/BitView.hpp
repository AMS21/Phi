#ifndef INCG_PHI_CORE_CONTAINER_BITVIEW_HPP
#define INCG_PHI_CORE_CONTAINER_BITVIEW_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Move.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/TypeTraits/disable_if.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/is_copy_assignable.hpp"
#include "Phi/TypeTraits/is_copy_constructible.hpp"
#include "Phi/TypeTraits/is_default_constructible.hpp"
#include "Phi/TypeTraits/is_move_assignable.hpp"
#include "Phi/TypeTraits/is_move_constructible.hpp"
#include "Phi/TypeTraits/is_nothrow_copy_assignable.hpp"
#include "Phi/TypeTraits/is_nothrow_copy_constructible.hpp"
#include "Phi/TypeTraits/is_nothrow_default_constructible.hpp"
#include "Phi/TypeTraits/is_nothrow_move_assignable.hpp"
#include "Phi/TypeTraits/is_nothrow_move_constructible.hpp"
#include <bitset>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class BitView
{
public:
    using this_type  = BitView<TypeT>;
    using value_type = TypeT;
    using bit_type   = std::bitset<sizeof(TypeT)>;

    static_assert(sizeof(TypeT) != 0, "phi::BitView: Cannot create a BitView with type of size 0");

    template <typename = enable_if_t<is_default_constructible<TypeT>::value>>
    constexpr BitView() noexcept(is_nothrow_default_constructible<TypeT>::value)
        : m_Value{}
    {}

    template <typename = enable_if_t<is_copy_constructible<TypeT>::value>>
    constexpr BitView(const TypeT& other) noexcept(is_nothrow_copy_constructible<TypeT>::value)
        : m_Value{other}
    {}

    constexpr BitView(const bit_type& other) noexcept
        : m_Bits{other}
    {}

    constexpr BitView(const BitView& other) noexcept
        : m_Bits(other.m_Bits)
    {}

    template <typename = enable_if_t<is_move_constructible<TypeT>::value>>
    constexpr BitView(TypeT&& other) noexcept(is_nothrow_move_constructible<TypeT>::value)
        : m_Value{other}
    {}

    constexpr BitView(bit_type&& other) noexcept
        : m_Bits{other}
    {}

    constexpr BitView(BitView&& other) noexcept
        : m_Bits{other.m_Bits}
    {}

    template <typename = enable_if_t<is_copy_assignable<TypeT>::value>>
    constexpr BitView& operator=(const TypeT& other) noexcept(
            is_nothrow_copy_assignable<TypeT>::value)
    {
        m_Value = other;

        return *this;
    }

    constexpr BitView& operator=(const bit_type& other) noexcept
    {
        m_Bits = other;

        return *this;
    }

    constexpr BitView& operator=(const BitView& other) noexcept
    {
        m_Bits = other.m_Bits;

        return *this;
    }

    template <typename = enable_if_t<is_move_assignable<TypeT>::value>>
    constexpr BitView& operator=(TypeT&& other) noexcept(is_nothrow_move_assignable<TypeT>::value)
    {
        m_Value = other;

        return *this;
    }

    constexpr BitView& operator=(bit_type&& other) noexcept
    {
        m_Bits = other;

        return *this;
    }

    constexpr BitView& operator=(BitView&& other) noexcept
    {
        m_Bits = other.m_Bits;

        return *this;
    }

    PHI_NODISCARD constexpr TypeT& get_value() noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD constexpr const TypeT& get_value() const noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD constexpr bit_type& get_bits() noexcept
    {
        return m_Bits;
    }

    PHI_NODISCARD constexpr const bit_type& get_bits() const noexcept
    {
        return m_Bits;
    }

    PHI_NODISCARD constexpr bool operator[](size_t pos) const noexcept
    {
        PHI_DBG_ASSERT(pos < sizeof(TypeT), "Access out of bounds");

        return m_Bits[pos];
    }

    PHI_NODISCARD constexpr typename bit_type::reference operator[](size_t pos) noexcept
    {
        PHI_DBG_ASSERT(pos < sizeof(TypeT), "Access out of bounds");

        return m_Bits[pos];
    }

    PHI_NODISCARD constexpr bool at(size_t pos) const noexcept
    {
        PHI_DBG_ASSERT(pos < sizeof(TypeT), "Access out of bounds");

        return m_Bits[pos];
    }

    PHI_NODISCARD constexpr typename bit_type::reference at(size_t pos) noexcept
    {
        PHI_DBG_ASSERT(pos < sizeof(TypeT), "Access out of bounds");

        return m_Bits[pos];
    }

    constexpr BitView& set_all() noexcept
    {
        m_Bits.set();

        return *this;
    }

    constexpr BitView& reset_all() noexcept
    {
        m_Bits.reset();

        return *this;
    }

    constexpr BitView& flip_all() noexcept
    {
        m_Bits.flip();

        return *this;
    }

    constexpr BitView& set(size_t pos) noexcept
    {
        PHI_DBG_ASSERT(pos < m_Bits.size(), "Access out of bounds");

        m_Bits.set(pos);

        return *this;
    }

    constexpr BitView& reset(size_t pos) noexcept
    {
        PHI_DBG_ASSERT(pos < m_Bits.size(), "Access out of bounds");

        m_Bits.reset(pos);

        return *this;
    }

    constexpr BitView& flip(size_t pos) noexcept
    {
        PHI_DBG_ASSERT(pos < m_Bits.size(), "Access out of bounds");

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
        std::bitset<sizeof(TypeT)> m_Bits;
        TypeT                      m_Value;
    };
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_BITVIEW_HPP
