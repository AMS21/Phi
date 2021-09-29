// This file is heavily inspired by Jonathan Boccaras NamedType library https://github.com/joboccara/NamedType
// licensed under the MIT license https://github.com/joboccara/NamedType/blob/master/LICENSE
// Original file at https://github.com/joboccara/NamedType/blob/master/test/tests.cpp
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

#include <catch2/catch.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Config/Compiler.hpp>
#include <Phi/Core/NamedType.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

// Usage examples

using Meter =
        phi::NamedType<unsigned long long, struct MeterParameter, phi::Addable, phi::Comparable>;
constexpr Meter operator"" _meter(unsigned long long value)
{
    return Meter(value);
}

using Width  = phi::NamedType<Meter, struct WidthParameter>;
using Height = phi::NamedType<Meter, struct HeightParameter>;

class Rectangle
{
public:
    Rectangle(Width width, Height height)
        : width_(width.get())
        , height_(height.get())
    {}
    Meter getWidth() const
    {
        return width_;
    }
    Meter getHeight() const
    {
        return height_;
    }

private:
    Meter width_;
    Meter height_;
};

TEST_CASE("Basic usage")
{
    Rectangle r(Width(10_meter), Height(12_meter));
    REQUIRE(r.getWidth().get() == 10);
    REQUIRE(r.getHeight().get() == 12);
}

using NameRef = phi::NamedType<std::string&, struct NameRefParameter>;

void changeValue(NameRef name)
{
    name.get() = "value2";
}

TEST_CASE("Passing a strong reference")
{
    std::string value = "value1";
    changeValue(NameRef(value));
    REQUIRE(value == "value2");
}

TEST_CASE("Construction of NamedType::ref from the underlying type")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag>;
    auto addOne     = [](StrongInt::reference si) { ++(si.get()); };

    int i = 42;
    addOne(StrongInt::reference(i));
    REQUIRE(i == 43);
}

TEST_CASE("Implicit conversion of NamedType to NamedType::ref")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag>;
    auto addOne     = [](StrongInt::reference si) { ++(si.get()); };

    StrongInt i(42);
    addOne(i);
    REQUIRE(i.get() == 43);

    StrongInt j(42);
    addOne(StrongInt::reference(j));
    REQUIRE(j.get() == 43);
}

struct PotentiallyThrowing
{
    PotentiallyThrowing()
    {}
};

struct NonDefaultConstructible
{
    NonDefaultConstructible(int)
    {}
};

struct UserProvided
{
    UserProvided();
};
UserProvided::UserProvided() = default;

TEST_CASE("Default construction")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag>;
    StrongInt strongInt;
    strongInt.get() = 42;
    REQUIRE(strongInt.get() == 42);
    STATIC_REQUIRE(std::is_nothrow_constructible<StrongInt>::value);

    //Default constructible
    STATIC_REQUIRE(std::is_default_constructible<StrongInt>::value);
    using StrongNonDefaultConstructible =
            phi::NamedType<NonDefaultConstructible, struct StrongNonDefaultConstructibleTag>;
    STATIC_REQUIRE_FALSE(std::is_default_constructible<StrongNonDefaultConstructible>::value);

    //Trivially constructible
    STATIC_REQUIRE(std::is_trivially_constructible<StrongInt>::value);
    using StrongUserProvided = phi::NamedType<UserProvided, struct StrongUserProvidedTag>;
    STATIC_REQUIRE_FALSE(std::is_trivially_constructible<StrongUserProvided>::value);

    //Nothrow constructible
    STATIC_REQUIRE(std::is_nothrow_constructible<StrongInt>::value);
    using StrongPotentiallyThrowing =
            phi::NamedType<PotentiallyThrowing, struct StrongPotentiallyThrowingTag>;
    STATIC_REQUIRE_FALSE(std::is_nothrow_constructible<StrongPotentiallyThrowing>::value);
}

template <typename Function>
using Comparator = phi::NamedType<Function, struct ComparatorParameter>;

