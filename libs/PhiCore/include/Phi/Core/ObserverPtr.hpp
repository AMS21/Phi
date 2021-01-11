#ifndef INCG_PHI_OBSERVERPTR_HPP
#define INCG_PHI_OBSERVERPTR_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

// A non owning smart pointer
template <typename TypeT>
class ObserverPtr
{
public:
    using this_type       = ObserverPtr<TypeT>;
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

    constexpr ObserverPtr(TypeT* pointer) noexcept
        : m_Ptr(pointer)
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

    constexpr ObserverPtr<TypeT>& operator=(std::nullptr_t) noexcept
    {
        m_Ptr = nullptr;

        return *this;
    }

    constexpr ObserverPtr<TypeT>& operator=(TypeT* pointer) noexcept
    {
        m_Ptr = pointer;

        return *this;
    }

    constexpr TypeT& operator*() const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    constexpr TypeT* operator->() const noexcept
    {
        return get();
    }

    constexpr operator bool() const noexcept
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

    constexpr TypeT* get() const noexcept
    {
        return m_Ptr;
    }

    constexpr TypeT* release() noexcept
    {
        TypeT* pointer = m_Ptr;
        reset();
        return pointer;
    }

    constexpr void reset(TypeT* pointer = nullptr) noexcept
    {
        m_Ptr = pointer;
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

template <typename TypeT>
[[nodiscard]] constexpr ObserverPtr<TypeT> make_observer(TypeT* pointer) noexcept
{
    return ObserverPtr<TypeT>(pointer);
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename TypeT>
    struct hash<phi::ObserverPtr<TypeT>>
    {
        std::size_t operator()(phi::ObserverPtr<TypeT> pointer) const noexcept
        {
            return std::hash<TypeT*>()(pointer.get());
        }
    };
} // namespace std

#endif // INCG_PHI_OBSERVERPTR_HPP
