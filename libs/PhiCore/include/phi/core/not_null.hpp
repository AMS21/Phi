#ifndef INCG_PHI_CORE_NOTNULL_HPP
#define INCG_PHI_CORE_NOTNULL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/declval.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/move.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/ptrdiff_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_copy_constructible.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/remove_cv.hpp"
#include "phi/type_traits/remove_reference.hpp"
#include <cstddef>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wunused-const-variable=")

namespace detail
{
    constexpr char AssignNullptrError[]{"May not assign nullptr to phi::not_null"};
    constexpr char ReturnNullptrError[]{"Returning nullptr from phi::not_null"};
} // namespace detail

PHI_GCC_SUPPRESS_WARNING_POP()

template <typename TypeT>
class PHI_ATTRIBUTE_POINTER not_null
{
private:
    static_assert(is_convertible<decltype(declval<TypeT>() != nullptr), bool>::value,
                  "phi::not_null: Type cannot be compared to nullptr.");

public:
    ~not_null() = default;

    template <typename = enable_if_t<!is_same<nullptr_t, TypeT>::value>>
    PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR explicit not_null(TypeT other) noexcept
        : m_Pointer{move(other)}
    {
        PHI_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT, typename = enable_if_t<is_convertible<OtherT, TypeT>::value>>
    // NOLINTNEXTLINE(bugprone-forwarding-reference-overload)
    PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR explicit not_null(OtherT&& other) noexcept
        : m_Pointer(forward(other))
    {
        PHI_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT, typename = enable_if_t<is_convertible<OtherT, TypeT>::value>>
    PHI_EXTENDED_CONSTEXPR not_null(const not_null<OtherT>& other) noexcept
        : not_null(other.get())
    {
        PHI_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT, typename = enable_if_t<is_convertible<OtherT, TypeT>::value>>
    PHI_EXTENDED_CONSTEXPR not_null(not_null<OtherT>&& other) noexcept
        : not_null(move(other.get()))
    {
        PHI_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    PHI_EXTENDED_CONSTEXPR not_null(const not_null& other) noexcept
        : m_Pointer(other.m_Pointer)
    {
        PHI_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    PHI_EXTENDED_CONSTEXPR not_null(not_null&& other) noexcept
        : m_Pointer(move(other.m_Pointer))
    {
        PHI_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
    PHI_EXTENDED_CONSTEXPR not_null& operator=(const not_null& other) noexcept
    {
        m_Pointer = other.m_Pointer;

        PHI_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null& operator=(not_null&& other) noexcept
    {
        m_Pointer = move(other.m_Pointer);

        PHI_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);

        return *this;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR
            typename conditional<is_copy_constructible<TypeT>::value, TypeT, const TypeT&>::type
            get() const noexcept
    {
        PHI_ASSERT(m_Pointer != nullptr, detail::ReturnNullptrError);

        return m_Pointer;
    }

    // Disallow compilation with nullptr constant
    not_null(nullptr_t)            = delete;
    not_null& operator=(nullptr_t) = delete;

    // Explicitly remove pointer operations
    not_null& operator++()                = delete;
    not_null& operator--()                = delete;
    not_null  operator++(int)             = delete; // NOLINT(cert-dcl21-cpp)
    not_null  operator--(int)             = delete; // NOLINT(cert-dcl21-cpp)
    not_null& operator+=(ptrdiff_t)       = delete;
    not_null& operator-=(ptrdiff_t)       = delete;
    void      operator[](ptrdiff_t) const = delete;

private:
    TypeT m_Pointer;
};

template <typename TypeT>
not_null<remove_cv_t<remove_reference_t<TypeT>>> make_not_null(TypeT&& val) noexcept
{
    return not_null<remove_cv_t<remove_reference_t<TypeT>>>{forward<TypeT>(val)};
}

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT>
struct hash<phi::not_null<TypeT>>
{
    size_t operator()(const phi::not_null<TypeT>& value) const
    {
        return hash<TypeT>{}(value.get());
    }
};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_NOTNULL_HPP