template <typename Function>
std::string performAction(Comparator<Function> comp)
{
    return comp.get()();
}

TEST_CASE("Strong generic type")
{
    REQUIRE(performAction(phi::make_named<Comparator>([]() { return std::string("compare"); })) ==
            "compare");
}

TEST_CASE("Addable")
{
    using AddableType = phi::NamedType<int, struct AddableTag, phi::Addable>;
    AddableType s1(12);
    AddableType s2(10);
    REQUIRE((s1 + s2).get() == 22);
    REQUIRE((+s1).get() == 12);
}

TEST_CASE("Addable constexpr")
{
    using AddableType = phi::NamedType<int, struct AddableTag, phi::Addable>;
    constexpr AddableType s1(12);
    constexpr AddableType s2(10);
    EXT_STATIC_REQUIRE((s1 + s2).get() == 22);
    EXT_STATIC_REQUIRE((+s1).get() == 12);
}

TEST_CASE("BinaryAddable")
{
    using BinaryAddableType = phi::NamedType<int, struct BinaryAddableTag, phi::BinaryAddable>;
    BinaryAddableType s1(12);
    BinaryAddableType s2(10);
    REQUIRE((s1 + s2).get() == 22);
}

TEST_CASE("BinaryAddable constexpr")
{
    using BinaryAddableType = phi::NamedType<int, struct BinaryAddableTag, phi::BinaryAddable>;

    constexpr BinaryAddableType s1(12);
    constexpr BinaryAddableType s2(10);
    EXT_STATIC_REQUIRE((s1 + s2).get() == 22);

    constexpr BinaryAddableType s(10);
    EXT_STATIC_REQUIRE(BinaryAddableType{12}.operator+=(s).get() == 22);
}

TEST_CASE("UnaryAddable")
{
    using UnaryAddableType = phi::NamedType<int, struct UnaryAddableTag, phi::UnaryAddable>;
    UnaryAddableType s1(12);
    REQUIRE((+s1).get() == 12);
}

TEST_CASE("UnaryAddable constexpr")
{
    using UnaryAddableType = phi::NamedType<int, struct UnaryAddableTag, phi::UnaryAddable>;
    constexpr UnaryAddableType s1(12);
    EXT_STATIC_REQUIRE((+s1).get() == 12);
}

TEST_CASE("Subtractable")
{
    using SubtractableType = phi::NamedType<int, struct SubtractableTag, phi::Subtractable>;
    SubtractableType s1(12);
    SubtractableType s2(10);
    REQUIRE((s1 - s2).get() == 2);
    REQUIRE((-s1).get() == -12);
}

TEST_CASE("Subtractable constexpr")
{
    using SubtractableType = phi::NamedType<int, struct SubtractableTag, phi::Subtractable>;
    constexpr SubtractableType s1(12);
    constexpr SubtractableType s2(10);
    EXT_STATIC_REQUIRE((s1 - s2).get() == 2);
    EXT_STATIC_REQUIRE((-s1).get() == -12);
}

TEST_CASE("BinarySubtractable")
{
    using BinarySubtractableType =
            phi::NamedType<int, struct BinarySubtractableTag, phi::BinarySubtractable>;
    BinarySubtractableType s1(12);
    BinarySubtractableType s2(10);
    REQUIRE((s1 - s2).get() == 2);
}

TEST_CASE("BinarySubtractable constexpr")
{
    using BinarySubtractableType =
            phi::NamedType<int, struct BinarySubtractableTag, phi::BinarySubtractable>;

    constexpr BinarySubtractableType s1(12);
    constexpr BinarySubtractableType s2(10);
    EXT_STATIC_REQUIRE((s1 - s2).get() == 2);

    constexpr BinarySubtractableType s(10);
    EXT_STATIC_REQUIRE(BinarySubtractableType{12}.operator-=(s).get() == 2);
}

TEST_CASE("UnarySubtractable")
{
    using UnarySubtractableType =
            phi::NamedType<int, struct UnarySubtractableTag, phi::UnarySubtractable>;
    UnarySubtractableType s(12);
    REQUIRE((-s).get() == -12);
}

