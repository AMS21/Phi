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
#ifndef INCG_PHI_CORE_NAMEDTYPE_HPP
#define INCG_PHI_CORE_NAMEDTYPE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/address_of.hpp"
#include "phi/core/crtp.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/move.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_nothrow_copy_constructible.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"
#include "phi/type_traits/is_reference.hpp"
#include "phi/type_traits/remove_reference.hpp"
#include <functional>
#include <iosfwd>
#include <utility>

// Enable empty base class optimization with multiple inheritance on Visual Studio.
#if PHI_HAS_EXTENSION_DECLSPEC_EMPTY_BASES()
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

    explicit constexpr named_type(const TypeT& value) noexcept(
            is_nothrow_copy_constructible<TypeT>::value)
        : m_Value(value)
    {}

    template <typename OtherT = TypeT, typename = enable_if_t<!is_reference<OtherT>::value, void>>
    explicit constexpr named_type(TypeT&& value) noexcept(
            is_nothrow_move_constructible<TypeT>::value)
        : m_Value(phi::move(value))
    {}

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& get() noexcept
    {
        return m_Value;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR_AND_CONST_OR(const)
            remove_reference_t<TypeT>& get() const noexcept
    {
        return m_Value;
    }

    operator reference()
    {
        return reference(m_Value);
    }

    struct argument
    {
        PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Weffc++")

        named_type operator=(TypeT&& value) const // lgtm [cpp/assignment-does-not-return-this]
        {
            return named_type(phi::forward<TypeT>(value));
        }

        template <typename OtherT>
        named_type operator=(OtherT&& value) const // lgtm [cpp/assignment-does-not-return-this]
        {
            return named_type(phi::forward<OtherT>(value));
        }

        PHI_GCC_SUPPRESS_WARNING_POP()

        argument()                = default;
        argument(argument const&) = delete;
        argument(argument&&)      = delete;
        argument& operator=(argument const&) = delete;
        argument& operator=(argument&&) = delete;
    };

private:
    TypeT m_Value;
};

template <template <typename TypeT> class StrongTypeT, typename TypeT>
PHI_NODISCARD constexpr StrongTypeT<TypeT> make_named(const TypeT& value)
{
    return StrongTypeT<TypeT>(value);
}

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Weffc++")

template <typename TypeT>
struct PHI_EBCO pre_incrementable : public crtp<TypeT, pre_incrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT& operator++()
    {
        ++this->underlying().get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO post_incrementable : public crtp<TypeT, post_incrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT operator++(int)
    {
        return TypeT(this->underlying().get()++);
    }
};

template <typename TypeT>
struct PHI_EBCO pre_decrementable : public crtp<TypeT, pre_decrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT& operator--()
    {
        --this->underlying().get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO post_decrementable : public crtp<TypeT, post_decrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT operator--(int)
    {
        return TypeT(this->underlying().get()--);
    }
};

PHI_GCC_SUPPRESS_WARNING_POP()

