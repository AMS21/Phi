#ifndef INCG_PHI_CORE_SCOPEPTR_HPP
#define INCG_PHI_CORE_SCOPEPTR_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/Algorithm/Exchange.hpp"
#include "Phi/Algorithm/Swap.hpp"
#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/Core/Nullptr.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/Core/Types.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/is_array.hpp"
#include "Phi/TypeTraits/is_bounded_array.hpp"
#include "Phi/TypeTraits/is_convertible.hpp"
#include "Phi/TypeTraits/is_unbounded_array.hpp"
#include "Phi/TypeTraits/remove_extent.hpp"

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

    constexpr explicit ScopePtr(nullptr_t) noexcept
        : m_Ptr(nullptr)
    {}

    constexpr explicit ScopePtr(TypeT* ptr) noexcept
        : m_Ptr(ptr)
    {}

    constexpr ScopePtr(ScopePtr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {}

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    constexpr ScopePtr(ScopePtr<OtherT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {}

    PHI_EXTENDED_CONSTEXPR ScopePtr(NotNullScopePtr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign from moved NotNullScopePtr");
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR ScopePtr(NotNullScopePtr<OtherT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign from moved NotNullScopePtr");
    }

    PHI_CONSTEXPR_DESTRUCTOR ~ScopePtr() noexcept
    {
        clear();
    }

    PHI_EXTENDED_CONSTEXPR ScopePtr<TypeT>& operator=(ScopePtr<TypeT>&& other) noexcept
    {
        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR ScopePtr<TypeT>& operator=(ScopePtr<OtherT>&& other) noexcept
    {
        reset(other.leak_ptr());

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR ScopePtr<TypeT>& operator=(NotNullScopePtr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign from moved NotNullScopePtr");

        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR ScopePtr<TypeT>& operator=(NotNullScopePtr<OtherT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign from moved NotNullScopePtr");

        reset(other.leak_ptr());

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR ScopePtr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        if (m_Ptr != ptr)
        {
            delete m_Ptr;
        }
        m_Ptr = ptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR ScopePtr<TypeT>& operator=(nullptr_t) noexcept
    {
        clear();

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR void clear() noexcept
    {
        delete m_Ptr;
        m_Ptr = nullptr;
    }

    PHI_EXTENDED_CONSTEXPR TypeT* leak_ptr() noexcept
    {
        TypeT* ptr = get();
        m_Ptr      = nullptr;

        return ptr;
    }

    PHI_EXTENDED_CONSTEXPR NotNullScopePtr<TypeT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Can not release to NotNullScopePtr from nullptr");

        return NotNullScopePtr<TypeT>(leak_ptr());
    }

    template <typename OtherT>
    PHI_EXTENDED_CONSTEXPR NotNullScopePtr<OtherT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Can not release to NotNullScopePtr from nullptr");

        return NotNullScopePtr<OtherT>(static_cast<OtherT*>(leak_ptr()));
    }

    PHI_EXTENDED_CONSTEXPR void reset(TypeT* new_ptr) noexcept
    {
        delete m_Ptr;
        m_Ptr = new_ptr;
    }

    PHI_EXTENDED_CONSTEXPR void swap(ScopePtr<TypeT>& other) noexcept
    {
        phi::swap(m_Ptr, other.m_Ptr);
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR void swap(ScopePtr<OtherT>& other) noexcept
    {
        phi::swap(m_Ptr, other.m_Ptr);
    }

    constexpr TypeT* get() noexcept
    {
        return m_Ptr;
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    constexpr const TypeT* get() const noexcept
    {
        return m_Ptr;
    }
#endif

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

    PHI_EXTENDED_CONSTEXPR TypeT* operator->()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator*()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return *get();
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const
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
constexpr Boolean operator==(const ScopePtr<LhsT>& lhs, nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <typename RhsT>
constexpr Boolean operator==(nullptr_t, const ScopePtr<RhsT>& rhs) noexcept
{
    return rhs.get() == nullptr;
}

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(const ScopePtr<LhsT>& lhs, const ScopePtr<RhsT>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
constexpr Boolean operator!=(const ScopePtr<LhsT>& lhs, nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

template <typename RhsT>
constexpr Boolean operator!=(nullptr_t, const ScopePtr<RhsT>& rhs) noexcept
{
    return rhs.get() != nullptr;
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

    NotNullScopePtr(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR explicit NotNullScopePtr(TypeT* ptr) noexcept
        : m_Ptr(ptr)
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
    }

    PHI_EXTENDED_CONSTEXPR NotNullScopePtr(NotNullScopePtr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR NotNullScopePtr(NotNullScopePtr<OtherT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
    }

    PHI_CONSTEXPR_DESTRUCTOR ~NotNullScopePtr() noexcept
    {
        clear();
    }

    PHI_EXTENDED_CONSTEXPR NotNullScopePtr<TypeT>& operator=(
            NotNullScopePtr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR NotNullScopePtr<TypeT>& operator=(
            NotNullScopePtr<OtherT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        reset(other.leak_ptr());

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR NotNullScopePtr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        if (m_Ptr != ptr)
        {
            delete m_Ptr;
        }
        m_Ptr = ptr;

        return *this;
    }

    NotNullScopePtr<TypeT>& operator=(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR TypeT* leak_ptr() noexcept
    {
        return exchange(m_Ptr, nullptr);
    }

    PHI_EXTENDED_CONSTEXPR void reset(TypeT* new_ptr) noexcept
    {
        PHI_DBG_ASSERT(new_ptr != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        delete m_Ptr;
        m_Ptr = new_ptr;
    }

    void reset(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR void swap(NotNullScopePtr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        phi::swap(m_Ptr, other.m_Ptr);
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR void swap(NotNullScopePtr<OtherT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign nullptr to phi::NotNullScopePtr");

        phi::swap(m_Ptr, other.m_Ptr);
    }

    operator bool() = delete;

    operator Boolean() = delete;

    PHI_EXTENDED_CONSTEXPR TypeT* get() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Accessing phi::NotNullScopePtr after it was deleted");

        return m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* get() const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Accessing phi::NotNullScopePtr after it was deleted");

        return m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR explicit operator const TypeT*() const noexcept
    {
        return get();
    }

    PHI_EXTENDED_CONSTEXPR explicit operator TypeT*() noexcept
    {
        return get();
    }

    PHI_EXTENDED_CONSTEXPR TypeT* operator->()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator*()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return *get();
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return *get();
    }

private:
    PHI_EXTENDED_CONSTEXPR void clear() noexcept
    {
        delete m_Ptr;
        m_Ptr = nullptr;
    }

    TypeT* m_Ptr;
};

template <typename LhsT, typename RhsT>
constexpr Boolean operator==(const NotNullScopePtr<LhsT>& lhs,
                             const NotNullScopePtr<RhsT>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
Boolean operator==(const NotNullScopePtr<LhsT>& lhs, nullptr_t) = delete;

template <typename RhsT>
Boolean operator==(nullptr_t, const NotNullScopePtr<RhsT>& rhs) = delete;

template <typename LhsT, typename RhsT>
constexpr Boolean operator!=(const NotNullScopePtr<LhsT>& lhs,
                             const NotNullScopePtr<RhsT>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
Boolean operator!=(const NotNullScopePtr<LhsT>& lhs, nullptr_t) = delete;

template <typename RhsT>
Boolean operator!=(nullptr_t, const NotNullScopePtr<RhsT>& rhs) = delete;

// make functions

template <typename TypeT, typename... ArgsT>
PHI_NODISCARD typename enable_if<!is_array<TypeT>::value, ScopePtr<TypeT>>::type make_scope(
        ArgsT&&... args)
{
    return ScopePtr<TypeT>(new TypeT(phi::forward<ArgsT>(args)...));
}

template <typename TypeT>
PHI_NODISCARD typename enable_if<is_unbounded_array<TypeT>::value, ScopePtr<TypeT>>::type
make_scope(phi::usize size)
{
    return ScopePtr<TypeT>(new typename remove_extent<TypeT>::type[size.get()]());
}

template <typename TypeT, typename... ArgsT>
typename enable_if<is_bounded_array<TypeT>::value, ScopePtr<TypeT>>::type make_scope(
        ArgsT&&... args) = delete;

template <typename TypeT>
PHI_NODISCARD typename enable_if<!is_array<TypeT>::value, ScopePtr<TypeT>>::type
make_scope_for_overwrite()
{
    return ScopePtr<TypeT>(new TypeT);
}

template <typename TypeT>
PHI_NODISCARD typename enable_if<is_unbounded_array<TypeT>::value, ScopePtr<TypeT>>::type
make_scope_for_overwrite(phi::usize size)
{
    return ScopePtr<TypeT>(new typename remove_extent<TypeT>::type[size.get()]);
}

template <typename TypeT, typename... ArgsT>
typename enable_if<is_bounded_array<TypeT>::value, ScopePtr<TypeT>>::type make_scope_for_overwrite(
        ArgsT&&... args) = delete;

template <typename TypeT, typename... ArgsT>
PHI_NODISCARD typename enable_if<!is_array<TypeT>::value, NotNullScopePtr<TypeT>>::type
make_not_null_scope(ArgsT&&... args)
{
    return NotNullScopePtr<TypeT>(new TypeT(phi::forward<ArgsT>(args)...));
}

template <typename TypeT>
PHI_NODISCARD typename enable_if<is_unbounded_array<TypeT>::value, NotNullScopePtr<TypeT>>::type
make_not_null_scope(phi::usize size)
{
    return NotNullScopePtr<TypeT>(new typename remove_extent<TypeT>::type[size.get()]());
}

template <typename TypeT, typename... ArgsT>
typename enable_if<is_bounded_array<TypeT>::value, NotNullScopePtr<TypeT>>::type
make_not_null_scope(ArgsT&&... args) = delete;

template <typename TypeT>
PHI_NODISCARD typename enable_if<!is_array<TypeT>::value, NotNullScopePtr<TypeT>>::type
make_not_null_scope_for_overwrite()
{
    return NotNullScopePtr<TypeT>(new TypeT);
}

template <typename TypeT>
PHI_NODISCARD typename enable_if<is_unbounded_array<TypeT>::value, NotNullScopePtr<TypeT>>::type
make_not_null_scope_for_overwrite(phi::usize size)
{
    return NotNullScopePtr<TypeT>(new typename remove_extent<TypeT>::type[size.get()]);
}

template <typename TypeT, typename... ArgsT>
typename enable_if<is_bounded_array<TypeT>::value, NotNullScopePtr<TypeT>>::type
make_not_null_scope_for_overwrite(ArgsT&&... args) = delete;

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename TypeT>
    struct hash<phi::ScopePtr<TypeT>>
    {
        phi::size_t operator()(phi::ScopePtr<TypeT> ptr) const noexcept
        {
            return std::hash<TypeT*>()(ptr.get());
        }
    };

    template <typename TypeT>
    struct hash<phi::NotNullScopePtr<TypeT>>
    {
        phi::size_t operator()(phi::NotNullScopePtr<TypeT> ptr) const noexcept
        {
            return std::hash<TypeT*>()(ptr.get());
        }
    };

    template <>
    struct hash<phi::NotNullScopePtr<phi::nullptr_t>>
    {
        phi::size_t operator()(phi::NotNullScopePtr<phi::nullptr_t> ptr) = delete;
    };
} // namespace std

#endif // INCG_PHI_CORE_SCOPEPTR_HPP