TEST_CASE("UnarySubtractable constexpr")
{
    using UnarySubtractableType =
            phi::NamedType<int, struct UnarySubtractableTag, phi::UnarySubtractable>;
    constexpr UnarySubtractableType s(12);
    EXT_STATIC_REQUIRE((-s).get() == -12);
}

TEST_CASE("Multiplicable")
{
    using MultiplicableType = phi::NamedType<int, struct MultiplicableTag, phi::Multiplicable>;
    MultiplicableType s1(12);
    MultiplicableType s2(10);
    REQUIRE((s1 * s2).get() == 120);
    s1 *= s2;
    REQUIRE(s1.get() == 120);
}

TEST_CASE("Multiplicable constexpr")
{
    using MultiplicableType = phi::NamedType<int, struct MultiplicableTag, phi::Multiplicable>;

    constexpr MultiplicableType s1(12);
    constexpr MultiplicableType s2(10);
    EXT_STATIC_REQUIRE((s1 * s2).get() == 120);

    constexpr MultiplicableType s(10);
    EXT_STATIC_REQUIRE(MultiplicableType{12}.operator*=(s).get() == 120);
}

TEST_CASE("Divisible")
{
    using DivisibleType = phi::NamedType<int, struct DivisibleTag, phi::Divisible>;
    DivisibleType s1(120);
    DivisibleType s2(10);
    REQUIRE((s1 / s2).get() == 12);
    s1 /= s2;
    REQUIRE(s1.get() == 12);
}

TEST_CASE("Divisible constexpr")
{
    using DivisibleType = phi::NamedType<int, struct DivisibleTag, phi::Divisible>;

    constexpr DivisibleType s1(120);
    constexpr DivisibleType s2(10);
    EXT_STATIC_REQUIRE((s1 / s2).get() == 12);

    constexpr DivisibleType s(10);
    EXT_STATIC_REQUIRE(DivisibleType{120}.operator/=(s).get() == 12);
}

TEST_CASE("Modulable")
{
    using ModulableType = phi::NamedType<int, struct ModulableTag, phi::Modulable>;
    ModulableType s1(5);
    ModulableType s2(2);
    CHECK((s1 % s2).get() == 1);
    s1 %= s2;
    CHECK(s1.get() == 1);
}

TEST_CASE("Modulable constexpr")
{
    using ModulableType = phi::NamedType<int, struct ModulableTag, phi::Modulable>;

    constexpr ModulableType s1(5);
    constexpr ModulableType s2(2);
    EXT_STATIC_REQUIRE((s1 % s2).get() == 1);

    constexpr ModulableType s(2);
    EXT_STATIC_REQUIRE(ModulableType{5}.operator%=(s).get() == 1);
}

TEST_CASE("BitWiseInvertable")
{
    using BitWiseInvertableType =
            phi::NamedType<int, struct BitWiseInvertableTag, phi::BitWiseInvertable>;
    BitWiseInvertableType s1(13);
    CHECK((~s1).get() == (~13));
}

TEST_CASE("BitWiseInvertable constexpr")
{
    using BitWiseInvertableType =
            phi::NamedType<int, struct BitWiseInvertableTag, phi::BitWiseInvertable>;
    constexpr BitWiseInvertableType s1(13);
    EXT_STATIC_REQUIRE((~s1).get() == (~13));
}

TEST_CASE("BitWiseAndable")
{
    using BitWiseAndableType = phi::NamedType<int, struct BitWiseAndableTag, phi::BitWiseAndable>;
    BitWiseAndableType s1(2);
    BitWiseAndableType s2(64);
    CHECK((s1 & s2).get() == (2 & 64));
    s1 &= s2;
    CHECK(s1.get() == (2 & 64));
}

