#ifndef INCG_PHI_OBSERVERPTR_HPP
#define INCG_PHI_OBSERVERPTR_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class NotNullObserverPtr;

// A non owning smart pointer
template <typename TypeT>
class ObserverPtr
{
public:
    using this_type       = ObserverPtr<TypeT>;
    using not_null_type   = NotNullObserverPtr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    constexpr ObserverPtr() noexcept
        : m_Ptr(nullptr)
    {}

    constexpr ObserverPtr(std::nullptr_t) noexcept
        : m_Ptr(nullptr)
    {}

    constexpr ObserverPtr(TypeT* ptr) noexcept
        : m_Ptr(ptr)
    {}

    constexpr ObserverPtr(const ObserverPtr<TypeT>& other) noexcept
        : m_Ptr(other.get())
    {}

    constexpr ObserverPtr(ObserverPtr<TypeT>&& other) noexcept
        : m_Ptr(std::move(other.get()))
    {}

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ObserverPtr(ObserverPtr<OtherT> other) noexcept
        : m_Ptr(other.get())
    {}

    constexpr ObserverPtr(const NotNullObserverPtr<TypeT>& other) noexcept
        : m_Ptr(other.get())
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::NotNullObserverPtr");
    }

    constexpr ObserverPtr(NotNullObserverPtr<TypeT>&& other) noexcept
        : m_Ptr(std::move(other.get()))
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::NotNullObserverPtr");
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ObserverPtr(const NotNullObserverPtr<OtherT>& other) noexcept
        : m_Ptr(other.get())
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::NotNullObserverPtr");
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ObserverPtr(NotNullObserverPtr<OtherT>&& other) noexcept
        : m_Ptr(std::move(other.get()))
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::NotNullObserverPtr");
    }

    constexpr ObserverPtr<TypeT>& operator=(const ObserverPtr<TypeT>& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    constexpr ObserverPtr<TypeT>& operator=(ObserverPtr<TypeT>&& other) noexcept
    {
        m_Ptr = std::move(other.m_Ptr);

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ObserverPtr<TypeT>& operator=(const ObserverPtr<OtherT>& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ObserverPtr<TypeT>& operator=(ObserverPtr<OtherT>&& other) noexcept
    {
        m_Ptr = std::move(other.m_Ptr);

        return *this;
    }

    constexpr ObserverPtr<TypeT>& operator=(const NotNullObserverPtr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::NotNullObserverPtr");

        m_Ptr = other.get();

        return *this;
    }

    constexpr ObserverPtr<TypeT>& operator=(NotNullObserverPtr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::NotNullObserverPtr");

        m_Ptr = std::move(other.get());

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ObserverPtr<TypeT>& operator=(const NotNullObserverPtr<OtherT>& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::NotNullObserverPtr");

        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ObserverPtr<TypeT>& operator=(NotNullObserverPtr<OtherT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::NotNullObserverPtr");

        m_Ptr = std::move(other.get());

        return *this;
    }

    constexpr ObserverPtr<TypeT>& operator=(std::nullptr_t) noexcept
    {
        m_Ptr = nullptr;

        return *this;
    }

    constexpr ObserverPtr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        m_Ptr = ptr;

        return *this;
    }

    constexpr TypeT& operator*() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    constexpr const TypeT& operator*() const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    constexpr TypeT* operator->() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    constexpr const TypeT* operator->() const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr operator Boolean() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator TypeT*() const noexcept
    {
        return get();
    }

    [[nodiscard]] constexpr TypeT* get() const noexcept
    {
        return m_Ptr;
    }

    constexpr TypeT* release() noexcept
    {
        TypeT* ptr = m_Ptr;
        reset();
        return ptr;
    }

    [[nodiscard]] constexpr NotNullObserverPtr<TypeT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot release to not null with nullptr");

        return NotNullObserverPtr<TypeT>(release());
    }

    template <typename OtherT>
    [[nodiscard]] constexpr NotNullObserverPtr<OtherT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot release to not null with nullptr");

        return NotNullObserverPtr<OtherT>(static_cast<OtherT*>(release()));
    }

    constexpr void reset(TypeT* ptr = nullptr) noexcept
    {
        m_Ptr = ptr;
    }

    constexpr void swap(ObserverPtr& other) noexcept
    {
        std::swap(m_Ptr, other.m_Ptr);
    }

private:
    TypeT* m_Ptr;
};

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(ObserverPtr<LhsT> lhs, ObserverPtr<RhsT> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
constexpr Boolean operator==(ObserverPtr<LhsT> lhs, std::nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <typename RhsT>
constexpr Boolean operator==(std::nullptr_t, ObserverPtr<RhsT> rhs) noexcept
{
    return rhs.get() == nullptr;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(ObserverPtr<LhsT> lhs, NotNullObserverPtr<RhsT> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(NotNullObserverPtr<LhsT> lhs, ObserverPtr<RhsT> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(ObserverPtr<LhsT> lhs, ObserverPtr<RhsT> rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
constexpr Boolean operator!=(ObserverPtr<LhsT> lhs, std::nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

template <typename RhsT>
constexpr Boolean operator!=(std::nullptr_t, ObserverPtr<RhsT> rhs) noexcept
{
    return rhs.get() != nullptr;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(ObserverPtr<LhsT> lhs, NotNullObserverPtr<RhsT> rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(NotNullObserverPtr<LhsT> lhs, ObserverPtr<RhsT> rhs) noexcept
{
    return lhs.get() != rhs.get();
}

// A non owning smart pointer which may not be null
template <typename TypeT>
class NotNullObserverPtr
{
public:
    using this_type       = NotNullObserverPtr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    NotNullObserverPtr() = delete;

    NotNullObserverPtr(std::nullptr_t) = delete;

    constexpr NotNullObserverPtr(TypeT* ptr) noexcept
        : m_Ptr(ptr)
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullObserverPtr.");
    }

    constexpr NotNullObserverPtr(const NotNullObserverPtr<TypeT>& other) noexcept
        : m_Ptr(other.get())
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::NotNullObserverPtr.");
    }

    constexpr NotNullObserverPtr(NotNullObserverPtr<TypeT>&& other) noexcept
        : m_Ptr(std::move(other.get()))
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::NotNullObserverPtr.");
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr NotNullObserverPtr(NotNullObserverPtr<OtherT> other) noexcept
        : m_Ptr(other.get())
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::NotNullObserverPtr.");
    }

    constexpr NotNullObserverPtr<TypeT>& operator=(const NotNullObserverPtr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::NotNullObserverPtr.");

        m_Ptr = other.m_Ptr;

        return *this;
    }

    constexpr NotNullObserverPtr<TypeT>& operator=(NotNullObserverPtr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::NotNullObserverPtr.");

        m_Ptr = std::move(other.m_Ptr);

        return *this;
    }

    NotNullObserverPtr<TypeT>& operator=(std::nullptr_t) = delete;

    constexpr NotNullObserverPtr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullObserverPtr");

        m_Ptr = ptr;

        return *this;
    }

    constexpr TypeT& operator*() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    constexpr const TypeT& operator*() const noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    constexpr TypeT* operator->() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    constexpr const TypeT* operator->() const noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    operator bool() = delete;

    operator Boolean() = delete;

    constexpr explicit operator TypeT*() const noexcept
    {
        return get();
    }

    [[nodiscard]] constexpr TypeT* get() const noexcept
    {
        return m_Ptr;
    }

    constexpr void reset(TypeT* ptr) noexcept
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullObserverPtr");

        m_Ptr = ptr;
    }

    void reset(std::nullptr_t) = delete;

    constexpr void swap(NotNullObserverPtr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::NotNullObserverPtr");
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::NotNullObserverPtr");

        std::swap(m_Ptr, other.m_Ptr);
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr void swap(NotNullObserverPtr<OtherT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::NotNullObserverPtr");
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::NotNullObserverPtr");

        std::swap(m_Ptr, other.m_Ptr);
    }

private:
    TypeT* m_Ptr;
};

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(NotNullObserverPtr<LhsT> lhs, NotNullObserverPtr<RhsT> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
Boolean operator==(NotNullObserverPtr<LhsT>, std::nullptr_t) = delete;

template <typename RhsT>
Boolean operator==(std::nullptr_t, NotNullObserverPtr<RhsT>) = delete;

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(NotNullObserverPtr<LhsT> lhs, NotNullObserverPtr<RhsT> rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
Boolean operator!=(NotNullObserverPtr<LhsT>, std::nullptr_t) = delete;

template <typename RhsT>
Boolean operator!=(std::nullptr_t, NotNullObserverPtr<RhsT>) = delete;

// make functions

template <typename TypeT>
[[nodiscard]] constexpr ObserverPtr<TypeT> make_observer(TypeT* ptr) noexcept
{
    return ObserverPtr<TypeT>(ptr);
}

template <typename TypeT>
[[nodiscard]] constexpr NotNullObserverPtr<TypeT> make_not_null_observer(TypeT* ptr) noexcept
{
    return NotNullObserverPtr<TypeT>(ptr);
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename TypeT>
    struct hash<phi::ObserverPtr<TypeT>>
    {
        std::size_t operator()(phi::ObserverPtr<TypeT> ptr) const noexcept
        {
            return std::hash<TypeT*>()(ptr.get());
        }
    };

    template <typename TypeT>
    struct hash<phi::NotNullObserverPtr<TypeT>>
    {
        std::size_t operator()(phi::NotNullObserverPtr<TypeT> ptr) const noexcept
        {
            return std::hash<TypeT*>()(ptr.get());
        }
    };
} // namespace std

#endif // INCG_PHI_OBSERVERPTR_HPP
