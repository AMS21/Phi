#ifndef INCG_PHI_CORE_FLAT_PTR_HPP
#define INCG_PHI_CORE_FLAT_PTR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/forward/flat_ptr.hpp"
#include "phi/forward/observer_ptr.hpp"
#include "phi/forward/ref_ptr.hpp"
#include "phi/forward/scope_ptr.hpp"
#include "phi/forward/std/hash.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wnonnull-compare")

class PHI_ATTRIBUTE_POINTER flat_ptr
{
public:
    using this_type     = flat_ptr;
    using not_null_type = not_null_flat_ptr;
    using value_type    = void*;

    PHI_CONSTEXPR flat_ptr() PHI_NOEXCEPT : m_Pointer(nullptr)
    {}

    PHI_CONSTEXPR flat_ptr(nullptr_t) PHI_NOEXCEPT : m_Pointer(nullptr)
    {}

    template <typename PointerT, enable_if_t<is_pointer<PointerT>::value, bool> = true>
    PHI_CONSTEXPR flat_ptr(PointerT pointer) PHI_NOEXCEPT
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        : m_Pointer(const_cast<void*>(static_cast<const void*>(pointer)))
    {}

    template <typename TypeT>
    PHI_CONSTEXPR flat_ptr(observer_ptr<TypeT>& pointer) PHI_NOEXCEPT
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    PHI_CONSTEXPR flat_ptr(not_null_observer_ptr<TypeT>& pointer) PHI_NOEXCEPT
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    PHI_CONSTEXPR flat_ptr(ref_ptr<TypeT>& pointer) PHI_NOEXCEPT
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    PHI_CONSTEXPR flat_ptr(not_null_ref_ptr<TypeT>& pointer) PHI_NOEXCEPT
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    PHI_CONSTEXPR flat_ptr(scope_ptr<TypeT>& pointer) PHI_NOEXCEPT
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    PHI_CONSTEXPR flat_ptr(not_null_scope_ptr<TypeT>& pointer) PHI_NOEXCEPT
        : m_Pointer{static_cast<void*>(pointer.get())}

    {}

    flat_ptr(const flat_ptr& other) = default;

    flat_ptr(flat_ptr&& other) = default;

    PHI_CONSTEXPR flat_ptr(const not_null_flat_ptr& other) PHI_NOEXCEPT;

    PHI_CONSTEXPR flat_ptr(not_null_flat_ptr&& other) PHI_NOEXCEPT;

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(nullptr_t) PHI_NOEXCEPT
    {
        m_Pointer = nullptr;

        return *this;
    }

    ~flat_ptr() = default;

    template <typename PointerT, enable_if_t<is_pointer<PointerT>::value, bool> = true>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(PointerT pointer) PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer);

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(observer_ptr<TypeT>& pointer) PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_observer_ptr<TypeT>& pointer) PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(ref_ptr<TypeT>& pointer) PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_ref_ptr<TypeT>& pointer) PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(scope_ptr<TypeT>& pointer) PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_scope_ptr<TypeT>& pointer) PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    flat_ptr& operator=(const flat_ptr& other) = default;

    flat_ptr& operator=(flat_ptr&& other) = default;

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(const not_null_flat_ptr& other) PHI_NOEXCEPT;

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_flat_ptr&& other) PHI_NOEXCEPT;

    PHI_NODISCARD PHI_CONSTEXPR void* get() PHI_NOEXCEPT
    {
        return m_Pointer;
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD PHI_CONSTEXPR const void* get() const PHI_NOEXCEPT
    {
        return m_Pointer;
    }
#endif

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_flat_ptr release_not_null() const PHI_NOEXCEPT;

    PHI_EXTENDED_CONSTEXPR void clear() PHI_NOEXCEPT
    {
        m_Pointer = nullptr;
    }

    PHI_EXTENDED_CONSTEXPR void reset(nullptr_t) PHI_NOEXCEPT
    {
        clear();
    }

    PHI_EXTENDED_CONSTEXPR void reset(const void* other = nullptr) PHI_NOEXCEPT
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        m_Pointer = const_cast<void*>(other);
    }

    template <typename PointerT, enable_if_t<is_pointer<PointerT>::value, bool> = true>
    PHI_EXTENDED_CONSTEXPR void reset(const PointerT other = nullptr) PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(other);
    }

    PHI_CONSTEXPR explicit operator bool() const PHI_NOEXCEPT
    {
        return get() != nullptr;
    }

    PHI_CONSTEXPR explicit operator boolean() const PHI_NOEXCEPT
    {
        return get() != nullptr;
    }

    PHI_CONSTEXPR explicit operator const void*() const PHI_NOEXCEPT
    {
        return get();
    }

    PHI_CONSTEXPR explicit operator void*() PHI_NOEXCEPT
    {
        return get();
    }

    PHI_EXTENDED_CONSTEXPR void swap(flat_ptr& other) PHI_NOEXCEPT
    {
        phi::swap(m_Pointer, other.m_Pointer);
    }

    void* operator->() = delete;

    const void* operator->() const = delete;

    void operator*() = delete;

    void operator*() const = delete;

