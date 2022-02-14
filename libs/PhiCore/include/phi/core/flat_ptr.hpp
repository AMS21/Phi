#ifndef INCG_PHI_CORE_FLAT_PTR_HPP
#define INCG_PHI_CORE_FLAT_PTR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_pointer.hpp"
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Winline")

class not_null_flat_ptr;

class flat_ptr
{
public:
    using this_type     = flat_ptr;
    using not_null_type = not_null_flat_ptr;
    using value_type    = void*;

    constexpr flat_ptr() noexcept
        : m_Ptr(nullptr)
    {}

    constexpr flat_ptr(nullptr_t) noexcept
        : m_Ptr(nullptr)
    {}

    template <typename PtrT, enable_if_t<is_pointer<PtrT>::value, bool> = true>
    constexpr flat_ptr(PtrT ptr) noexcept
        : m_Ptr(static_cast<void*>(ptr))
    {}

    constexpr flat_ptr(const flat_ptr& other) noexcept
        : m_Ptr(other.m_Ptr)
    {}

    constexpr flat_ptr(flat_ptr&& other) noexcept
        : m_Ptr(other.get())
    {}

    constexpr flat_ptr(const not_null_flat_ptr& other) noexcept;

    constexpr flat_ptr(not_null_flat_ptr&& other) noexcept;

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(nullptr_t) noexcept
    {
        m_Ptr = nullptr;

        return *this;
    }

    ~flat_ptr() = default;

    template <typename PtrT, enable_if_t<is_pointer<PtrT>::value, bool> = true>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(PtrT ptr) noexcept
    {
        m_Ptr = static_cast<void*>(ptr);

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(const flat_ptr& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(flat_ptr&& other) noexcept
    {
        m_Ptr = other.get();

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(const not_null_flat_ptr& other) noexcept;

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_flat_ptr&& other) noexcept;

    PHI_NODISCARD constexpr void* get() noexcept
    {
        return m_Ptr;
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD constexpr const void* get() const noexcept
    {
        return m_Ptr;
    }
#endif

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_flat_ptr release_not_null() const noexcept;

    PHI_EXTENDED_CONSTEXPR void clear() noexcept
    {
        m_Ptr = nullptr;
    }

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator boolean() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator const void*() const noexcept
    {
        return get();
    }

    constexpr explicit operator void*() noexcept
    {
        return get();
    }

    PHI_EXTENDED_CONSTEXPR void swap(flat_ptr& other) noexcept
    {
        phi::swap(m_Ptr, other.m_Ptr);
    }

    void* operator->() = delete;

    const void* operator->() const = delete;

    void operator*() = delete;

    void operator*() const = delete;

private:
    void* m_Ptr;
};

constexpr boolean operator==(const flat_ptr& lhs, const flat_ptr& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

constexpr boolean operator==(const flat_ptr& lhs, nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

constexpr boolean operator==(nullptr_t, const flat_ptr& rhs) noexcept
{
    return rhs.get() == nullptr;
}

constexpr boolean operator!=(const flat_ptr& lhs, const flat_ptr& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

constexpr boolean operator!=(const flat_ptr& lhs, nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

constexpr boolean operator!=(nullptr_t, const flat_ptr& rhs) noexcept
{
    return rhs.get() != nullptr;
}

PHI_EXTENDED_CONSTEXPR inline void swap(flat_ptr& lhs, flat_ptr& rhs) noexcept
{
    lhs.swap(rhs);
}

class not_null_flat_ptr
{
public:
    using this_type  = not_null_flat_ptr;
    using value_type = void*;

    not_null_flat_ptr() = delete;

    not_null_flat_ptr(nullptr_t) = delete;

    template <typename PtrT, enable_if_t<is_pointer<PtrT>::value, bool> = true>
    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr(PtrT ptr) noexcept
        : m_Ptr(static_cast<void*>(ptr))
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_flat_ptr");
    }

    constexpr not_null_flat_ptr(const not_null_flat_ptr& other) noexcept
        : m_Ptr(other.m_Ptr)
    {}

    constexpr not_null_flat_ptr(not_null_flat_ptr&& other) noexcept
        : m_Ptr(other.m_Ptr)
    {}

    ~not_null_flat_ptr() = default;

    not_null_flat_ptr& operator=(nullptr_t) = delete;

    template <typename PtrT>
    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(
            enable_if_t<is_pointer<PtrT>::value, PtrT> ptr) noexcept
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_flat_ptr");

        m_Ptr = static_cast<void*>(ptr);

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(const not_null_flat_ptr& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(not_null_flat_ptr&& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    PHI_NODISCARD constexpr void* get() noexcept
    {
        return m_Ptr;
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD constexpr const void* get() const noexcept
    {
        return m_Ptr;
    }
#endif

    constexpr explicit operator const void*() const noexcept
    {
        return get();
    }

    constexpr explicit operator void*() noexcept
    {
        return get();
    }

    PHI_EXTENDED_CONSTEXPR void swap(not_null_flat_ptr& other) noexcept
    {
        phi::swap(m_Ptr, other.m_Ptr);
    }

    void* operator->() = delete;

    const void* operator->() const = delete;

    void operator*() = delete;

    void operator*() const = delete;

private:
    void* m_Ptr;
};

constexpr flat_ptr::flat_ptr(const not_null_flat_ptr& other) noexcept
    : m_Ptr(const_cast<void*>(other.get()))
{}

constexpr flat_ptr::flat_ptr(not_null_flat_ptr&& other) noexcept
    : m_Ptr(other.get())
{}

PHI_EXTENDED_CONSTEXPR_OR_INLINE flat_ptr& flat_ptr::operator=(
        const not_null_flat_ptr& other) noexcept
{
    m_Ptr = const_cast<void*>(other.get());

    return *this;
}

PHI_EXTENDED_CONSTEXPR_OR_INLINE flat_ptr& flat_ptr::operator=(not_null_flat_ptr&& other) noexcept
{
    m_Ptr = other.get();

    return *this;
}

PHI_EXTENDED_CONSTEXPR not_null_flat_ptr flat_ptr::release_not_null() const noexcept
{
    PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to release nullptr to phi::not_null_flat_ptr");

    return {m_Ptr};
}

constexpr boolean operator==(const not_null_flat_ptr& lhs, const not_null_flat_ptr& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

boolean operator==(const not_null_flat_ptr&, nullptr_t) = delete;

boolean operator==(nullptr_t, const not_null_flat_ptr&) = delete;

constexpr boolean operator!=(const not_null_flat_ptr& lhs, const not_null_flat_ptr& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

boolean operator!=(const not_null_flat_ptr&, nullptr_t) = delete;

boolean operator!=(nullptr_t, const not_null_flat_ptr&) = delete;

inline void swap(not_null_flat_ptr& lhs, not_null_flat_ptr& rhs) noexcept
{
    lhs.swap(rhs);
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <>
    struct hash<phi::flat_ptr>
    {
        size_t operator()(const phi::flat_ptr& ptr) const noexcept
        {
            return std::hash<const void*>()(ptr.get());
        }
    };

    template <>
    struct hash<phi::not_null_flat_ptr>
    {
        size_t operator()(const phi::not_null_flat_ptr& ptr) const noexcept
        {
            return std::hash<const void*>()(ptr.get());
        }
    };
} // namespace std

PHI_GCC_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_FLAT_PTR_HPP
