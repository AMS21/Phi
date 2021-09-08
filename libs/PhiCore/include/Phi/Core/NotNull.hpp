#ifndef INCG_PHI_CORE_NOTNULL_HPP
#define INCG_PHI_CORE_NOTNULL_HPP

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/PhiConfig.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    constexpr char AssignNullptrError[]{"May not assign nullptr to phi::NotNull"};
    constexpr char ReturnNullptrError[]{"Returning nullptr from phi::NotNull"};
} // namespace detail

template <typename TypeT>
class NotNull
{
private:
    static_assert(std::is_convertible<decltype(std::declval<TypeT>() != nullptr), bool>::value,
                  "Phi::NotNull: Type cannot be compared to nullptr.");

public:
    template <typename = std::enable_if_t<!std::is_same<std::nullptr_t, TypeT>::value>>
    constexpr explicit NotNull(TypeT other) noexcept
        : m_Pointer(std::move(other))
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT,
              typename = std::enable_if_t<std::is_convertible<OtherT, TypeT>::value>>
    constexpr explicit NotNull(OtherT&& other) noexcept
        : m_Pointer(std::forward(other))
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT,
              typename = std::enable_if_t<std::is_convertible<OtherT, TypeT>::value>>
    constexpr NotNull(const NotNull<OtherT>& other) noexcept
        : NotNull(other.get())
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT,
              typename = std::enable_if_t<std::is_convertible<OtherT, TypeT>::value>>
    constexpr NotNull(NotNull<OtherT>&& other) noexcept
        : NotNull(std::move(other.get()))
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    constexpr NotNull(const NotNull& other) noexcept
        : m_Pointer(other.m_Pointer)
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    constexpr NotNull(NotNull&& other) noexcept
        : m_Pointer(std::move(other.m_Pointer))
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    constexpr NotNull& operator=(const NotNull& other) noexcept
    {
        m_Pointer = other.m_Pointer;

        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);

        return *this;
    }

    constexpr NotNull& operator=(NotNull&& other) noexcept
    {
        m_Pointer = std::move(other.m_Pointer);

        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);

        return *this;
    }

    PHI_NODISCARD constexpr typename std::conditional<std::is_copy_constructible<TypeT>::value,
                                                      TypeT, const TypeT&>::type
    get() const noexcept
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::ReturnNullptrError);
        return m_Pointer;
    }

    // Disallow compilation with nullptr constant
    NotNull(std::nullptr_t) = delete;
    NotNull& operator=(std::nullptr_t) = delete;

    // Explicitly remove pointer operations
    NotNull& operator++()                     = delete;
    NotNull& operator--()                     = delete;
    NotNull  operator++(int)                  = delete;
    NotNull  operator--(int)                  = delete;
    NotNull& operator+=(std::ptrdiff_t)       = delete;
    NotNull& operator-=(std::ptrdiff_t)       = delete;
    void     operator[](std::ptrdiff_t) const = delete;

private:
    TypeT m_Pointer;
};

template <typename TypeT>
auto make_not_null(TypeT&& val) noexcept
{
    return NotNull<std::remove_cv_t<std::remove_reference_t<TypeT>>>{std::forward<TypeT>(val)};
}

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename TypeT>
    struct hash<phi::NotNull<TypeT>>
    {
        std::size_t operator()(const phi::NotNull<TypeT>& value) const
        {
            return hash<TypeT>{}(value.get());
        }
    };
} // namespace std

#endif // INCG_PHI_CORE_NOTNULL_HPP