private:
    void* m_Pointer;
};

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(const flat_ptr& lhs,
                                                   const flat_ptr& rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs.get();
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(const flat_ptr& lhs, nullptr_t) PHI_NOEXCEPT
{
    return lhs.get() == nullptr;
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(nullptr_t, const flat_ptr& rhs) PHI_NOEXCEPT
{
    return rhs.get() == nullptr;
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(const flat_ptr& lhs,
                                                   const void*     rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs;
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(const void*     lhs,
                                                   const flat_ptr& rhs) PHI_NOEXCEPT
{
    return lhs == rhs.get();
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const flat_ptr& lhs,
                                                   const flat_ptr& rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs.get();
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const flat_ptr& lhs, nullptr_t) PHI_NOEXCEPT
{
    return lhs.get() != nullptr;
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(nullptr_t, const flat_ptr& rhs) PHI_NOEXCEPT
{
    return rhs.get() != nullptr;
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const flat_ptr& lhs,
                                                   const void*     rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs;
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const void*     lhs,
                                                   const flat_ptr& rhs) PHI_NOEXCEPT
{
    return lhs != rhs.get();
}

PHI_EXTENDED_CONSTEXPR PHI_ALWAYS_INLINE void swap(flat_ptr& lhs, flat_ptr& rhs) PHI_NOEXCEPT
{
    lhs.swap(rhs);
}

class PHI_ATTRIBUTE_POINTER not_null_flat_ptr
{
public:
    using this_type  = not_null_flat_ptr;
    using value_type = void*;

    not_null_flat_ptr() = delete;

    not_null_flat_ptr(nullptr_t) = delete;

    template <typename PointerT, enable_if_t<is_pointer<PointerT>::value, bool> = true>
    PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR not_null_flat_ptr(PointerT pointer) PHI_NOEXCEPT
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        : m_Pointer(const_cast<void*>(static_cast<const void*>(pointer)))
    {
        PHI_ASSERT(pointer != nullptr, "Trying to assign nullptr to phi::not_null_flat_ptr");
    }

    template <typename TypeT>
    PHI_CONSTEXPR not_null_flat_ptr(const not_null_observer_ptr<TypeT>& pointer) PHI_NOEXCEPT
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        : m_Pointer{const_cast<void*>(static_cast<const void*>(pointer.get()))}
    {}

    template <typename TypeT>
    PHI_CONSTEXPR not_null_flat_ptr(const not_null_ref_ptr<TypeT>& pointer) PHI_NOEXCEPT
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        : m_Pointer{const_cast<void*>(static_cast<const void*>(pointer.get()))}
    {}

    template <typename TypeT>
    PHI_CONSTEXPR not_null_flat_ptr(const not_null_scope_ptr<TypeT>& pointer) PHI_NOEXCEPT
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        : m_Pointer{const_cast<void*>(static_cast<const void*>(pointer.get()))}
    {}

    not_null_flat_ptr(const not_null_flat_ptr&) = default;

    not_null_flat_ptr(not_null_flat_ptr&&) = default;

    ~not_null_flat_ptr() = default;

    not_null_flat_ptr& operator=(nullptr_t) = delete;

    template <typename PointerT>
    PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(
            enable_if_t<is_pointer<PointerT>::value, PointerT> pointer) PHI_NOEXCEPT
    {
        PHI_ASSERT(pointer != nullptr, "Trying to assign nullptr to phi::not_null_flat_ptr");

        m_Pointer = static_cast<void*>(pointer);

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(not_null_observer_ptr<TypeT>& pointer)
            PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(not_null_ref_ptr<TypeT>& pointer)
            PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(not_null_scope_ptr<TypeT>& pointer)
            PHI_NOEXCEPT
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    not_null_flat_ptr& operator=(const not_null_flat_ptr&) = default;

    not_null_flat_ptr& operator=(not_null_flat_ptr&&) = default;

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR void* get() PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Pointer != nullptr, "Trying to get nullptr from phi::not_null_flat_ptr");

        return m_Pointer;
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR const void* get() const PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Pointer != nullptr, "Trying to get nullptr from phi::not_null_flat_ptr");

        return m_Pointer;
    }
#endif

    PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR explicit operator const void*() const PHI_NOEXCEPT
    {
        return get();
    }

    PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR explicit operator void*() PHI_NOEXCEPT
    {
        return get();
    }

    void reset(nullptr_t) = delete;

    template <typename PointerT, enable_if_t<is_pointer<PointerT>::value, bool> = true>
    PHI_EXTENDED_CONSTEXPR void reset(const PointerT other) PHI_NOEXCEPT
    {
        PHI_ASSERT(other != nullptr, "Trying to assign nullptr to phi::not_null_flat_ptr");

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
        m_Pointer = const_cast<void*>(static_cast<const void*>(other));
    }

    PHI_EXTENDED_CONSTEXPR void swap(not_null_flat_ptr& other) PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Pointer != nullptr, "Trying to assign nullptr to phi::not_null_flat_ptr");
        PHI_ASSERT(other.m_Pointer != nullptr,
                   "Trying to assign nullptr to phi::not_null_flat_ptr");

        phi::swap(m_Pointer, other.m_Pointer);
    }

    void* operator->() = delete;

    const void* operator->() const = delete;

    void operator*() = delete;

    void operator*() const = delete;

private:
    void* m_Pointer;
};

PHI_GCC_SUPPRESS_WARNING_POP()

PHI_CONSTEXPR flat_ptr::flat_ptr(const not_null_flat_ptr& other) PHI_NOEXCEPT
    : m_Pointer(const_cast<void*>(other.get())) // NOLINT(cppcoreguidelines-pro-type-const-cast)
{}

PHI_CONSTEXPR flat_ptr::flat_ptr(not_null_flat_ptr&& other) PHI_NOEXCEPT : m_Pointer(other.get())
{}

PHI_EXTENDED_CONSTEXPR_OR_INLINE flat_ptr& flat_ptr::operator=(const not_null_flat_ptr& other)
        PHI_NOEXCEPT
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    m_Pointer = const_cast<void*>(other.get());

    return *this;
}

