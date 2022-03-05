#ifndef INCG_PHI_CORE_OBSERVER_PTR_HPP
#define INCG_PHI_CORE_OBSERVER_PTR_HPP

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
#include "phi/core/forward.hpp"
#include "phi/core/move.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_convertible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class not_null_observer_ptr;

// A non owning smart pointer
template <typename TypeT>
class observer_ptr
{
public:
    using this_type       = observer_ptr<TypeT>;
    using not_null_type   = not_null_observer_ptr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    constexpr observer_ptr() noexcept
        : m_Ptr(nullptr)
    {}

    constexpr observer_ptr(nullptr_t) noexcept
        : m_Ptr(nullptr)
    {}

    constexpr observer_ptr(TypeT* ptr) noexcept
        : m_Ptr(ptr)
    {}

    constexpr observer_ptr(const observer_ptr<TypeT>& other) noexcept
        : m_Ptr(other.get())
    {}

    constexpr observer_ptr(observer_ptr<TypeT>&& other) noexcept
        : m_Ptr(move(other.get()))
    {}

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    constexpr observer_ptr(observer_ptr<OtherT> other) noexcept
        : m_Ptr(other.get())
    {}

    PHI_EXTENDED_CONSTEXPR observer_ptr(const not_null_observer_ptr<TypeT>& other) noexcept
        : m_Ptr(other.get())
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::not_null_observer_ptr");
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr(not_null_observer_ptr<TypeT>&& other) noexcept
        : m_Ptr(move(other.get()))
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::not_null_observer_ptr");
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr(const not_null_observer_ptr<OtherT>& other) noexcept
        : m_Ptr(other.get())
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::not_null_observer_ptr");
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr(not_null_observer_ptr<OtherT>&& other) noexcept
        : m_Ptr(move(other.get()))
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::not_null_observer_ptr");
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(const observer_ptr<TypeT>& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(observer_ptr<TypeT>&& other) noexcept
    {
        m_Ptr = move(other.m_Ptr);

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(
            const observer_ptr<OtherT>& other) noexcept
    {
        m_Ptr = other.m_Ptr;

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(observer_ptr<OtherT>&& other) noexcept
    {
        m_Ptr = move(other.m_Ptr);

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(
            const not_null_observer_ptr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::not_null_observer_ptr");

        m_Ptr = other.get();

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(
            not_null_observer_ptr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::not_null_observer_ptr");

        m_Ptr = move(other.get());

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(
            const not_null_observer_ptr<OtherT>& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::not_null_observer_ptr");

        m_Ptr = other.get();

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(
            not_null_observer_ptr<OtherT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Assign nullptr from phi::not_null_observer_ptr");

        m_Ptr = move(other.get());

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(nullptr_t) noexcept
    {
        m_Ptr = nullptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR observer_ptr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        m_Ptr = ptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator*() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR TypeT* operator->() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr operator boolean() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator TypeT*() const noexcept
    {
        return get();
    }

    PHI_NODISCARD constexpr TypeT* get() const noexcept
    {
        return m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR TypeT* release() noexcept
    {
        TypeT* ptr = m_Ptr;
        reset();
        return ptr;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot release to not null with nullptr");

        return not_null_observer_ptr<TypeT>(release());
    }

    template <typename OtherT>
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<OtherT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot release to not null with nullptr");

        return not_null_observer_ptr<OtherT>(static_cast<OtherT*>(release()));
    }

    PHI_EXTENDED_CONSTEXPR void reset(TypeT* ptr = nullptr) noexcept
    {
        m_Ptr = ptr;
    }

    PHI_EXTENDED_CONSTEXPR void swap(observer_ptr& other) noexcept
    {
        phi::swap(m_Ptr, other.m_Ptr);
    }

private:
    TypeT* m_Ptr;
};

template <typename LhsT, typename RhsT>
constexpr boolean operator==(observer_ptr<LhsT> lhs, observer_ptr<RhsT> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
constexpr boolean operator==(observer_ptr<LhsT> lhs, nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <typename RhsT>
constexpr boolean operator==(nullptr_t, observer_ptr<RhsT> rhs) noexcept
{
    return rhs.get() == nullptr;
}

template <typename LhsT, typename RhsT>
constexpr boolean operator==(observer_ptr<LhsT> lhs, not_null_observer_ptr<RhsT> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT, typename RhsT>
constexpr boolean operator==(not_null_observer_ptr<LhsT> lhs, observer_ptr<RhsT> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT, typename RhsT>
constexpr boolean operator!=(observer_ptr<LhsT> lhs, observer_ptr<RhsT> rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
constexpr boolean operator!=(observer_ptr<LhsT> lhs, nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

template <typename RhsT>
constexpr boolean operator!=(nullptr_t, observer_ptr<RhsT> rhs) noexcept
{
    return rhs.get() != nullptr;
}

template <typename LhsT, typename RhsT>
constexpr boolean operator!=(observer_ptr<LhsT> lhs, not_null_observer_ptr<RhsT> rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT, typename RhsT>
constexpr boolean operator!=(not_null_observer_ptr<LhsT> lhs, observer_ptr<RhsT> rhs) noexcept
{
    return lhs.get() != rhs.get();
}

// A non owning smart pointer which may not be null
template <typename TypeT>
class not_null_observer_ptr
{
public:
    using this_type       = not_null_observer_ptr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    not_null_observer_ptr() = delete;

    not_null_observer_ptr(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(TypeT* ptr) noexcept
        : m_Ptr(ptr)
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr.");
    }

    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(const not_null_observer_ptr<TypeT>& other) noexcept
        : m_Ptr(other.get())
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_observer_ptr.");
    }

    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(not_null_observer_ptr<TypeT>&& other) noexcept
        : m_Ptr(move(other.get()))
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_observer_ptr.");
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr(not_null_observer_ptr<OtherT> other) noexcept
        : m_Ptr(other.get())
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_observer_ptr.");
    }

    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT>& operator=(
            const not_null_observer_ptr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_observer_ptr.");

        m_Ptr = other.m_Ptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT>& operator=(
            not_null_observer_ptr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_observer_ptr.");

        m_Ptr = move(other.m_Ptr);

        return *this;
    }

    not_null_observer_ptr<TypeT>& operator=(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr");

        m_Ptr = ptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator*() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return *m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR TypeT* operator->() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Cannot dereference a nullptr.");

        return get();
    }

    operator bool() = delete;

    operator boolean() = delete;

    constexpr explicit operator TypeT*() const noexcept
    {
        return get();
    }

    PHI_NODISCARD constexpr TypeT* get() const noexcept
    {
        return m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR void reset(TypeT* ptr) noexcept
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr");

        m_Ptr = ptr;
    }

    void reset(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR void swap(not_null_observer_ptr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr");
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_observer_ptr");

        phi::swap(m_Ptr, other.m_Ptr);
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR void swap(not_null_observer_ptr<OtherT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::not_null_observer_ptr");
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_observer_ptr");

        phi::swap(m_Ptr, other.m_Ptr);
    }

private:
    TypeT* m_Ptr;
};

template <typename LhsT, typename RhsT>
constexpr boolean operator==(not_null_observer_ptr<LhsT> lhs,
                             not_null_observer_ptr<RhsT> rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
boolean operator==(not_null_observer_ptr<LhsT>, nullptr_t) = delete;

template <typename RhsT>
boolean operator==(nullptr_t, not_null_observer_ptr<RhsT>) = delete;

template <typename LhsT, typename RhsT>
constexpr boolean operator!=(not_null_observer_ptr<LhsT> lhs,
                             not_null_observer_ptr<RhsT> rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
boolean operator!=(not_null_observer_ptr<LhsT>, nullptr_t) = delete;

template <typename RhsT>
boolean operator!=(nullptr_t, not_null_observer_ptr<RhsT>) = delete;

// make functions

template <typename TypeT>
PHI_NODISCARD constexpr observer_ptr<TypeT> make_observer(TypeT* ptr) noexcept
{
    return observer_ptr<TypeT>(ptr);
}

template <typename TypeT>
PHI_NODISCARD constexpr not_null_observer_ptr<TypeT> make_not_null_observer(TypeT* ptr) noexcept
{
    return not_null_observer_ptr<TypeT>(ptr);
}

template <typename TypeT>
not_null_observer_ptr<TypeT> make_not_null_observer(nullptr_t ptr) = delete;

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT>
struct hash<phi::observer_ptr<TypeT>>
{
    phi::size_t operator()(phi::observer_ptr<TypeT> ptr) const noexcept
    {
        return std::hash<TypeT*>()(ptr.get());
    }
};

template <typename TypeT>
struct hash<phi::not_null_observer_ptr<TypeT>>
{
    phi::size_t operator()(phi::not_null_observer_ptr<TypeT> ptr) const noexcept
    {
        return std::hash<TypeT*>()(ptr.get());
    }
};

template <>
struct hash<phi::not_null_observer_ptr<nullptr_t>>
{
    phi::size_t operator()(phi::not_null_observer_ptr<nullptr_t> ptr) = delete;
};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_OBSERVER_PTR_HPP
