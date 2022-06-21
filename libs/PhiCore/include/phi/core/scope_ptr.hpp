#ifndef INCG_PHI_CORE_SCOPE_PTR_HPP
#define INCG_PHI_CORE_SCOPE_PTR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/exchange.hpp"
#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/core/types.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_array.hpp"
#include "phi/type_traits/is_bounded_array.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_unbounded_array.hpp"
#include "phi/type_traits/remove_extent.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class not_null_scope_ptr;

template <typename TypeT>
class observer_ptr;

template <typename TypeT>
class not_null_observer_ptr;

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wtautological-pointer-compare")
PHI_GCC_SUPPRESS_WARNING("-Wnonnull-compare")

template <typename TypeT>
class PHI_ATTRIBUTE_OWNER scope_ptr
{
public:
    using this_type       = scope_ptr<TypeT>;
    using not_null_type   = not_null_scope_ptr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    constexpr scope_ptr() noexcept
        : m_Ptr{nullptr}
    {}

    constexpr explicit scope_ptr(nullptr_t) noexcept
        : m_Ptr{nullptr}
    {}

    constexpr explicit scope_ptr(TypeT* ptr) noexcept
        : m_Ptr{ptr}
    {}

    scope_ptr(const scope_ptr<TypeT>&) = delete;

    constexpr scope_ptr(scope_ptr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {}

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    constexpr scope_ptr(scope_ptr<OtherT>&& other) noexcept
        : m_Ptr{other.leak_ptr()}
    {}

    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_EXTENDED_CONSTEXPR scope_ptr(not_null_scope_ptr<TypeT>&& other) noexcept
        : m_Ptr{other.leak_ptr()}
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign from moved not_null_scope_ptr");
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_EXTENDED_CONSTEXPR scope_ptr(not_null_scope_ptr<OtherT>&& other) noexcept
        : m_Ptr{other.leak_ptr()}
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign from moved not_null_scope_ptr");
    }

    PHI_CONSTEXPR_DESTRUCTOR ~scope_ptr() noexcept
    {
        clear();
    }

    scope_ptr<TypeT>& operator=(const scope_ptr<TypeT>&) = delete;