TEST_CASE("BitWiseAndable constexpr")
{
    using BitWiseAndableType = phi::NamedType<int, struct BitWiseAndableTag, phi::BitWiseAndable>;

    constexpr BitWiseAndableType s1(2);
    constexpr BitWiseAndableType s2(64);
    EXT_STATIC_REQUIRE((s1 & s2).get() == (2 & 64));

    constexpr BitWiseAndableType s(64);
    EXT_STATIC_REQUIRE(BitWiseAndableType{2}.operator&=(s).get() == (2 & 64));
}

TEST_CASE("BitWiseOrable")
{
    using BitWiseOrableType = phi::NamedType<int, struct BitWiseOrableTag, phi::BitWiseOrable>;
    BitWiseOrableType s1(2);
    BitWiseOrableType s2(64);
    CHECK((s1 | s2).get() == (2 | 64));
    s1 |= s2;
    CHECK(s1.get() == (2 | 64));
}

TEST_CASE("BitWiseOrable constexpr")
{
    using BitWiseOrableType = phi::NamedType<int, struct BitWiseOrableTag, phi::BitWiseOrable>;

    constexpr BitWiseOrableType s1(2);
    constexpr BitWiseOrableType s2(64);
    EXT_STATIC_REQUIRE((s1 | s2).get() == (2 | 64));

    constexpr BitWiseOrableType s(64);
    EXT_STATIC_REQUIRE(BitWiseOrableType{2}.operator|=(s).get() == (2 | 64));
}

TEST_CASE("BitWiseXorable")
{
    using BitWiseXorableType = phi::NamedType<int, struct BitWiseXorableTag, phi::BitWiseXorable>;
    BitWiseXorableType s1(2);
    BitWiseXorableType s2(64);
    CHECK((s1 ^ s2).get() == (2 ^ 64));
    s1 ^= s2;
    CHECK(s1.get() == (2 ^ 64));
}

TEST_CASE("BitWiseXorable constexpr")
{
    using BitWiseXorableType = phi::NamedType<int, struct BitWiseXorableTag, phi::BitWiseXorable>;
    constexpr BitWiseXorableType s1(2);
    constexpr BitWiseXorableType s2(64);
    EXT_STATIC_REQUIRE((s1 ^ s2).get() == 66);

    constexpr BitWiseXorableType s(64);
    EXT_STATIC_REQUIRE(BitWiseXorableType{2}.operator^=(s).get() == 66);
}

TEST_CASE("BitWiseLeftShiftable")
{
    using BitWiseLeftShiftableType =
            phi::NamedType<int, struct BitWiseLeftShiftableTag, phi::BitWiseLeftShiftable>;
    BitWiseLeftShiftableType s1(2);
    BitWiseLeftShiftableType s2(3);
    CHECK((s1 << s2).get() == (2 << 3));
    s1 <<= s2;
    CHECK(s1.get() == (2 << 3));
}

TEST_CASE("BitWiseLeftShiftable constexpr")
{
    using BitWiseLeftShiftableType =
            phi::NamedType<int, struct BitWiseLeftShiftableTag, phi::BitWiseLeftShiftable>;
    constexpr BitWiseLeftShiftableType s1(2);
    constexpr BitWiseLeftShiftableType s2(3);
    EXT_STATIC_REQUIRE((s1 << s2).get() == (2 << 3));

    constexpr BitWiseLeftShiftableType s(3);
    EXT_STATIC_REQUIRE(BitWiseLeftShiftableType{2}.operator<<=(s).get() == (2 << 3));
}

TEST_CASE("BitWiseRightShiftable")
{
    using BitWiseRightShiftableType =
            phi::NamedType<int, struct BitWiseRightShiftableTag, phi::BitWiseRightShiftable>;
    BitWiseRightShiftableType s1(2);
    BitWiseRightShiftableType s2(3);
    CHECK((s1 >> s2).get() == (2 >> 3));
    s1 >>= s2;
    CHECK(s1.get() == (2 >> 3));
}

