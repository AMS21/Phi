#ifndef INCG_PHI_CORE_SCOPEPTR_HPP
#define INCG_PHI_CORE_SCOPEPTR_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/TypeTraits.hpp"
#include "Phi/Core/Types.hpp"
#include <cstddef>
#include <type_traits>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class NotNullScopePtr;

template <typename TypeT>
class ScopePtr
{
public:
    using this_type       = ScopePtr<TypeT>;
    using not_null_type   = NotNullScopePtr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    constexpr ScopePtr() noexcept
        : m_Ptr(nullptr)
    {}

    constexpr explicit ScopePtr(std::nullptr_t) noexcept
        : m_Ptr(nullptr)
    {}

    constexpr explicit ScopePtr(TypeT* ptr) noexcept
        : m_Ptr(ptr)
    {}

    constexpr ScopePtr(ScopePtr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {}

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ScopePtr(ScopePtr<OtherT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {}

    constexpr ScopePtr(NotNullScopePtr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign from moved NotNullScopePtr");
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ScopePtr(NotNullScopePtr<OtherT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign from moved NotNullScopePtr");
    }

    ~ScopePtr() noexcept
    {
        clear();
    }

    constexpr ScopePtr<TypeT>& operator=(ScopePtr<TypeT>&& other) noexcept
    {
        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ScopePtr<TypeT>& operator=(ScopePtr<OtherT>&& other) noexcept
    {
        reset(other.leak_ptr());

        return *this;
    }

    constexpr ScopePtr<TypeT>& operator=(NotNullScopePtr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign from moved NotNullScopePtr");

        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ScopePtr<TypeT>& operator=(NotNullScopePtr<OtherT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign from moved NotNullScopePtr");

        reset(other.leak_ptr());

        return *this;
    }

    constexpr ScopePtr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        if (m_Ptr != ptr)
        {
            delete m_Ptr;
        }
        m_Ptr = ptr;

        return *this;
    }

    constexpr ScopePtr<TypeT>& operator=(std::nullptr_t) noexcept
    {
        clear();

        return *this;
    }

    void clear() noexcept
    {
        delete m_Ptr;
        m_Ptr = nullptr;
    }

    constexpr TypeT* leak_ptr() noexcept
    {
        TypeT* ptr = get();
        m_Ptr      = nullptr;

        return ptr;
    }

    constexpr NotNullScopePtr<TypeT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Can not release to NotNullScopePtr from nullptr");

        return NotNullScopePtr<TypeT>(leak_ptr());
    }

    template <typename OtherT>
    constexpr NotNullScopePtr<OtherT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Can not release to NotNullScopePtr from nullptr");

        return NotNullScopePtr<OtherT>(static_cast<OtherT*>(leak_ptr()));
    }

    void reset(TypeT* new_ptr) noexcept
    {
        delete m_Ptr;
        m_Ptr = new_ptr;
    }

    constexpr void swap(ScopePtr<TypeT>& other) noexcept
    {
        std::swap(m_Ptr, other.m_Ptr);
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr void swap(ScopePtr<OtherT>& other) noexcept
    {
        std::swap(m_Ptr, other.m_Ptr);
    }

    constexpr TypeT* get() noexcept
    {
        return m_Ptr;
    }

    constexpr const TypeT* get() const noexcept
    {
        return m_Ptr;
    }

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator Boolean() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator const TypeT*() const noexcept
    {
        return get();
    }

    constexpr explicit operator TypeT*() noexcept
    {
        return get();
    }

    TypeT* operator->()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    const TypeT* operator->() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    TypeT& operator*()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return *get();
    }

    const TypeT& operator*() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return *get();
    }

private:
    TypeT* m_Ptr;
};

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(const ScopePtr<LhsT>& lhs, const ScopePtr<RhsT>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
constexpr Boolean operator==(const ScopePtr<LhsT>& lhs, std::nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <typename RhsT>
constexpr Boolean operator==(std::nullptr_t, const ScopePtr<RhsT>& rhs) noexcept
{
    return rhs.get() == nullptr;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(const ScopePtr<LhsT>& lhs, const ScopePtr<RhsT>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
constexpr Boolean operator!=(const ScopePtr<LhsT>& lhs, std::nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

template <typename RhsT>
constexpr Boolean operator!=(std::nullptr_t, const ScopePtr<RhsT>& rhs) noexcept
{
    return rhs.get() != nullptr;
}

template <typename LhsT, typename RhsT>
constexpr void swap(ScopePtr<LhsT>& lhs, ScopePtr<RhsT>& rhs)
{
    lhs.swap(rhs);
}

/* NotNullScopePtr */

template <typename TypeT>
class NotNullScopePtr
{
public:
    using this_type       = NotNullScopePtr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    NotNullScopePtr() = delete;

    NotNullScopePtr(std::nullptr_t) = delete;

    constexpr explicit NotNullScopePtr(TypeT* ptr) noexcept
        : m_Ptr(ptr)
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
    }

    constexpr NotNullScopePtr(NotNullScopePtr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr NotNullScopePtr(NotNullScopePtr<OtherT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
    }

    ~NotNullScopePtr() noexcept
    {
        clear();
    }

    constexpr NotNullScopePtr<TypeT>& operator=(NotNullScopePtr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr NotNullScopePtr<TypeT>& operator=(NotNullScopePtr<OtherT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        reset(other.leak_ptr());

        return *this;
    }

    constexpr NotNullScopePtr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        if (m_Ptr != ptr)
        {
            delete m_Ptr;
        }
        m_Ptr = ptr;

        return *this;
    }

    NotNullScopePtr<TypeT>& operator=(std::nullptr_t) = delete;

    TypeT* leak_ptr() noexcept
    {
        return std::exchange(m_Ptr, nullptr);
    }

    void reset(TypeT* new_ptr) noexcept
    {
        PHI_DBG_ASSERT(new_ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        delete m_Ptr;
        m_Ptr = new_ptr;
    }

    void reset(std::nullptr_t) = delete;

    constexpr void swap(NotNullScopePtr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        std::swap(m_Ptr, other.m_Ptr);
    }

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr void swap(NotNullScopePtr<OtherT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        std::swap(m_Ptr, other.m_Ptr);
    }

    operator bool() = delete;

    operator Boolean() = delete;

    constexpr TypeT* get() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Accessing phi::NotNullScopePtr after it was deleted");

        return m_Ptr;
    }

    constexpr const TypeT* get() const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Accessing phi::NotNullScopePtr after it was deleted");

        return m_Ptr;
    }

    constexpr explicit operator const TypeT*() const noexcept
    {
        return get();
    }

    constexpr explicit operator TypeT*() noexcept
    {
        return get();
    }

    TypeT* operator->()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    const TypeT* operator->() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    TypeT& operator*()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return *get();
    }

    const TypeT& operator*() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return *get();
    }

private:
    void clear() noexcept
    {
        delete m_Ptr;
        m_Ptr = nullptr;
    }

private:
    TypeT* m_Ptr;
};

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(const NotNullScopePtr<LhsT>& lhs,
                             const NotNullScopePtr<RhsT>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
Boolean operator==(const NotNullScopePtr<LhsT>& lhs, std::nullptr_t) = delete;

template <typename RhsT>
Boolean operator==(std::nullptr_t, const NotNullScopePtr<RhsT>& rhs) = delete;

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(const NotNullScopePtr<LhsT>& lhs,
                             const NotNullScopePtr<RhsT>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
Boolean operator!=(const NotNullScopePtr<LhsT>& lhs, std::nullptr_t) = delete;

template <typename RhsT>
Boolean operator!=(std::nullptr_t, const NotNullScopePtr<RhsT>& rhs) = delete;

template <typename LhsT, typename RhsT>
constexpr void swap(NotNullScopePtr<LhsT>& lhs, NotNullScopePtr<RhsT>& rhs)
{
    lhs.swap(rhs);
}

// make functions

template <typename TypeT, typename... ArgsT>
[[nodiscard]] std::enable_if_t<!std::is_array<TypeT>::value, ScopePtr<TypeT>> make_scope(
        ArgsT&&... args)
{
    return ScopePtr<TypeT>(new TypeT(std::forward<ArgsT>(args)...));
}

template <typename TypeT>
[[nodiscard]] std::enable_if_t<is_unbounded_array_v<TypeT>, ScopePtr<TypeT>> make_scope(
        phi::usize size)
{
    return ScopePtr<TypeT>(new typename std::remove_extent<TypeT>::type[size.get()]());
}

template <typename TypeT, typename... ArgsT>
std::enable_if_t<is_bounded_array_v<TypeT>, ScopePtr<TypeT>> make_scope(ArgsT&&... args) = delete;

template <typename TypeT>
[[nodiscard]] std::enable_if_t<!std::is_array<TypeT>::value, ScopePtr<TypeT>>
make_scope_for_overwrite()
{
    return ScopePtr<TypeT>(new TypeT);
}

template <typename TypeT>
[[nodiscard]] std::enable_if_t<is_unbounded_array_v<TypeT>, ScopePtr<TypeT>>
make_scope_for_overwrite(phi::usize size)
{
    return ScopePtr<TypeT>(new typename std::remove_extent<TypeT>::type[size.get()]);
}

template <typename TypeT, typename... ArgsT>
std::enable_if_t<is_bounded_array_v<TypeT>, ScopePtr<TypeT>> make_scope_for_overwrite(
        ArgsT&&... args) = delete;

template <typename TypeT, typename... ArgsT>
[[nodiscard]] std::enable_if_t<!std::is_array<TypeT>::value, NotNullScopePtr<TypeT>>
make_not_null_scope(ArgsT&&... args)
{
    return NotNullScopePtr<TypeT>(new TypeT(std::forward<ArgsT>(args)...));
}

template <typename TypeT>
[[nodiscard]] std::enable_if_t<is_unbounded_array_v<TypeT>, NotNullScopePtr<TypeT>>
make_not_null_scope(phi::usize size)
{
    return NotNullScopePtr<TypeT>(new typename std::remove_extent<TypeT>::type[size.get()]());
}

template <typename TypeT, typename... ArgsT>
std::enable_if_t<is_bounded_array_v<TypeT>, NotNullScopePtr<TypeT>> make_not_null_scope(
        ArgsT&&... args) = delete;

template <typename TypeT>
[[nodiscard]] std::enable_if_t<!std::is_array<TypeT>::value, NotNullScopePtr<TypeT>>
make_not_null_scope_for_overwrite()
{
    return NotNullScopePtr<TypeT>(new TypeT);
}

template <typename TypeT>
[[nodiscard]] std::enable_if_t<is_unbounded_array_v<TypeT>, NotNullScopePtr<TypeT>>
make_not_null_scope_for_overwrite(phi::usize size)
{
    return NotNullScopePtr<TypeT>(new typename std::remove_extent<TypeT>::type[size.get()]);
}

template <typename TypeT, typename... ArgsT>
std::enable_if_t<is_bounded_array_v<TypeT>, NotNullScopePtr<TypeT>>
make_not_null_scope_for_overwrite(ArgsT&&... args) = delete;

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename TypeT>
    struct hash<phi::ScopePtr<TypeT>>
    {
        std::size_t operator()(phi::ScopePtr<TypeT> ptr) const noexcept
        {
            return std::hash<TypeT*>()(ptr.get());
        }
    };

    template <typename TypeT>
    struct hash<phi::NotNullScopePtr<TypeT>>
    {
        std::size_t operator()(phi::NotNullScopePtr<TypeT> ptr) const noexcept
        {
            return std::hash<TypeT*>()(ptr.get());
        }
    };
} // namespace std

#endif // INCG_PHI_CORE_SCOPEPTR_HPP