    PHI_EXTENDED_CONSTEXPR scope_ptr<TypeT>& operator=(scope_ptr<TypeT>&& other) noexcept
    {
        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR scope_ptr<TypeT>& operator=(scope_ptr<OtherT>&& other) noexcept
    {
        reset(other.leak_ptr());

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR scope_ptr<TypeT>& operator=(not_null_scope_ptr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign from moved not_null_scope_ptr");

        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR scope_ptr<TypeT>& operator=(not_null_scope_ptr<OtherT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr, "Trying to assign from moved not_null_scope_ptr");

        reset(other.leak_ptr());

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR scope_ptr<TypeT>& operator=(TypeT* ptr) noexcept
    {
        if (m_Ptr != ptr)
        {
            delete m_Ptr;
        }
        m_Ptr = ptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR scope_ptr<TypeT>& operator=(nullptr_t) noexcept
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

    PHI_NODISCARD constexpr observer_ptr<TypeT> observer() noexcept
    {
        return observer_ptr<TypeT>{get()};
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT> not_null_observer() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to create not_null_observer_ptr from nullptr");
        return not_null_observer_ptr<TypeT>{get()};
    }

    PHI_EXTENDED_CONSTEXPR not_null_scope_ptr<TypeT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Can not release to not_null_scope_ptr from nullptr");

        return not_null_scope_ptr<TypeT>(leak_ptr());
    }

    template <typename OtherT>
    PHI_EXTENDED_CONSTEXPR not_null_scope_ptr<OtherT> release_not_null() noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Can not release to not_null_scope_ptr from nullptr");

        return not_null_scope_ptr<OtherT>(static_cast<OtherT*>(leak_ptr()));
    }

    PHI_EXTENDED_CONSTEXPR void reset(TypeT* new_ptr) noexcept
    {
        delete m_Ptr;
        m_Ptr = new_ptr;
    }

    PHI_EXTENDED_CONSTEXPR void swap(scope_ptr<TypeT>& other) noexcept
    {
        phi::swap(m_Ptr, other.m_Ptr);
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR void swap(scope_ptr<OtherT>& other) noexcept
    {
        phi::swap(m_Ptr, other.m_Ptr);
    }

    PHI_NODISCARD constexpr TypeT* get() noexcept
    {
        return m_Ptr;
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD constexpr const TypeT* get() const noexcept
    {
        return m_Ptr;
    }
#endif

    constexpr explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    constexpr explicit operator boolean() const noexcept
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

    PHI_EXTENDED_CONSTEXPR TypeT* operator->() PHI_ATTRIBUTE_RETURNS_NONNULL
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const PHI_ATTRIBUTE_RETURNS_NONNULL
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
constexpr boolean operator==(const scope_ptr<LhsT>& lhs, const scope_ptr<RhsT>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
constexpr boolean operator==(const scope_ptr<LhsT>& lhs, nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <typename RhsT>
constexpr boolean operator==(nullptr_t, const scope_ptr<RhsT>& rhs) noexcept
{
    return rhs.get() == nullptr;
}

template <typename LhsT, typename RhsT>
constexpr boolean operator!=(const scope_ptr<LhsT>& lhs, const scope_ptr<RhsT>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
constexpr boolean operator!=(const scope_ptr<LhsT>& lhs, nullptr_t) noexcept
{
    return lhs.get() != nullptr;
}

template <typename RhsT>
constexpr boolean operator!=(nullptr_t, const scope_ptr<RhsT>& rhs) noexcept
{
    return rhs.get() != nullptr;
}

template <typename TypeT>
PHI_EXTENDED_CONSTEXPR void swap(scope_ptr<TypeT>& lhs, scope_ptr<TypeT>& rhs) noexcept
{
    lhs.swap(rhs);
}

/* not_null_scope_ptr */

template <typename TypeT>
class PHI_ATTRIBUTE_OWNER not_null_scope_ptr
{
public:
    using this_type       = not_null_scope_ptr<TypeT>;
    using value_type      = TypeT;
    using reference       = TypeT&;
    using const_reference = const TypeT&;
    using pointer         = TypeT*;
    using const_pointer   = const TypeT*;

    not_null_scope_ptr() = delete;

    not_null_scope_ptr(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR explicit not_null_scope_ptr(TypeT* ptr) noexcept PHI_ATTRIBUTE_NONNULL
        : m_Ptr(ptr)
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_scope_ptr");
    }

    not_null_scope_ptr(const not_null_scope_ptr<TypeT>&) = delete;

    PHI_EXTENDED_CONSTEXPR not_null_scope_ptr(not_null_scope_ptr<TypeT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to phi::not_null_scope_ptr");
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    PHI_EXTENDED_CONSTEXPR not_null_scope_ptr(not_null_scope_ptr<OtherT>&& other) noexcept
        : m_Ptr(other.leak_ptr())
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to assign nullptr to phi::not_null_scope_ptr");
    }

    PHI_CONSTEXPR_DESTRUCTOR ~not_null_scope_ptr() noexcept
    {
        clear();
    }

    not_null_scope_ptr<TypeT>& operator=(const not_null_scope_ptr<TypeT>&) = delete;

    PHI_EXTENDED_CONSTEXPR not_null_scope_ptr<TypeT>& operator=(
            not_null_scope_ptr<TypeT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_scope_ptr");

        reset(other.leak_ptr());

        return *this;
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR not_null_scope_ptr<TypeT>& operator=(
            not_null_scope_ptr<OtherT>&& other) noexcept
    {
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_scope_ptr");

        reset(other.leak_ptr());

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null_scope_ptr<TypeT>& operator=(TypeT* ptr) noexcept
            PHI_ATTRIBUTE_NONNULL
    {
        PHI_DBG_ASSERT(ptr != nullptr, "Trying to assign nullptr to phi::not_null_scope_ptr");

        if (m_Ptr != ptr)
        {
            delete m_Ptr;
        }
        m_Ptr = ptr;

        return *this;
    }

    not_null_scope_ptr<TypeT>& operator=(nullptr_t) = delete;

    PHI_ATTRIBUTE_RETURNS_NONNULL PHI_EXTENDED_CONSTEXPR TypeT* leak_ptr() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to leak nullptr from phi::not_null_scope_ptr");

        return exchange(m_Ptr, nullptr);
    }

    PHI_EXTENDED_CONSTEXPR not_null_observer_ptr<TypeT> observer() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Trying to create not_null_observer_ptr from nullptr");
        return not_null_observer_ptr<TypeT>{get()};
    }

    PHI_EXTENDED_CONSTEXPR void reset(TypeT* new_ptr) noexcept PHI_ATTRIBUTE_NONNULL
    {
        PHI_DBG_ASSERT(new_ptr != nullptr, "Trying to assign nullptr to phi::not_null_scope_ptr");

        delete m_Ptr;
        m_Ptr = new_ptr;
    }

    void reset(nullptr_t) = delete;

    PHI_EXTENDED_CONSTEXPR void swap(not_null_scope_ptr<TypeT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::not_null_scope_ptr");
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_scope_ptr");

        phi::swap(m_Ptr, other.m_Ptr);
    }

    template <typename OtherT, typename enable_if<is_convertible<OtherT*, TypeT*>::value>::type = 0>
    PHI_EXTENDED_CONSTEXPR void swap(not_null_scope_ptr<OtherT>& other) noexcept
    {
        PHI_DBG_ASSERT(get() != nullptr, "Trying to assign nullptr to phi::not_null_scope_ptr");
        PHI_DBG_ASSERT(other.get() != nullptr,
                       "Trying to assign nullptr to phi::not_null_scope_ptr");

        phi::swap(m_Ptr, other.m_Ptr);
    }

    operator bool() = delete;

    operator boolean() = delete;

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_EXTENDED_CONSTEXPR TypeT* get() noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Accessing phi::not_null_scope_ptr after it was deleted");

        return m_Ptr;
    }

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_EXTENDED_CONSTEXPR const TypeT* get()
            const noexcept
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Accessing phi::not_null_scope_ptr after it was deleted");

        return m_Ptr;
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_RETURNS_NONNULL explicit operator const TypeT*()
            const noexcept
    {
        return get();
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_RETURNS_NONNULL explicit operator TypeT*() noexcept
    {
        return get();
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_RETURNS_NONNULL TypeT* operator->()
    {
        PHI_DBG_ASSERT(m_Ptr != nullptr, "Cannot dereference a nullptr");
        return get();
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_RETURNS_NONNULL const TypeT* operator->() const
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

        // Clear pointer in debug mode
#if defined(PHI_DEBUG)
        m_Ptr = nullptr;
#endif
    }

    TypeT* m_Ptr;
};

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename LhsT, typename RhsT>
constexpr boolean operator==(const not_null_scope_ptr<LhsT>& lhs,
                             const not_null_scope_ptr<RhsT>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename LhsT>
boolean operator==(const not_null_scope_ptr<LhsT>& lhs, nullptr_t) = delete;

template <typename RhsT>
boolean operator==(nullptr_t, const not_null_scope_ptr<RhsT>& rhs) = delete;

template <typename LhsT, typename RhsT>
constexpr boolean operator!=(const not_null_scope_ptr<LhsT>& lhs,
                             const not_null_scope_ptr<RhsT>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

template <typename LhsT>
boolean operator!=(const not_null_scope_ptr<LhsT>& lhs, nullptr_t) = delete;

template <typename RhsT>
boolean operator!=(nullptr_t, const not_null_scope_ptr<RhsT>& rhs) = delete;

// make functions

template <typename TypeT, typename... ArgsT>
PHI_NODISCARD typename enable_if<!is_array<TypeT>::value, scope_ptr<TypeT>>::type make_scope(
        ArgsT&&... args)
{
    return scope_ptr<TypeT>(new TypeT(phi::forward<ArgsT>(args)...));
}

template <typename TypeT>
PHI_NODISCARD typename enable_if<is_unbounded_array<TypeT>::value, scope_ptr<TypeT>>::type
make_scope(phi::usize size)
{
    return scope_ptr<TypeT>(new typename remove_extent<TypeT>::type[size.unsafe()]());
}

template <typename TypeT, typename... ArgsT>
typename enable_if<is_bounded_array<TypeT>::value, scope_ptr<TypeT>>::type make_scope(
        ArgsT&&... args) = delete;

template <typename TypeT>
PHI_NODISCARD typename enable_if<!is_array<TypeT>::value, scope_ptr<TypeT>>::type
make_scope_for_overwrite()
{
    return scope_ptr<TypeT>(new TypeT);
}

template <typename TypeT>
PHI_NODISCARD typename enable_if<is_unbounded_array<TypeT>::value, scope_ptr<TypeT>>::type
make_scope_for_overwrite(phi::usize size)
{
    return scope_ptr<TypeT>(new typename remove_extent<TypeT>::type[size.unsafe()]);
}

template <typename TypeT, typename... ArgsT>
typename enable_if<is_bounded_array<TypeT>::value, scope_ptr<TypeT>>::type make_scope_for_overwrite(
        ArgsT&&... args) = delete;

template <typename TypeT, typename... ArgsT>
PHI_NODISCARD typename enable_if<!is_array<TypeT>::value, not_null_scope_ptr<TypeT>>::type
make_not_null_scope(ArgsT&&... args)
{
    return not_null_scope_ptr<TypeT>(new TypeT(phi::forward<ArgsT>(args)...));
}

template <typename TypeT>
PHI_NODISCARD typename enable_if<is_unbounded_array<TypeT>::value, not_null_scope_ptr<TypeT>>::type
make_not_null_scope(phi::usize size)
{
    return not_null_scope_ptr<TypeT>(new typename remove_extent<TypeT>::type[size.unsafe()]());
}

template <typename TypeT, typename... ArgsT>
typename enable_if<is_bounded_array<TypeT>::value, not_null_scope_ptr<TypeT>>::type
make_not_null_scope(ArgsT&&... args) = delete;

template <typename TypeT>
PHI_NODISCARD typename enable_if<!is_array<TypeT>::value, not_null_scope_ptr<TypeT>>::type
make_not_null_scope_for_overwrite()
{
    return not_null_scope_ptr<TypeT>(new TypeT);
}

template <typename TypeT>
PHI_NODISCARD typename enable_if<is_unbounded_array<TypeT>::value, not_null_scope_ptr<TypeT>>::type
make_not_null_scope_for_overwrite(phi::usize size)
{
    return not_null_scope_ptr<TypeT>(new typename remove_extent<TypeT>::type[size.unsafe()]);
}

template <typename TypeT, typename... ArgsT>
typename enable_if<is_bounded_array<TypeT>::value, not_null_scope_ptr<TypeT>>::type
make_not_null_scope_for_overwrite(ArgsT&&... args) = delete;

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT>
struct hash<phi::scope_ptr<TypeT>>
{
    phi::size_t operator()(phi::scope_ptr<TypeT> ptr) const noexcept
    {
        return std::hash<TypeT*>()(ptr.get());
    }
};

template <typename TypeT>
struct hash<phi::not_null_scope_ptr<TypeT>>
{
    phi::size_t operator()(phi::not_null_scope_ptr<TypeT> ptr) const noexcept
    {
        return std::hash<TypeT*>()(ptr.get());
    }
};

template <>
struct hash<phi::not_null_scope_ptr<phi::nullptr_t>>
{
    phi::size_t operator()(phi::not_null_scope_ptr<phi::nullptr_t> ptr) = delete;
};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_SCOPE_PTR_HPP