TEST_CASE("BitWiseRightShiftable constexpr")
{
    using BitWiseRightShiftableType =
            phi::NamedType<int, struct BitWiseRightShiftableTag, phi::BitWiseRightShiftable>;
    constexpr BitWiseRightShiftableType s1(2);
    constexpr BitWiseRightShiftableType s2(3);
    EXT_STATIC_REQUIRE((s1 >> s2).get() == (2 >> 3));

    constexpr BitWiseRightShiftableType s(3);
    EXT_STATIC_REQUIRE(BitWiseRightShiftableType{2}.operator>>=(s).get() == (2 >> 3));
}

TEST_CASE("Comparable")
{
    REQUIRE((10_meter == 10_meter));
    REQUIRE(!(10_meter == 11_meter));
    REQUIRE((10_meter != 11_meter));
    REQUIRE(!(10_meter != 10_meter));
    REQUIRE((10_meter < 11_meter));
    REQUIRE(!(10_meter < 10_meter));
    REQUIRE((10_meter <= 10_meter));
    REQUIRE((10_meter <= 11_meter));
    REQUIRE(!(10_meter <= 9_meter));
    REQUIRE((11_meter > 10_meter));
    REQUIRE(!(10_meter > 11_meter));
    REQUIRE((11_meter >= 10_meter));
    REQUIRE((10_meter >= 10_meter));
    REQUIRE(!(9_meter >= 10_meter));
}

TEST_CASE("Comparable constexpr")
{
    EXT_STATIC_REQUIRE((10_meter == 10_meter));
    EXT_STATIC_REQUIRE(!(10_meter == 11_meter));
    EXT_STATIC_REQUIRE((10_meter != 11_meter));
    EXT_STATIC_REQUIRE(!(10_meter != 10_meter));
    EXT_STATIC_REQUIRE((10_meter < 11_meter));
    EXT_STATIC_REQUIRE(!(10_meter < 10_meter));
    EXT_STATIC_REQUIRE((10_meter <= 10_meter));
    EXT_STATIC_REQUIRE((10_meter <= 11_meter));
    EXT_STATIC_REQUIRE(!(10_meter <= 9_meter));
    EXT_STATIC_REQUIRE((11_meter > 10_meter));
    EXT_STATIC_REQUIRE(!(10_meter > 11_meter));
    EXT_STATIC_REQUIRE((11_meter >= 10_meter));
    EXT_STATIC_REQUIRE((10_meter >= 10_meter));
    EXT_STATIC_REQUIRE(!(9_meter >= 10_meter));
}

TEST_CASE("ConvertibleWithOperator")
{
    struct B
    {
        B(int x_)
            : x(x_)
        {}
        int x;
    };

    struct A
    {
        A(int x_)
            : x(x_)
        {}
        operator B() const
        {
            return B(x);
        }
        int x;
    };

    using StrongA = phi::NamedType<A, struct StrongATag, phi::ImplicitlyConvertibleTo<B>::templ>;
    StrongA strongA(A(42));
    B       b = strongA;
    REQUIRE(b.x == 42);
}

TEST_CASE("ConvertibleWithOperator constexpr")
{
    struct B
    {
        constexpr B(int x_)
            : x(x_)
        {}
        int x;
    };

    struct A
    {
        constexpr A(int x_)
            : x(x_)
        {}
        constexpr operator B() const
        {
            return B(x);
        }
        int x;
    };

    using StrongA = phi::NamedType<A, struct StrongATag, phi::ImplicitlyConvertibleTo<B>::templ>;
    EXT_CONSTEXPR_RUNTIME StrongA strongA(A(42));
    EXT_CONSTEXPR_RUNTIME B       b = strongA;
    EXT_STATIC_REQUIRE(b.x == 42);
}

TEST_CASE("ConvertibleWithConstructor")
{
    struct A
    {
        A(int x_)
            : x(x_)
        {}
        int x;
    };

    struct B
    {
        B(A a)
            : x(a.x)
        {}
        int x;
    };

    using StrongA = phi::NamedType<A, struct StrongATag, phi::ImplicitlyConvertibleTo<B>::templ>;
    StrongA strongA(A(42));
    B       b = strongA;
    REQUIRE(b.x == 42);
}

