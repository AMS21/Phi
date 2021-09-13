#ifndef INCG_PHI_CORE_NOTNULL_HPP
#define INCG_PHI_CORE_NOTNULL_HPP

#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Core/Assert.hpp"
#include "Phi/Core/Boolean.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/Core/Move.hpp"
#include "Phi/Core/Nullptr.hpp"
#include "Phi/PhiConfig.hpp"
#include "Phi/TypeTraits/conditional.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/is_convertible.hpp"
#include "Phi/TypeTraits/is_copy_constructible.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"
#include "Phi/TypeTraits/remove_reference.hpp"
#include <cstddef>
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
    static_assert(is_convertible<decltype(declval<TypeT>() != nullptr), bool>::value,
                  "Phi::NotNull: Type cannot be compared to nullptr.");

public:
    template <typename = enable_if_t<!is_same<nullptr_t, TypeT>::value>>
    constexpr explicit NotNull(TypeT other) noexcept
        : m_Pointer(move(other))
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT, typename = enable_if_t<is_convertible<OtherT, TypeT>::value>>
    constexpr explicit NotNull(OtherT&& other) noexcept
        : m_Pointer(forward(other))
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT, typename = enable_if_t<is_convertible<OtherT, TypeT>::value>>
    constexpr NotNull(const NotNull<OtherT>& other) noexcept
        : NotNull(other.get())
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    template <typename OtherT, typename = enable_if_t<is_convertible<OtherT, TypeT>::value>>
    constexpr NotNull(NotNull<OtherT>&& other) noexcept
        : NotNull(move(other.get()))
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    constexpr NotNull(const NotNull& other) noexcept
        : m_Pointer(other.m_Pointer)
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);
    }

    constexpr NotNull(NotNull&& other) noexcept
        : m_Pointer(move(other.m_Pointer))
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
        m_Pointer = move(other.m_Pointer);

        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::AssignNullptrError);

        return *this;
    }

    PHI_NODISCARD constexpr
            typename conditional<is_copy_constructible<TypeT>::value, TypeT, const TypeT&>::type
            get() const noexcept
    {
        PHI_DBG_ASSERT(m_Pointer != nullptr, detail::ReturnNullptrError);
        return m_Pointer;
    }

    // Disallow compilation with nullptr constant
    NotNull(nullptr_t) = delete;
    NotNull& operator=(nullptr_t) = delete;

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
    return NotNull<remove_cv_t<remove_reference_t<TypeT>>>{forward<TypeT>(val)};
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
