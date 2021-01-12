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
class ScopePtr
{
public:
    using this_type       = ScopePtr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    constexpr ScopePtr() noexcept
        : m_Ptr(nullptr)
    {}

    constexpr ScopePtr(std::nullptr_t) noexcept
        : m_Ptr(nullptr)
    {}

    constexpr explicit ScopePtr(TypeT* pointer) noexcept
        : m_Ptr(pointer)
    {}

    constexpr ScopePtr(ScopePtr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {}

    template <typename OtherT, std::enable_if_t<std::is_convertible_v<OtherT*, TypeT*>> = 0>
    constexpr ScopePtr(ScopePtr<OtherT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {}

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

    constexpr ScopePtr<TypeT>& operator=(TypeT* pointer) noexcept
    {
        if (m_Ptr != pointer)
        {
            delete m_Ptr;
        }
        m_Ptr = pointer;

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

    TypeT* leak_ptr() noexcept
    {
        TypeT* pointer = get();
        m_Ptr          = nullptr;

        return pointer;
    }

    void reset(TypeT* new_pointer) noexcept
    {
        clear();
        m_Ptr = new_pointer;
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

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename TypeT>
    struct hash<phi::ScopePtr<TypeT>>
    {
        std::size_t operator()(phi::ScopePtr<TypeT> pointer) const noexcept
        {
            return std::hash<TypeT*>()(pointer.get());
        }
    };
} // namespace std

#endif // INCG_PHI_CORE_SCOPEPTR_HPP