TEST_CASE("ConvertibleWithConstructor constexpr")
{
    struct A
    {
        constexpr A(int x_)
            : x(x_)
        {}
        int x;
    };

    struct B
    {
        constexpr B(A a)
            : x(a.x)
        {}
        int x;
    };

    using StrongA = phi::NamedType<A, struct StrongATag, phi::ImplicitlyConvertibleTo<B>::templ>;
    EXT_CONSTEXPR_RUNTIME StrongA strongA(A(42));
    EXT_CONSTEXPR_RUNTIME B       b = strongA;
    EXT_STATIC_REQUIRE(b.x == 42);
}

TEST_CASE("ConvertibleToItself")
{
    using MyInt = phi::NamedType<int, struct MyIntTag, phi::ImplicitlyConvertibleTo<int>::templ>;
    MyInt myInt(42);
    int   i = myInt;
    REQUIRE(i == 42);
}

TEST_CASE("ConvertibleToItself constexpr")
{
    using MyInt = phi::NamedType<int, struct MyIntTag, phi::ImplicitlyConvertibleTo<int>::templ>;
    EXT_CONSTEXPR_RUNTIME MyInt myInt(42);
    EXT_CONSTEXPR_RUNTIME int   i = myInt;
    EXT_STATIC_REQUIRE(i == 42);
}

TEST_CASE("Hash")
{
    using SerialNumber =
            phi::NamedType<std::string, struct SerialNumberTag, phi::Comparable, phi::Hashable>;

    std::unordered_map<SerialNumber, int> hashMap = {{SerialNumber{"AA11"}, 10},
                                                     {SerialNumber{"BB22"}, 20}};
    SerialNumber                          cc33{"CC33"};
    hashMap[cc33] = 30;
    REQUIRE(hashMap[SerialNumber{"AA11"}] == 10);
    REQUIRE(hashMap[SerialNumber{"BB22"}] == 20);
    REQUIRE(hashMap[cc33] == 30);
}

struct testFunctionCallable_A
{
    testFunctionCallable_A(int x_)
        : x(x_)
    {}
    // ensures that passing the argument to a function doesn't make a copy
    testFunctionCallable_A(testFunctionCallable_A const&) = delete;
    testFunctionCallable_A(testFunctionCallable_A&&)      = default;
    testFunctionCallable_A& operator+=(testFunctionCallable_A const& other)
    {
        x += other.x;
        return *this;
    }
    int x;
};

testFunctionCallable_A operator+(testFunctionCallable_A const& a1, testFunctionCallable_A const& a2)
{
    return testFunctionCallable_A(a1.x + a2.x);
}

bool operator==(testFunctionCallable_A const& a1, testFunctionCallable_A const& a2)
{
    return a1.x == a2.x;
}

TEST_CASE("Function callable")
{
    using A              = testFunctionCallable_A;
    auto functionTakingA = [](A const& a) { return a.x; };

    using StrongA = phi::NamedType<A, struct StrongATag, phi::FunctionCallable>;
    StrongA       strongA(A(42));
    const StrongA constStrongA(A(42));
    REQUIRE(functionTakingA(strongA) == 42);
    REQUIRE(functionTakingA(constStrongA) == 42);
    REQUIRE(strongA + strongA == 84);
}

struct testFunctionCallable_B
{
    constexpr testFunctionCallable_B(int x_)
        : x(x_)
    {}
    // ensures that passing the argument to a function doesn't make a copy
    testFunctionCallable_B(testFunctionCallable_B const&) = delete;
    testFunctionCallable_B(testFunctionCallable_B&&)      = default;
    PHI_EXTENDED_CONSTEXPR testFunctionCallable_B& operator+=(testFunctionCallable_B const& other)
    {
        x += other.x;
        return *this;
    }
    int x;
};

constexpr testFunctionCallable_B operator+(testFunctionCallable_B const& a1,
                                           testFunctionCallable_B const& a2)
{
    return testFunctionCallable_B(a1.x + a2.x);
}

constexpr bool operator==(testFunctionCallable_B const& a1, testFunctionCallable_B const& a2)
{
    return a1.x == a2.x;
}

