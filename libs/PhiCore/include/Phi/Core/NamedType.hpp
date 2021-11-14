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

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/Core/AddressOf.hpp"
#include "Phi/Core/CRTP.hpp"
#include "Phi/Core/Forward.hpp"
#include "Phi/Core/Move.hpp"
#include "Phi/Core/SizeT.hpp"
#include "Phi/TypeTraits/enable_if.hpp"
#include "Phi/TypeTraits/is_nothrow_copy_constructible.hpp"
#include "Phi/TypeTraits/is_nothrow_move_constructible.hpp"
#include "Phi/TypeTraits/is_reference.hpp"
#include "Phi/TypeTraits/remove_reference.hpp"
#include <memory>
#include <utility>

// Enable empty base class optimization with multiple inheritance on Visual Studio.
#if PHI_HAS_EXTENSION_DECLSPEC_EMPTY_BASES()
#    define PHI_EBCO __declspec(empty_bases)
#else
#    define PHI_EBCO /* Nothing */
#endif

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
class PHI_EBCO NamedType : public SkillsT<NamedType<TypeT, ParameterT, SkillsT...>>...
{
public:
    using this_type       = phi::NamedType<TypeT, ParameterT, SkillsT...>;
    using underlying_type = TypeT;
    using reference       = NamedType<TypeT&, ParameterT, SkillsT...>;
    using const_reference = NamedType<const TypeT&, ParameterT, SkillsT...>;
    using pointer         = NamedType<remove_reference_t<TypeT>*, ParameterT, SkillsT...>;
    using const_pointer   = NamedType<const remove_reference_t<TypeT>*, ParameterT, SkillsT...>;

    NamedType() = default;

    explicit constexpr NamedType(const TypeT& value) noexcept(
            is_nothrow_copy_constructible<TypeT>::value)
        : m_Value(value)
    {}