PHI_EXTENDED_CONSTEXPR_OR_INLINE flat_ptr& flat_ptr::operator=(not_null_flat_ptr&& other)
        PHI_NOEXCEPT
{
    m_Pointer = other.get();

    return *this;
}

PHI_EXTENDED_CONSTEXPR not_null_flat_ptr flat_ptr::release_not_null() const PHI_NOEXCEPT
{
    PHI_ASSERT(m_Pointer != nullptr, "Trying to release nullptr to phi::not_null_flat_ptr");

    return {m_Pointer};
}

PHI_CONSTEXPR boolean operator==(const not_null_flat_ptr& lhs,
                                 const not_null_flat_ptr& rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs.get();
}

boolean operator==(const not_null_flat_ptr&, nullptr_t) = delete;

boolean operator==(nullptr_t, const not_null_flat_ptr&) = delete;

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(const not_null_flat_ptr& lhs,
                                                   const void*              rhs) PHI_NOEXCEPT
{
    return lhs.get() == rhs;
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator==(const void*              lhs,
                                                   const not_null_flat_ptr& rhs) PHI_NOEXCEPT
{
    return lhs == rhs.get();
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const not_null_flat_ptr& lhs,
                                                   const not_null_flat_ptr& rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs.get();
}

boolean operator!=(const not_null_flat_ptr&, nullptr_t) = delete;

boolean operator!=(nullptr_t, const not_null_flat_ptr&) = delete;

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const not_null_flat_ptr& lhs,
                                                   const void*              rhs) PHI_NOEXCEPT
{
    return lhs.get() != rhs;
}

PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean operator!=(const void*              lhs,
                                                   const not_null_flat_ptr& rhs) PHI_NOEXCEPT
{
    return lhs != rhs.get();
}

PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR void swap(not_null_flat_ptr& lhs,
                                                   not_null_flat_ptr& rhs) PHI_NOEXCEPT
{
    lhs.swap(rhs);
}

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <>
struct hash<phi::flat_ptr>
{
    size_t operator()(const phi::flat_ptr& ptr) const PHI_NOEXCEPT
    {
        return std::hash<const void*>()(ptr.get());
    }
};

template <>
struct hash<phi::not_null_flat_ptr>
{
    size_t operator()(const phi::not_null_flat_ptr& ptr) const PHI_NOEXCEPT
    {
        return std::hash<const void*>()(ptr.get());
    }
};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_FLAT_PTR_HPP
