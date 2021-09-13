#ifndef INCG_PHI_CORE_FLAT_PTR_HPP
#define INCG_PHI_CORE_FLAT_PTR_HPP

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core//Nullptr.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/PhiConfig.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/is_pointer.hpp"
#include <cstdint>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

class NotNullFlatPtr;

class FlatPtr
{
public:
    using this_type     = FlatPtr;
    using not_null_type = NotNullFlatPtr;
    using value_type    = void*;

    constexpr FlatPtr() noexcept
        : m_Ptr(nullptr)
    {}

    constexpr FlatPtr(nullptr_t) noexcept
        : m_Ptr(nullptr)
    {}

    template <typename PtrT, enable_if_t<is_pointer_v<PtrT>, bool> = true>
    constexpr FlatPtr(PtrT ptr) noexcept
        : m_Ptr(static_cast<void*>(ptr))
    {}

    constexpr FlatPtr(const FlatPtr& other) noexcept
        : m_Ptr(other.m_Ptr)
    {}

    constexpr FlatPtr(FlatPtr&& other) noexcept
        : m_Ptr(other.get())
    {}

    constexpr FlatPtr(const NotNullFlatPtr& other) noexcept;

    constexpr FlatPtr(NotNullFlatPtr&& other) noexcept;

    constexpr FlatPtr& operator=(nullptr_t) noexcept
    {
        m_Ptr = nullptr;

        return *this;
    }

    ~FlatPtr() = default;

    template <typename PtrT, enable_if_t<is_pointer_v<PtrT>, bool> = true>
    constexpr FlatPtr& operator=(PtrT ptr) noexcept
    {
        m_Ptr = static_cast<void*>(ptr);

        return *this;
    }

    constexpr FlatPtr& operator=(const FlatPtr& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    constexpr FlatPtr& operator=(FlatPtr&& other) noexcept
    {
        m_Ptr = other.get();

        return *this;
    }

    constexpr FlatPtr& operator=(const NotNullFlatPtr& other) noexcept;

    constexpr FlatPtr& operator=(NotNullFlatPtr&& other) noexcept;

    constexpr void* get() noexcept
    {
        return m_Ptr;
    }

    PHI_NODISCARD constexpr const void* get() const noexcept
    {
        return m_Ptr;
    }

    PHI_NODISCARD constexpr NotNullFlatPtr release_not_null() const noexcept;

    constexpr void clear() noexcept
    {
        m_Ptr = nullptr;
    }

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator Boolean() const noexcept
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

    void swap(FlatPtr& other) noexcept
    {
        std::swap(m_Ptr, other.m_Ptr);
    }

    void* operator->() = delete;

    const void* operator->() const = delete;

    void operator*() = delete;

    void operator*() const = delete;

private:
    void* m_Ptr;
};

constexpr Boolean operator==(const FlatPtr& lhs, const FlatPtr& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

constexpr Boolean operator==(const FlatPtr& lhs, nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

constexpr Boolean operator==(nullptr_t, const FlatPtr& rhs) noexcept
{
    return rhs.get() == nullptr;
}

constexpr Boolean operator!=(const FlatPtr& lhs, const FlatPtr& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

constexpr Boolean operator!=(const FlatPtr& lhs, nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

constexpr Boolean operator!=(nullptr_t, const FlatPtr& rhs) noexcept
{
    return rhs.get() != nullptr;
}

inline void swap(FlatPtr& lhs, FlatPtr& rhs)
{
    lhs.swap(rhs);
}

class NotNullFlatPtr
{
public:
    using this_type  = NotNullFlatPtr;
    using value_type = void*;

    NotNullFlatPtr() = delete;

    NotNullFlatPtr(nullptr_t) = delete;

    template <typename PtrT, enable_if_t<is_pointer_v<PtrT>, bool> = true>
    constexpr NotNullFlatPtr(PtrT ptr) noexcept
        : m_Ptr(static_cast<void*>(ptr))
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullFlatPtr");
    }

    constexpr NotNullFlatPtr(const NotNullFlatPtr& other) noexcept
        : m_Ptr(other.m_Ptr)
    {}

    constexpr NotNullFlatPtr(NotNullFlatPtr&& other) noexcept
        : m_Ptr(other.m_Ptr)
    {}

    ~NotNullFlatPtr() = default;

    constexpr NotNullFlatPtr& operator=(nullptr_t) = delete;

    template <typename PtrT>
    constexpr NotNullFlatPtr& operator=(enable_if_t<is_pointer_v<PtrT>, PtrT> ptr) noexcept
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullFlatPtr");

        m_Ptr = static_cast<void*>(ptr);

        return *this;
    }

    constexpr NotNullFlatPtr& operator=(const NotNullFlatPtr& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    constexpr NotNullFlatPtr& operator=(NotNullFlatPtr&& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    PHI_NODISCARD constexpr void* get() noexcept
    {
        return m_Ptr;
    }

    PHI_NODISCARD constexpr const void* get() const noexcept
    {
        return m_Ptr;
    }

    constexpr explicit operator const void*() const noexcept
    {
        return get();
    }

    constexpr explicit operator void*() noexcept
    {
        return get();
    }

    void swap(NotNullFlatPtr& other) noexcept
    {
        std::swap(m_Ptr, other.m_Ptr);
    }

    void* operator->() = delete;

    const void* operator->() const = delete;

    void operator*() = delete;

    void operator*() const = delete;

private:
    void* m_Ptr;
};

constexpr FlatPtr::FlatPtr(const NotNullFlatPtr& other) noexcept
    : m_Ptr(const_cast<void*>(other.get()))
{}

constexpr FlatPtr::FlatPtr(NotNullFlatPtr&& other) noexcept
    : m_Ptr(other.get())
{}

constexpr FlatPtr& FlatPtr::operator=(const NotNullFlatPtr& other) noexcept
{
    m_Ptr = const_cast<void*>(other.get());

    return *this;
}

constexpr FlatPtr& FlatPtr::operator=(NotNullFlatPtr&& other) noexcept
{
    m_Ptr = other.get();

    return *this;
}

constexpr NotNullFlatPtr FlatPtr::release_not_null() const noexcept
{
    PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to release nullptr to phi::NotNullFlatPtr");

    return NotNullFlatPtr(m_Ptr);
}

constexpr Boolean operator==(const NotNullFlatPtr& lhs, const NotNullFlatPtr& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

Boolean operator==(const NotNullFlatPtr&, nullptr_t) = delete;

Boolean operator==(nullptr_t, const NotNullFlatPtr&) = delete;

constexpr Boolean operator!=(const NotNullFlatPtr& lhs, const NotNullFlatPtr& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

Boolean operator!=(const NotNullFlatPtr&, nullptr_t) = delete;

Boolean operator!=(nullptr_t, const NotNullFlatPtr&) = delete;

inline void swap(NotNullFlatPtr& lhs, NotNullFlatPtr& rhs) noexcept
{
    lhs.swap(rhs);
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <>
    struct hash<phi::FlatPtr>
    {
        std::size_t operator()(phi::FlatPtr ptr) const noexcept
        {
            return std::hash<void*>()(ptr.get());
        }
    };

    template <>
    struct hash<phi::NotNullFlatPtr>
    {
        std::size_t operator()(phi::NotNullFlatPtr ptr) const noexcept
        {
            return std::hash<void*>()(ptr.get());
        }
    };
} // namespace std

#endif // INCG_PHI_CORE_FLAT_PTR_HPP