    template <typename OtherT = TypeT, typename = enable_if_t<!is_reference<OtherT>::value, void>>
    explicit constexpr NamedType(TypeT&& value) noexcept(
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

    struct Argument
    {
        PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Weffc++")

        NamedType operator=(TypeT&& value) const // lgtm [cpp/assignment-does-not-return-this]
        {
            return NamedType(phi::forward<TypeT>(value));
        }

        template <typename OtherT>
        NamedType operator=(OtherT&& value) const // lgtm [cpp/assignment-does-not-return-this]
        {
            return NamedType(phi::forward<OtherT>(value));
        }

        PHI_GCC_SUPPRESS_WARNING_POP()

        Argument()                = default;
        Argument(Argument const&) = delete;
        Argument(Argument&&)      = delete;
        Argument& operator=(Argument const&) = delete;
        Argument& operator=(Argument&&) = delete;
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
struct PHI_EBCO PreIncrementable : CRTP<TypeT, PreIncrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT& operator++()
    {
        ++this->underlying().get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO PostIncrementable : CRTP<TypeT, PostIncrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT operator++(int)
    {
        return TypeT(this->underlying().get()++);
    }
};

template <typename TypeT>
struct PHI_EBCO PreDecrementable : CRTP<TypeT, PreDecrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT& operator--()
    {
        --this->underlying().get();
        return this->underlying();
    }
};

template <typename TypeT>
struct PHI_EBCO PostDecrementable : CRTP<TypeT, PostDecrementable>
{
    PHI_EXTENDED_CONSTEXPR TypeT operator--(int)
    {
        return TypeT(this->underlying().get()--);
    }
};

PHI_GCC_SUPPRESS_WARNING_POP()

template <typename TypeT>
struct PHI_EBCO BinaryAddable : CRTP<TypeT, BinaryAddable>
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
struct PHI_EBCO UnaryAddable : CRTP<TypeT, UnaryAddable>
{
    PHI_NODISCARD constexpr TypeT operator+() const
    {
        return TypeT(+this->underlying().get());
    }
};

template <typename TypeT>
struct PHI_EBCO Addable : BinaryAddable<TypeT>, UnaryAddable<TypeT>
{
    using BinaryAddable<TypeT>::operator+;

    using UnaryAddable<TypeT>::operator+;
};

template <typename TypeT>
struct PHI_EBCO BinarySubtractable : CRTP<TypeT, BinarySubtractable>
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
struct PHI_EBCO UnarySubtractable : CRTP<TypeT, UnarySubtractable>
{
    PHI_NODISCARD constexpr TypeT operator-() const
    {
        return TypeT(-this->underlying().get());
    }
};

template <typename TypeT>
struct PHI_EBCO Subtractable : BinarySubtractable<TypeT>, UnarySubtractable<TypeT>
{
    using UnarySubtractable<TypeT>::operator-;

    using BinarySubtractable<TypeT>::operator-;
};

template <typename TypeT>
struct PHI_EBCO Multiplicable : CRTP<TypeT, Multiplicable>
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
struct PHI_EBCO Divisible : CRTP<TypeT, Divisible>
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
struct PHI_EBCO Modulable : CRTP<TypeT, Modulable>
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
struct PHI_EBCO BitWiseInvertable : CRTP<TypeT, BitWiseInvertable>
{
    PHI_NODISCARD constexpr TypeT operator~() const
    {
        return TypeT(~this->underlying().get());
    }
};

template <typename TypeT>
struct PHI_EBCO BitWiseAndable : CRTP<TypeT, BitWiseAndable>
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
struct PHI_EBCO BitWiseOrable : CRTP<TypeT, BitWiseOrable>
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
struct PHI_EBCO BitWiseXorable : CRTP<TypeT, BitWiseXorable>
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
struct PHI_EBCO BitWiseLeftShiftable : CRTP<TypeT, BitWiseLeftShiftable>
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
struct PHI_EBCO BitWiseRightShiftable : CRTP<TypeT, BitWiseRightShiftable>
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

template <typename TypeT>
struct PHI_EBCO Comparable : CRTP<TypeT, Comparable>
{
    PHI_NODISCARD constexpr bool operator<(const TypeT& other) const
    {
        return this->underlying().get() < other.get();
    }

    PHI_NODISCARD constexpr bool operator>(const TypeT& other) const
    {
        return other.get() < this->underlying().get();
    }

    PHI_NODISCARD constexpr bool operator<=(const TypeT& other) const
    {
        return !(other.get() < this->underlying().get());
    }

    PHI_NODISCARD constexpr bool operator>=(const TypeT& other) const
    {
        return !(*this < other);
    }

#if PHI_COMPILER_IS(MSVC)
    PHI_NODISCARD constexpr bool operator==(const TypeT& other) const
    {
        return !(*this < other) && !(other.get() < this->underlying().get());
    }
#else
    PHI_NODISCARD friend constexpr bool operator==(const Comparable<TypeT>& self,
                                                   const TypeT&             other)
    {
        return !(self < other) && !(other.get() < self.underlying().get());
    }
#endif

    PHI_NODISCARD constexpr bool operator!=(const TypeT& other) const
    {
        return !(*this == other);
    }
};

template <typename TypeT>
struct PHI_EBCO Dereferencable;

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct PHI_EBCO Dereferencable<NamedType<TypeT, ParameterT, SkillsT...>>
    : CRTP<NamedType<TypeT, ParameterT, SkillsT...>, Dereferencable>
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
struct PHI_EBCO ImplicitlyConvertibleTo
{
    template <typename TypeT>
    struct templ : public CRTP<TypeT, templ>
    {
        PHI_NODISCARD constexpr operator DestinationT() const
        {
            return this->underlying().get();
        }
    };
};

template <typename TypeT>
struct PHI_EBCO Printable : CRTP<TypeT, Printable>
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
typename enable_if<NamedType<TypeT, ParameterT, SkillsT...>::is_printable,
                   std::basic_ostream<CharT, CharTraitsT>&>::type
operator<<(std::basic_ostream<CharT, CharTraitsT>&         stream,
           NamedType<TypeT, ParameterT, SkillsT...> const& object)
{
    object.print(stream);
    return stream;
}

template <typename TypeT>
struct PHI_EBCO Hashable
{
    static constexpr bool is_hashable = true;
};

template <typename NamedTypeT>
struct PHI_EBCO FunctionCallable;

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct PHI_EBCO FunctionCallable<NamedType<TypeT, ParameterT, SkillsT...>>
    : CRTP<NamedType<TypeT, ParameterT, SkillsT...>, FunctionCallable>
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
struct PHI_EBCO MethodCallable;

template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
struct PHI_EBCO MethodCallable<NamedType<TypeT, ParameterT, SkillsT...>>
    : CRTP<NamedType<TypeT, ParameterT, SkillsT...>, MethodCallable>
{
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR remove_reference_t<TypeT>* operator->()
    {
        return addressof(this->underlying().get());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const remove_reference_t<TypeT>* operator->() const
    {
        return addressof(this->underlying().get());
    }
};

template <typename NamedTypeT>
struct PHI_EBCO Callable : FunctionCallable<NamedTypeT>, MethodCallable<NamedTypeT>
{};

template <typename TypeT>
struct PHI_EBCO Arithmetic : PreIncrementable<TypeT>,
                             PostIncrementable<TypeT>,
                             PreDecrementable<TypeT>,
                             PostDecrementable<TypeT>,
                             Addable<TypeT>,
                             Subtractable<TypeT>,
                             Multiplicable<TypeT>,
                             Divisible<TypeT>,
                             Modulable<TypeT>,
                             BitWiseInvertable<TypeT>,
                             BitWiseAndable<TypeT>,
                             BitWiseOrable<TypeT>,
                             BitWiseXorable<TypeT>,
                             BitWiseLeftShiftable<TypeT>,
                             BitWiseRightShiftable<TypeT>,
                             Comparable<TypeT>,
                             Printable<TypeT>,
                             Hashable<TypeT>
{};

DETAIL_PHI_END_NAMESPACE()

namespace std
{
    template <typename TypeT, typename ParameterT, template <typename> class... SkillsT>
    struct hash<phi::NamedType<TypeT, ParameterT, SkillsT...>>
    {
        using NamedType       = phi::NamedType<TypeT, ParameterT, SkillsT...>;
        using checkIfHashable = typename enable_if<NamedType::is_hashable, void>::type;

        size_t operator()(const NamedType& value) const noexcept
        {
            static_assert(noexcept(std::hash<TypeT>()(value.get())),
                          "hash fuction should not throw");

            return std::hash<TypeT>()(value.get());
        }
    };

} // namespace std

#undef PHI_EBCO

#endif // INCG_PHI_CORE_NAMEDTYPE_HPP
