// This file is heavily inspired by Jonathan Boccaras NamedType library https://github.com/joboccara/NamedType
// licensed under the MIT license https://github.com/joboccara/NamedType/blob/master/LICENSE
// Original files at
// https://github.com/joboccara/NamedType/blob/master/include/NamedType/named_type_impl.hpp
// https://github.com/joboccara/NamedType/blob/master/include/NamedType/underlying_functionalities.hpp
/* MIT License

Copyright (c) 2017 Jonathan Boccara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*!
 * \file NamedType.hpp
 * \brief Exports the strongly typed class NamedType.
 *
**/
#ifndef INCG_PHI_CORE_NAMED_TYPE_HPP
#define INCG_PHI_CORE_NAMED_TYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/standard_library.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/address_of.hpp"
#include "phi/core/crtp.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/move.hpp"
#include "phi/forward/std/hash.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_nothrow_copy_constructible.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"
#include "phi/type_traits/is_reference.hpp"
#include "phi/type_traits/remove_reference.hpp"
#include <functional>
#include <iosfwd>

// Enable empty base class optimization with multiple inheritance on Visual Studio or Clang on windows.
#if PHI_COMPILER_IS_ATLEAST(MSVC, 19, 14, 0) || PHI_COMPILER_IS(WINCLANG)
#    define PHI_EBCO __declspec(empty_bases)
#else
#    define PHI_EBCO /* Nothing */
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
class PHI_EBCO named_type : public SkillsT<named_type<TypeT, ParameterT, SkillsT...>>...
{
public:
    using this_type       = phi::named_type<TypeT, ParameterT, SkillsT...>;
    using underlying_type = TypeT;
    using reference       = named_type<TypeT&, ParameterT, SkillsT...>;
    using const_reference = named_type<const TypeT&, ParameterT, SkillsT...>;
    using pointer         = named_type<remove_reference_t<TypeT>*, ParameterT, SkillsT...>;
    using const_pointer   = named_type<const remove_reference_t<TypeT>*, ParameterT, SkillsT...>;

    named_type() = default;

    explicit PHI_CONSTEXPR named_type(const TypeT& value)
#if PHI_HAS_WORKING_IS_NOTHROW_COPY_CONSTRUCTIBLE()
            PHI_NOEXCEPT_EXPR(is_nothrow_copy_constructible<TypeT>::value)
#endif
        : m_Value(value)
    {}