constexpr int functionTakingB(testFunctionCallable_B const& b)
{
    return b.x;
}

TEST_CASE("Function callable constexpr")
{
    using B = testFunctionCallable_B;

    using StrongB = phi::NamedType<B, struct StrongATag, phi::FunctionCallable>;
    constexpr StrongB constStrongB(B(42));
    EXT_STATIC_REQUIRE(functionTakingB(StrongB(B(42))) == 42);
    EXT_STATIC_REQUIRE(functionTakingB(constStrongB) == 42);
    EXT_STATIC_REQUIRE(StrongB(B(42)) + StrongB(B(42)) == 84);
    EXT_STATIC_REQUIRE(constStrongB + constStrongB == 84);
}

TEST_CASE("Method callable")
{
    class A
    {
    public:
        A(int x_)
            : x(x_)
        {}
        A(A const&) = delete; // ensures that invoking a method doesn't make a copy
        A(A&&)      = default;

        int method()
        {
            return x;
        }
        int constMethod() const
        {
            return x;
        }

    private:
        int x;
    };

    using StrongA = phi::NamedType<A, struct StrongATag, phi::MethodCallable>;
    StrongA       strongA(A(42));
    const StrongA constStrongA(A((42)));
    REQUIRE(strongA->method() == 42);
    REQUIRE(constStrongA->constMethod() == 42);
}

TEST_CASE("Method callable constexpr")
{
    class A
    {
    public:
        constexpr A(int x_)
            : x(x_)
        {}
        A(A const&) = delete; // ensures that invoking a method doesn't make a copy
        A(A&&)      = default;

        constexpr int method()
        {
            return x;
        }
        constexpr int constMethod() const
        {
            return x;
        }

    private:
        int x;
    };

    using StrongA = phi::NamedType<A, struct StrongATag, phi::MethodCallable>;
    EXT_CONSTEXPR_RUNTIME const StrongA constStrongA(A((42)));
    EXT_STATIC_REQUIRE(StrongA(A(42))->method() == 42);
    EXT_STATIC_REQUIRE(constStrongA->constMethod() == 42);
}

TEST_CASE("Callable")
{
    class A
    {
    public:
        A(int x_)
            : x(x_)
        {}
        A(A const&) = delete; // ensures that invoking a method or function doesn't make a copy
        A(A&&)      = default;

        int method()
        {
            return x;
        }
        int constMethod() const
        {
            return x;
        }

    private:
        int x;
    };

    auto functionTakingA = [](A const& a) { return a.constMethod(); };

    using StrongA = phi::NamedType<A, struct StrongATag, phi::Callable>;
    StrongA       strongA(A(42));
    const StrongA constStrongA(A(42));
    REQUIRE(functionTakingA(strongA) == 42);
    REQUIRE(strongA->method() == 42);
    REQUIRE(constStrongA->constMethod() == 42);
}

TEST_CASE("Named arguments")
{
    using FirstName = phi::NamedType<std::string, struct FirstNameTag>;
    using LastName  = phi::NamedType<std::string, struct LastNameTag>;
    static const FirstName::Argument firstName;
    static const LastName::Argument  lastName;
    auto getFullName = [](FirstName const& firstName_, LastName const& lastName_) //
    {
        return firstName_.get() + lastName_.get(); //
    };

    auto fullName = getFullName(firstName = "James", lastName = "Bond");
    REQUIRE(fullName == "JamesBond");
}

TEST_CASE("Named arguments with bracket constructor")
{
    using Numbers = phi::NamedType<std::vector<int>, struct NumbersTag>;
    static const Numbers::Argument numbers;
    auto getNumbers = [](Numbers const& numbers_) { return numbers_.get(); };

    auto vec = getNumbers(numbers = {1, 2, 3});
    REQUIRE(vec == std::vector<int>{1, 2, 3});
}

TEST_CASE("Empty base class optimization")
{
    REQUIRE(sizeof(Meter) == sizeof(double));
}

using strong_int = phi::NamedType<int, struct IntTag>;

