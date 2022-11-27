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
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_pointer.hpp"

PHI_EXTERNAL_HEADERS_BEGIN()
#include <utility>
PHI_EXTERNAL_HEADERS_END()

DETAIL_PHI_BEGIN_NAMESPACE()

class not_null_flat_ptr;

template <typename TypeT>
class observer_ptr;

template <typename TypeT>
class not_null_observer_ptr;

template <typename TypeT>
class ref_ptr;

template <typename TypeT>
class not_null_ref_ptr;

template <typename TypeT>
class scope_ptr;

template <typename TypeT>
class not_null_scope_ptr;

class PHI_ATTRIBUTE_POINTER flat_ptr
{
public:
    using this_type     = flat_ptr;
    using not_null_type = not_null_flat_ptr;
    using value_type    = void*;

    constexpr flat_ptr() noexcept
        : m_Pointer(nullptr)
    {}

    constexpr flat_ptr(nullptr_t) noexcept
        : m_Pointer(nullptr)
    {}

    template <typename PointerT, enable_if_t<is_pointer<PointerT>::value, bool> = true>
    constexpr flat_ptr(PointerT pointer) noexcept
        : m_Pointer(static_cast<void*>(pointer))
    {}

    template <typename TypeT>
    constexpr flat_ptr(observer_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    constexpr flat_ptr(not_null_observer_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    constexpr flat_ptr(ref_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    constexpr flat_ptr(not_null_ref_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    constexpr flat_ptr(scope_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    constexpr flat_ptr(not_null_scope_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}

    {}

    flat_ptr(const flat_ptr& other) = default;

    flat_ptr(flat_ptr&& other) = default;

    constexpr flat_ptr(const not_null_flat_ptr& other) noexcept;

    constexpr flat_ptr(not_null_flat_ptr&& other) noexcept;

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(nullptr_t) noexcept
    {
        m_Pointer = nullptr;

        return *this;
    }

    ~flat_ptr() = default;

    template <typename PointerT, enable_if_t<is_pointer<PointerT>::value, bool> = true>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(PointerT pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer);

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(observer_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_observer_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(ref_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_ref_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(scope_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_scope_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    flat_ptr& operator=(const flat_ptr& other) = default;

    flat_ptr& operator=(flat_ptr&& other) = default;

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(const not_null_flat_ptr& other) noexcept;

    PHI_EXTENDED_CONSTEXPR flat_ptr& operator=(not_null_flat_ptr&& other) noexcept;

    PHI_NODISCARD constexpr void* get() noexcept
    {
        return m_Pointer;
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD constexpr const void* get() const noexcept
    {
        return m_Pointer;
    }
#endif

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_flat_ptr release_not_null() const noexcept;

    PHI_EXTENDED_CONSTEXPR void clear() noexcept
    {
        m_Pointer = nullptr;
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
        phi::swap(m_Pointer, other.m_Pointer);
    }

    void* operator->() = delete;

    const void* operator->() const = delete;

    void operator*() = delete;

    void operator*() const = delete;

private:
    void* m_Pointer;
};

PHI_ALWAYS_INLINE constexpr boolean operator==(const flat_ptr& lhs, const flat_ptr& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

PHI_ALWAYS_INLINE constexpr boolean operator==(const flat_ptr& lhs, nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

PHI_ALWAYS_INLINE constexpr boolean operator==(nullptr_t, const flat_ptr& rhs) noexcept
{
    return rhs.get() == nullptr;
}

PHI_ALWAYS_INLINE constexpr boolean operator!=(const flat_ptr& lhs, const flat_ptr& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

PHI_ALWAYS_INLINE constexpr boolean operator!=(const flat_ptr& lhs, nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

PHI_ALWAYS_INLINE constexpr boolean operator!=(nullptr_t, const flat_ptr& rhs) noexcept
{
    return rhs.get() != nullptr;
}

PHI_EXTENDED_CONSTEXPR PHI_ALWAYS_INLINE void swap(flat_ptr& lhs, flat_ptr& rhs) noexcept
{
    lhs.swap(rhs);
}

// NOTE: The tautological compare warning is only valid if the compiler supports the non standard PHI_ATTRIBUTE_NONNULLL. The assert is a more generalized way to ensure that we don't get any null pointers
PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wtautological-pointer-compare")
PHI_GCC_SUPPRESS_WARNING("-Wnonnull-compare")

class PHI_ATTRIBUTE_POINTER not_null_flat_ptr
{
public:
    using this_type  = not_null_flat_ptr;
    using value_type = void*;

    not_null_flat_ptr() = delete;

    not_null_flat_ptr(nullptr_t) = delete;

    template <typename PointerT, enable_if_t<is_pointer<PointerT>::value, bool> = true>
    PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR not_null_flat_ptr(PointerT pointer) noexcept
        : m_Pointer(static_cast<void*>(pointer))
    {
        PHI_ASSERT(pointer != nullptr, "Trying to assign nullptr to phi::not_null_flat_ptr");
    }

    template <typename TypeT>
    constexpr not_null_flat_ptr(not_null_observer_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    constexpr not_null_flat_ptr(not_null_ref_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    template <typename TypeT>
    constexpr not_null_flat_ptr(not_null_scope_ptr<TypeT>& pointer) noexcept
        : m_Pointer{static_cast<void*>(pointer.get())}
    {}

    not_null_flat_ptr(const not_null_flat_ptr&) = default;

    not_null_flat_ptr(not_null_flat_ptr&&) = default;

    ~not_null_flat_ptr() = default;

    not_null_flat_ptr& operator=(nullptr_t) = delete;

    template <typename PointerT>
    PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(
            enable_if_t<is_pointer<PointerT>::value, PointerT> pointer) noexcept
    {
        PHI_ASSERT(pointer != nullptr, "Trying to assign nullptr to phi::not_null_flat_ptr");

        m_Pointer = static_cast<void*>(pointer);

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(
            not_null_observer_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(not_null_ref_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    template <typename TypeT>
    PHI_EXTENDED_CONSTEXPR not_null_flat_ptr& operator=(not_null_scope_ptr<TypeT>& pointer) noexcept
    {
        m_Pointer = static_cast<void*>(pointer.get());

        return *this;
    }

    not_null_flat_ptr& operator=(const not_null_flat_ptr&) = default;

    not_null_flat_ptr& operator=(not_null_flat_ptr&&) = default;

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL constexpr void* get() noexcept
    {
        PHI_ASSERT(m_Pointer != nullptr, "Trying to get nullptr from phi::not_null_flat_ptr");

        return m_Pointer;
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL constexpr const void* get() const noexcept
    {
        PHI_ASSERT(m_Pointer != nullptr, "Trying to get nullptr from phi::not_null_flat_ptr");

        return m_Pointer;
    }
#endif

    PHI_ATTRIBUTE_RETURNS_NONNULL constexpr explicit operator const void*() const noexcept
    {
        return get();
    }

    PHI_ATTRIBUTE_RETURNS_NONNULL constexpr explicit operator void*() noexcept
    {
        return get();
    }

    PHI_EXTENDED_CONSTEXPR void swap(not_null_flat_ptr& other) noexcept
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

PHI_CLANG_SUPPRESS_WARNING_POP()

constexpr flat_ptr::flat_ptr(const not_null_flat_ptr& other) noexcept
    : m_Pointer(const_cast<void*>(other.get())) // NOLINT(cppcoreguidelines-pro-type-const-cast)
{}

constexpr flat_ptr::flat_ptr(not_null_flat_ptr&& other) noexcept
    : m_Pointer(other.get())
{}

PHI_EXTENDED_CONSTEXPR_OR_INLINE flat_ptr& flat_ptr::operator=(
        const not_null_flat_ptr& other) noexcept
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    m_Pointer = const_cast<void*>(other.get());

    return *this;
}

PHI_EXTENDED_CONSTEXPR_OR_INLINE flat_ptr& flat_ptr::operator=(not_null_flat_ptr&& other) noexcept
{
    m_Pointer = other.get();

    return *this;
}

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=pure")

PHI_EXTENDED_CONSTEXPR not_null_flat_ptr flat_ptr::release_not_null() const noexcept
{
    PHI_ASSERT(m_Pointer != nullptr, "Trying to release nullptr to phi::not_null_flat_ptr");

    return {m_Pointer};
}

PHI_GCC_SUPPRESS_WARNING_POP()

constexpr boolean operator==(const not_null_flat_ptr& lhs, const not_null_flat_ptr& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

boolean operator==(const not_null_flat_ptr&, nullptr_t) = delete;

boolean operator==(nullptr_t, const not_null_flat_ptr&) = delete;

PHI_ALWAYS_INLINE constexpr boolean operator!=(const not_null_flat_ptr& lhs,
                                               const not_null_flat_ptr& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

boolean operator!=(const not_null_flat_ptr&, nullptr_t) = delete;

boolean operator!=(nullptr_t, const not_null_flat_ptr&) = delete;

PHI_ALWAYS_INLINE PHI_EXTENDED_CONSTEXPR void swap(not_null_flat_ptr& lhs,
                                                   not_null_flat_ptr& rhs) noexcept
{
    lhs.swap(rhs);
}

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

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

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_FLAT_PTR_HPP