    template <typename OtherT = TypeT, typename = enable_if_t<!is_reference<OtherT>::value, void>>
    explicit PHI_CONSTEXPR named_type(TypeT&& value)
#if PHI_HAS_WORKING_IS_NOTHROW_MOVE_CONSTRUCTIBLE()
            PHI_NOEXCEPT_EXPR(is_nothrow_move_constructible<TypeT>::value)
#endif
        : m_Value(phi::move(value))
    {}

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& unsafe() PHI_NOEXCEPT
    {
        return m_Value;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR_AND_CONST_OR(const)
            remove_reference_t<TypeT>& unsafe() const PHI_NOEXCEPT
    {
        return m_Value;
    }

    operator reference()
    {
        return reference(m_Value);
    }

    struct argument
    {
        // NOLINTNEXTLINE(misc-unconventional-assign-operator)
        named_type operator=(TypeT&& value) const // lgtm [cpp/assignment-does-not-return-this]
        {
            return named_type(phi::forward<TypeT>(value));
        }

        template <typename OtherT>
        // NOLINTNEXTLINE(misc-unconventional-assign-operator)
        named_type operator=(OtherT&& value) const // lgtm [cpp/assignment-does-not-return-this]
        {
            return named_type(forward<OtherT>(value));
        }

        argument()                           = default;
        ~argument()                          = default;
        argument(argument const&)            = delete;
        argument(argument&&)                 = delete;
        argument& operator=(argument const&) = delete;
        argument& operator=(argument&&)      = delete;
    };

private:
    TypeT m_Value;
};

template <template <typename TypeT> class StrongTypeT, typename TypeT>
PHI_NODISCARD PHI_CONSTEXPR StrongTypeT<TypeT> make_named(const TypeT& value)
{
    return StrongTypeT<TypeT>(value);
}

template <typename TypeT>
struct PHI_EBCO pre_incrementable : public crtp<TypeT, pre_incrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT& operator++()
    {
        ++this->underlying().unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO post_incrementable : public crtp<TypeT, post_incrementable>
{
    // NOLINTNEXTLINE(cert-dcl21-cpp)
    PHI_EXTENDED_CONSTEXPR TypeT operator++(int)
    {
        return TypeT(this->underlying().unsafe()++);
    }
};

template <typename TypeT>
struct PHI_EBCO pre_decrementable : public crtp<TypeT, pre_decrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT& operator--()
    {
        --this->underlying().unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO post_decrementable : public crtp<TypeT, post_decrementable>
{
    // NOLINTNEXTLINE(cert-dcl21-cpp)
    PHI_EXTENDED_CONSTEXPR TypeT operator--(int)
    {
        return TypeT(this->underlying().unsafe()--);
    }
};

template <typename TypeT>
struct PHI_EBCO binary_addable : public crtp<TypeT, binary_addable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator+(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() + other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator+=(const TypeT& other)
    {
        this->underlying().unsafe() += other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO unary_addable : public crtp<TypeT, unary_addable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator+() const
    {
        return TypeT(+this->underlying().unsafe());
    }
};

template <typename TypeT>
struct PHI_EBCO addable : public binary_addable<TypeT>, unary_addable<TypeT>
{
    using binary_addable<TypeT>::operator+;
    using unary_addable<TypeT>::operator+;
};

template <typename TypeT>
struct PHI_EBCO binary_subtractable : public crtp<TypeT, binary_subtractable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator-(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() - other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator-=(const TypeT& other)
    {
        this->underlying().unsafe() -= other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO unary_subtractable : public crtp<TypeT, unary_subtractable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator-() const
    {
        return TypeT(-this->underlying().unsafe());
    }
};

template <typename TypeT>
struct PHI_EBCO subtractable : public binary_subtractable<TypeT>, unary_subtractable<TypeT>
{
    using unary_subtractable<TypeT>::operator-;
    using binary_subtractable<TypeT>::operator-;
};

template <typename TypeT>
struct PHI_EBCO multiplicable : public crtp<TypeT, multiplicable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator*(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() * other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator*=(const TypeT& other)
    {
        this->underlying().unsafe() *= other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO divisible : public crtp<TypeT, divisible>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator/(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() / other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator/=(const TypeT& other)
    {
        this->underlying().unsafe() /= other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO modulable : public crtp<TypeT, modulable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator%(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() % other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator%=(const TypeT& other)
    {
        this->underlying().unsafe() %= other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_invertible : public crtp<TypeT, bit_wise_invertible>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator~() const
    {
        return TypeT(~this->underlying().unsafe());
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_andable : public crtp<TypeT, bit_wise_andable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator&(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() & other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator&=(const TypeT& other)
    {
        this->underlying().unsafe() &= other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_orable : public crtp<TypeT, bit_wise_orable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator|(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() | other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator|=(const TypeT& other)
    {
        this->underlying().unsafe() |= other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_xorable : public crtp<TypeT, bit_wise_xorable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator^(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() ^ other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator^=(const TypeT& other)
    {
        this->underlying().unsafe() ^= other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_left_shiftable : public crtp<TypeT, bit_wise_left_shiftable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator<<(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() << other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator<<=(const TypeT& other)
    {
        this->underlying().unsafe() <<= other.unsafe();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_right_shiftable : public crtp<TypeT, bit_wise_right_shiftable>
{
    PHI_NODISCARD PHI_CONSTEXPR TypeT operator>>(const TypeT& other) const
    {
        return TypeT(this->underlying().unsafe() >> other.unsafe());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator>>=(const TypeT& other)
    {
        this->underlying().unsafe() >>= other.unsafe();
        return this->underlying();
    }
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wzero-as-null-pointer-constant")

template <typename TypeT>
struct PHI_EBCO comparable : public crtp<TypeT, comparable>
{
    PHI_NODISCARD PHI_CONSTEXPR bool operator<(const comparable<TypeT>& other) const
    {
        return this->underlying().unsafe() < other.underlying().unsafe();
    }

    PHI_NODISCARD PHI_CONSTEXPR bool operator>(const comparable<TypeT>& other) const
    {
        return other.underlying().unsafe() < this->underlying().unsafe();
    }

    PHI_NODISCARD PHI_CONSTEXPR bool operator<=(const comparable<TypeT>& other) const
    {
        return !(other < *this);
    }

    PHI_NODISCARD PHI_CONSTEXPR bool operator>=(const comparable<TypeT>& other) const
    {
        return !(*this < other);
    }

    PHI_NODISCARD PHI_CONSTEXPR bool operator==(const comparable<TypeT>& other) const
    {
        return !(*this < other) && !(other < *this);
    }

    PHI_NODISCARD PHI_CONSTEXPR bool operator!=(const comparable<TypeT>& other) const
    {
        return !(*this == other);
    }
};

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename TypeT>
struct PHI_EBCO dereferenceable;

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct PHI_EBCO dereferenceable<named_type<TypeT, ParameterT, SkillsT...>>
    : public crtp<named_type<TypeT, ParameterT, SkillsT...>, dereferenceable>
{
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& operator*() &
    {
        return this->underlying().unsafe();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const remove_reference_t<TypeT>& operator*() const&
    {
        return this->underlying().unsafe();
    }
};

template <typename DestinationT>
struct PHI_EBCO implicitly_convertible_to
{
    template <typename TypeT>
    struct templ : public crtp<TypeT, templ>
    {
        PHI_NODISCARD PHI_CONSTEXPR operator DestinationT() const
        {
            return this->underlying().unsafe();
        }
    };
};

template <typename TypeT>
struct PHI_EBCO printable : public crtp<TypeT, printable>
{
    static PHI_CONSTEXPR_AND_CONST bool is_printable = true;

    template <typename CharT, typename CharTraitsT>
    void print(std::basic_ostream<CharT, CharTraitsT>& stream) const
    {
        stream << this->underlying().unsafe();
    }
};

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT, typename CharT,
          typename CharTraitsT>
typename enable_if<named_type<TypeT, ParameterT, SkillsT...>::is_printable,
                   std::basic_ostream<CharT, CharTraitsT>&>::type
operator<<(std::basic_ostream<CharT, CharTraitsT>&          stream,
           named_type<TypeT, ParameterT, SkillsT...> const& object)
{
    object.print(stream);
    return stream;
}

template <typename TypeT>
struct PHI_EBCO hashable
{
    static PHI_CONSTEXPR_AND_CONST bool is_hashable = true;
};

template <typename NamedTypeT>
struct PHI_EBCO function_callable;

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct PHI_EBCO function_callable<named_type<TypeT, ParameterT, SkillsT...>>
    : public crtp<named_type<TypeT, ParameterT, SkillsT...>, function_callable>
{
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR operator TypeT&()
    {
        return this->underlying().unsafe();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR operator const TypeT&() const
    {
        return this->underlying().unsafe();
    }
};

template <typename NamedTypeT>
struct PHI_EBCO method_callable;

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct PHI_EBCO method_callable<named_type<TypeT, ParameterT, SkillsT...>>
    : public crtp<named_type<TypeT, ParameterT, SkillsT...>, method_callable>
{
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR remove_reference_t<TypeT>* operator->()
    {
        return address_of(this->underlying().unsafe());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const remove_reference_t<TypeT>* operator->() const
    {
        return address_of(this->underlying().unsafe());
    }
};

template <typename NamedTypeT>
struct PHI_EBCO callable : public function_callable<NamedTypeT>, method_callable<NamedTypeT>
{};

template <typename TypeT>
struct PHI_EBCO arithmetic : public pre_incrementable<TypeT>,
                             post_incrementable<TypeT>,
                             pre_decrementable<TypeT>,
                             post_decrementable<TypeT>,
                             addable<TypeT>,
                             subtractable<TypeT>,
                             multiplicable<TypeT>,
                             divisible<TypeT>,
                             modulable<TypeT>,
                             bit_wise_invertible<TypeT>,
                             bit_wise_andable<TypeT>,
                             bit_wise_orable<TypeT>,
                             bit_wise_xorable<TypeT>,
                             bit_wise_left_shiftable<TypeT>,
                             bit_wise_right_shiftable<TypeT>,
                             comparable<TypeT>,
                             printable<TypeT>,
                             hashable<TypeT>
{
    using post_incrementable<TypeT>::operator++;
    using pre_incrementable<TypeT>::operator++;
    using post_decrementable<TypeT>::operator--;
    using pre_decrementable<TypeT>::operator--;
};

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct hash<phi::named_type<TypeT, ParameterT, SkillsT...>>
{
    using named_type      = phi::named_type<TypeT, ParameterT, SkillsT...>;
    using checkIfHashable = typename enable_if<named_type::is_hashable, void>::type;

    size_t operator()(const named_type& value) const PHI_NOEXCEPT
    {
        static_assert(PHI_NOEXCEPT_EXPR(std::hash<TypeT>()(value.unsafe())),
                      "hash fuction should not throw");

        return std::hash<TypeT>()(value.unsafe());
    }
};

DETAIL_PHI_END_STD_NAMESPACE()

#undef PHI_EBCO

#endif // INCG_PHI_CORE_NAMED_TYPE_HPP