TEST_CASE("constexpr")
{
    using strong_bool = phi::NamedType<bool, struct BoolTag>;

    EXT_STATIC_REQUIRE(strong_bool{true}.get());
}

struct throw_on_construction
{
    [[noreturn]] throw_on_construction()
    {
        throw 42;
    }

    [[noreturn]] throw_on_construction(int)
    {
        throw "exception";
    }
};

using C = phi::NamedType<throw_on_construction, struct throwTag>;

TEST_CASE("noexcept")
{
    CHECK(noexcept(strong_int{}));
    CHECK(!noexcept(C{}));

    CHECK(noexcept(strong_int(3)));
    CHECK(!noexcept(C{5}));
}

TEST_CASE("Arithmetic")
{
    using strong_arithmetic = phi::NamedType<int, struct ArithmeticTag, phi::Arithmetic>;
    strong_arithmetic a{1};
    strong_arithmetic b{2};

    CHECK((a + b).get() == 3);

    a += b;
    CHECK(a.get() == 3);

    CHECK((a - b).get() == 1);

    a -= b;
    CHECK(a.get() == 1);

    a.get() = 5;
    CHECK((a * b).get() == 10);

    a *= b;
    CHECK(a.get() == 10);

    CHECK((a / b).get() == 5);

    a /= b;
    CHECK(a.get() == 5);
}

TEST_CASE("Printable")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::Printable>;

    std::ostringstream oss;
    oss << StrongInt(42);
    CHECK(oss.str() == "42");
}

TEST_CASE("Dereferencable")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::Dereferencable>;

    {
        StrongInt a{1};
        int&      value = *a;
        CHECK(value == 1);
    }

    {
        const StrongInt a{1};
        const int&      value = *a;
        CHECK(value == 1);
    }

    {
        StrongInt a{1};
        int&      value = *a;
        value           = 2;
        CHECK(a.get() == 2);
    }

    {
        auto functionReturningStrongInt = []() { return StrongInt{28}; };
        auto functionTakingInt          = [](int value) { return value; };

        int value = functionTakingInt(*functionReturningStrongInt());
        CHECK(value == 28);
    }
}

TEST_CASE("Dereferencable constexpr")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::Dereferencable>;

    EXT_CONSTEXPR_RUNTIME StrongInt a{28};
    EXT_STATIC_REQUIRE(*a == 28);
    EXT_STATIC_REQUIRE(*StrongInt{28} == 28);
}

TEST_CASE("PreIncrementable")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::PreIncrementable>;
    StrongInt a{1};
    StrongInt b = ++a;
    CHECK(a.get() == 2);
    CHECK(b.get() == 2);
}

TEST_CASE("PreIncrementable constexpr")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::PreIncrementable>;
    EXT_STATIC_REQUIRE((++StrongInt{1}).get() == 2);
}

TEST_CASE("PostIncrementable")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::PostIncrementable>;
    StrongInt a{1};
    StrongInt b = a++;
    CHECK(a.get() == 2);
    CHECK(b.get() == 1);
}

TEST_CASE("PostIncrementable constexpr")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::PostIncrementable>;
    EXT_STATIC_REQUIRE((StrongInt { 1 } ++).get() == 1);
}

TEST_CASE("PreDecrementable")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::PreDecrementable>;
    StrongInt a{1};
    StrongInt b = --a;
    CHECK(a.get() == 0);
    CHECK(b.get() == 0);
}

TEST_CASE("PreDecrementable constexpr")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::PreDecrementable>;
    EXT_STATIC_REQUIRE((--StrongInt{1}).get() == 0);
}

TEST_CASE("PostDecrementable")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::PostDecrementable>;
    StrongInt a{1};
    StrongInt b = a--;
    CHECK(a.get() == 0);
    CHECK(b.get() == 1);
}

TEST_CASE("PostDecrementable constexpr")
{
    using StrongInt = phi::NamedType<int, struct StrongIntTag, phi::PostDecrementable>;
    EXT_STATIC_REQUIRE((StrongInt { 1 } --).get() == 1);
}