template <typename TypeT>
struct PHI_EBCO binary_addable : public crtp<TypeT, binary_addable>
{
    PHI_NODISCARD constexpr TypeT operator+(const TypeT& other) const
    {
        return TypeT(this->underlying().get() + other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator+=(const TypeT& other)
    {
        this->underlying().get() += other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO unary_addable : public crtp<TypeT, unary_addable>
{
    PHI_NODISCARD constexpr TypeT operator+() const
    {
        return TypeT(+this->underlying().get());
    }
};

template <typename TypeT>
struct PHI_EBCO addable : public binary_addable<TypeT>, unary_addable<TypeT>
{
    using binary_addable<TypeT>::operator+;
    using unary_addable<TypeT>:: operator+;
};

template <typename TypeT>
struct PHI_EBCO binary_subtractable : public crtp<TypeT, binary_subtractable>
{
    PHI_NODISCARD constexpr TypeT operator-(const TypeT& other) const
    {
        return TypeT(this->underlying().get() - other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator-=(const TypeT& other)
    {
        this->underlying().get() -= other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO unary_subtractable : public crtp<TypeT, unary_subtractable>
{
    PHI_NODISCARD constexpr TypeT operator-() const
    {
        return TypeT(-this->underlying().get());
    }
};

template <typename TypeT>
struct PHI_EBCO subtractable : public binary_subtractable<TypeT>, unary_subtractable<TypeT>
{
    using unary_subtractable<TypeT>:: operator-;
    using binary_subtractable<TypeT>::operator-;
};

template <typename TypeT>
struct PHI_EBCO multiplicable : public crtp<TypeT, multiplicable>
{
    PHI_NODISCARD constexpr TypeT operator*(const TypeT& other) const
    {
        return TypeT(this->underlying().get() * other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator*=(const TypeT& other)
    {
        this->underlying().get() *= other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO divisible : public crtp<TypeT, divisible>
{
    PHI_NODISCARD constexpr TypeT operator/(const TypeT& other) const
    {
        return TypeT(this->underlying().get() / other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator/=(const TypeT& other)
    {
        this->underlying().get() /= other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO modulable : public crtp<TypeT, modulable>
{
    PHI_NODISCARD constexpr TypeT operator%(const TypeT& other) const
    {
        return TypeT(this->underlying().get() % other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator%=(const TypeT& other)
    {
        this->underlying().get() %= other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_invertable : public crtp<TypeT, bit_wise_invertable>
{
    PHI_NODISCARD constexpr TypeT operator~() const
    {
        return TypeT(~this->underlying().get());
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_andable : public crtp<TypeT, bit_wise_andable>
{
    PHI_NODISCARD constexpr TypeT operator&(const TypeT& other) const
    {
        return TypeT(this->underlying().get() & other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator&=(const TypeT& other)
    {
        this->underlying().get() &= other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_orable : public crtp<TypeT, bit_wise_orable>
{
    PHI_NODISCARD constexpr TypeT operator|(const TypeT& other) const
    {
        return TypeT(this->underlying().get() | other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator|=(const TypeT& other)
    {
        this->underlying().get() |= other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_xorable : public crtp<TypeT, bit_wise_xorable>
{
    PHI_NODISCARD constexpr TypeT operator^(const TypeT& other) const
    {
        return TypeT(this->underlying().get() ^ other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator^=(const TypeT& other)
    {
        this->underlying().get() ^= other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_left_shiftable : public crtp<TypeT, bit_wise_left_shiftable>
{
    PHI_NODISCARD constexpr TypeT operator<<(const TypeT& other) const
    {
        return TypeT(this->underlying().get() << other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator<<=(const TypeT& other)
    {
        this->underlying().get() <<= other.get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO bit_wise_right_shiftable : public crtp<TypeT, bit_wise_right_shiftable>
{
    PHI_NODISCARD constexpr TypeT operator>>(const TypeT& other) const
    {
        return TypeT(this->underlying().get() >> other.get());
    }

    PHI_EXTENDED_CONSTEXPR TypeT& operator>>=(const TypeT& other)
    {
        this->underlying().get() >>= other.get();
        return this->underlying();
    }
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wzero-as-null-pointer-constant")

template <typename TypeT>
struct PHI_EBCO comparable : public crtp<TypeT, comparable>
{
    PHI_NODISCARD constexpr bool operator<(const comparable<TypeT>& other) const
    {
        return this->underlying().get() < other.underlying().get();
    }

    PHI_NODISCARD constexpr bool operator>(const comparable<TypeT>& other) const
    {
        return other.underlying().get() < this->underlying().get();
    }

    PHI_NODISCARD constexpr bool operator<=(const comparable<TypeT>& other) const
    {
        return !(other < *this);
    }

    PHI_NODISCARD constexpr bool operator>=(const comparable<TypeT>& other) const
    {
        return !(*this < other);
    }

    PHI_NODISCARD constexpr bool operator==(const comparable<TypeT>& other) const
    {
        return !(*this < other) && !(other < *this);
    }

    PHI_NODISCARD constexpr bool operator!=(const comparable<TypeT>& other) const
    {
        return !(*this == other);
    }
};

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename TypeT>
struct PHI_EBCO dereferencable;

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct PHI_EBCO dereferencable<named_type<TypeT, ParameterT, SkillsT...>>
    : public crtp<named_type<TypeT, ParameterT, SkillsT...>, dereferencable>
{
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& operator*() &
    {
        return this->underlying().get();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const remove_reference_t<TypeT>& operator*() const&
    {
        return this->underlying().get();
    }
};

template <typename DestinationT>
struct PHI_EBCO implicitly_convertible_to
{
    template <typename TypeT>
    struct templ : public crtp<TypeT, templ>
    {
        PHI_NODISCARD constexpr operator DestinationT() const
        {
            return this->underlying().get();
        }
    };
};

template <typename TypeT>
struct PHI_EBCO printable : public crtp<TypeT, printable>
{
    static constexpr bool is_printable = true;

    template <typename CharT, typename CharTraitsT>
    void print(std::basic_ostream<CharT, CharTraitsT>& stream) const
    {
        stream << this->underlying().get();
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
    static constexpr bool is_hashable = true;
};

template <typename NamedTypeT>
struct PHI_EBCO function_callable;

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct PHI_EBCO function_callable<named_type<TypeT, ParameterT, SkillsT...>>
    : public crtp<named_type<TypeT, ParameterT, SkillsT...>, function_callable>
{
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR operator TypeT&()
    {
        return this->underlying().get();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR operator const TypeT&() const
    {
        return this->underlying().get();
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
        return address_of(this->underlying().get());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const remove_reference_t<TypeT>* operator->() const
    {
        return address_of(this->underlying().get());
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
                             bit_wise_invertable<TypeT>,
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
    using pre_incrementable<TypeT>:: operator++;
    using post_decrementable<TypeT>::operator--;
    using pre_decrementable<TypeT>:: operator--;
};

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct hash<phi::named_type<TypeT, ParameterT, SkillsT...>>
{
    using named_type      = phi::named_type<TypeT, ParameterT, SkillsT...>;
    using checkIfHashable = typename enable_if<named_type::is_hashable, void>::type;

    size_t operator()(const named_type& value) const noexcept
    {
        static_assert(noexcept(std::hash<TypeT>()(value.get())), "hash fuction should not throw");

        return std::hash<TypeT>()(value.get());
    }
};

DETAIL_PHI_END_STD_NAMESPACE()

#undef PHI_EBCO

#endif // INCG_PHI_CORE_NAMEDTYPE_HPP
