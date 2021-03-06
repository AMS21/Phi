// This file is heavily inspired by Sy Brands Optional library https://github.com/TartanLlama/Optional
// licensed under CC0 https://github.com/TartanLlama/Optional/blob/master/COPYING
// Original files at
// * https://github.com/TartanLlama/optional/blob/master/tests/assignment.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/bases.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/constexpr.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/constructors.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/emplace.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/extensions.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/in_place.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/issues.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/make_optional.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/noexcept.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/nullopt.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/observers.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/relops.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/swap.cpp

#include <Phi/Core/Optional.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

TEST_CASE("Optional Assigment value")
{
    phi::Optional<int> o1 = 42;
    phi::Optional<int> o2 = 12;
    phi::Optional<int> o3;

    o1 = o1;
    REQUIRE(*o1 == 42);

    o1 = o2;
    REQUIRE(*o1 == 12);

    o1 = o3;
    REQUIRE(!o1);

    o1 = 42;
    REQUIRE(*o1 == 42);

    o1 = phi::nullopt;
    REQUIRE(!o1);

    o1 = std::move(o2);
    REQUIRE(*o1 == 12);

    phi::Optional<short> o4 = 42;

    o1 = o4;
    REQUIRE(*o1 == 42);

    o1 = std::move(o4);
    REQUIRE(*o1 == 42);
}

TEST_CASE("Optional assignment reference")
{
    auto i = 42;
    auto j = 12;

    phi::Optional<int&> o1 = i;
    phi::Optional<int&> o2 = j;
    phi::Optional<int&> o3;

    o1 = o1;
    REQUIRE(*o1 == 42);
    REQUIRE(&*o1 == &i);

    o1 = o2;
    REQUIRE(*o1 == 12);

    o1 = o3;
    REQUIRE(!o1);

    auto k = 42;
    o1     = k;
    REQUIRE(*o1 == 42);
    REQUIRE(*o1 == i);
    REQUIRE(*o1 == k);
    REQUIRE(&*o1 != &i);
    REQUIRE(&*o1 == &k);

    k = 12;
    REQUIRE(*o1 == 12);

    o1 = phi::nullopt;
    REQUIRE(!o1);

    o1 = std::move(o2);
    REQUIRE(*o1 == 12);
}

TEST_CASE("Optional triviality")
{
    REQUIRE(std::is_trivially_copy_constructible<phi::Optional<int>>::value);
    REQUIRE(std::is_trivially_copy_assignable<phi::Optional<int>>::value);
    REQUIRE(std::is_trivially_move_constructible<phi::Optional<int>>::value);
    REQUIRE(std::is_trivially_move_assignable<phi::Optional<int>>::value);
    REQUIRE(std::is_trivially_destructible<phi::Optional<int>>::value);

    {
        struct T
        {
            T(const T&) = default;
            T(T&&)      = default;
            T& operator=(const T&) = default;
            T& operator=(T&&) = default;
            ~T()              = default;
        };

        REQUIRE(std::is_trivially_copy_constructible<phi::Optional<T>>::value);
        REQUIRE(std::is_trivially_copy_assignable<phi::Optional<T>>::value);
        REQUIRE(std::is_trivially_move_constructible<phi::Optional<T>>::value);
        REQUIRE(std::is_trivially_move_assignable<phi::Optional<T>>::value);
        REQUIRE(std::is_trivially_destructible<phi::Optional<T>>::value);
    }

    {
        struct T
        {
            T(const T&)
            {}
            T(T&&){};
            T& operator=(const T&)
            {
                return *this;
            }
            T& operator=(T&&)
            {
                return *this;
            };
            ~T()
            {}
        };
        REQUIRE_FALSE(std::is_trivially_copy_constructible<phi::Optional<T>>::value);
        REQUIRE_FALSE(std::is_trivially_copy_assignable<phi::Optional<T>>::value);
        REQUIRE_FALSE(std::is_trivially_move_constructible<phi::Optional<T>>::value);
        REQUIRE_FALSE(std::is_trivially_move_assignable<phi::Optional<T>>::value);
        REQUIRE_FALSE(std::is_trivially_destructible<phi::Optional<T>>::value);
    }
}

TEST_CASE("Optional Deletion")
{
    REQUIRE(std::is_copy_constructible<phi::Optional<int>>::value);
    REQUIRE(std::is_copy_assignable<phi::Optional<int>>::value);
    REQUIRE(std::is_move_constructible<phi::Optional<int>>::value);
    REQUIRE(std::is_move_assignable<phi::Optional<int>>::value);
    REQUIRE(std::is_destructible<phi::Optional<int>>::value);

    {
        struct T
        {
            T(const T&) = default;
            T(T&&)      = default;
            T& operator=(const T&) = default;
            T& operator=(T&&) = default;
            ~T()              = default;
        };
        REQUIRE(std::is_copy_constructible<phi::Optional<T>>::value);
        REQUIRE(std::is_copy_assignable<phi::Optional<T>>::value);
        REQUIRE(std::is_move_constructible<phi::Optional<T>>::value);
        REQUIRE(std::is_move_assignable<phi::Optional<T>>::value);
        REQUIRE(std::is_destructible<phi::Optional<T>>::value);
    }

    {
        struct T
        {
            T(const T&) = delete;
            T(T&&)      = delete;
            T& operator=(const T&) = delete;
            T& operator=(T&&) = delete;
        };
        REQUIRE_FALSE(std::is_copy_constructible<phi::Optional<T>>::value);
        REQUIRE_FALSE(std::is_copy_assignable<phi::Optional<T>>::value);
        REQUIRE_FALSE(std::is_move_constructible<phi::Optional<T>>::value);
        REQUIRE_FALSE(std::is_move_assignable<phi::Optional<T>>::value);
    }

    {
        struct T
        {
            T(const T&) = delete;
            T(T&&)      = default;
            T& operator=(const T&) = delete;
            T& operator=(T&&) = default;
        };
        REQUIRE_FALSE(std::is_copy_constructible<phi::Optional<T>>::value);
        REQUIRE_FALSE(std::is_copy_assignable<phi::Optional<T>>::value);
        REQUIRE(std::is_move_constructible<phi::Optional<T>>::value);
        REQUIRE(std::is_move_assignable<phi::Optional<T>>::value);
    }

    {
        struct T
        {
            T(const T&) = default;
            T(T&&)      = delete;
            T& operator=(const T&) = default;
            T& operator=(T&&) = delete;
        };
        REQUIRE(std::is_copy_constructible<phi::Optional<T>>::value);
        REQUIRE(std::is_copy_assignable<phi::Optional<T>>::value);
    }
}

TEST_CASE("Optional constexpr")
{
    SECTION("empty construct")
    {
        constexpr phi::Optional<int> o2{};
        constexpr phi::Optional<int> o3 = {};
        constexpr phi::Optional<int> o4 = phi::nullopt;
        constexpr phi::Optional<int> o5 = {phi::nullopt};
        constexpr phi::Optional<int> o6(phi::nullopt);

        STATIC_REQUIRE(!o2);
        STATIC_REQUIRE(!o3);
        STATIC_REQUIRE(!o4);
        STATIC_REQUIRE(!o5);
        STATIC_REQUIRE(!o6);
    }

    SECTION("value construct")
    {
        constexpr phi::Optional<int> o1 = 42;
        constexpr phi::Optional<int> o2{42};
        constexpr phi::Optional<int> o3(42);
        constexpr phi::Optional<int> o4 = {42};
        constexpr int                i  = 42;
        constexpr phi::Optional<int> o5 = std::move(i);
        constexpr phi::Optional<int> o6{std::move(i)};
        constexpr phi::Optional<int> o7(std::move(i));
        constexpr phi::Optional<int> o8 = {std::move(i)};

        STATIC_REQUIRE(*o1 == 42);
        STATIC_REQUIRE(*o2 == 42);
        STATIC_REQUIRE(*o3 == 42);
        STATIC_REQUIRE(*o4 == 42);
        STATIC_REQUIRE(*o5 == 42);
        STATIC_REQUIRE(*o6 == 42);
        STATIC_REQUIRE(*o7 == 42);
        STATIC_REQUIRE(*o8 == 42);
    }
}

struct foo
{
    foo()     = default;
    foo(foo&) = delete;
    foo(foo&&){};
};

TEST_CASE("Optional Constructors")
{
    phi::Optional<int> o1;
    REQUIRE(!o1);

    phi::Optional<int> o2 = phi::nullopt;
    REQUIRE(!o2);

    phi::Optional<int> o3 = 42;
    REQUIRE(*o3 == 42);

    phi::Optional<int> o4 = o3;
    REQUIRE(*o4 == 42);

    phi::Optional<int> o5 = o1;
    REQUIRE(!o5);

    phi::Optional<int> o6 = std::move(o3);
    REQUIRE(*o6 == 42);

    phi::Optional<short> o7 = 42;
    REQUIRE(*o7 == 42);

    phi::Optional<int> o8 = o7;
    REQUIRE(*o8 == 42);

    phi::Optional<int> o9 = std::move(o7);
    REQUIRE(*o9 == 42);

    {
        phi::Optional<int&> o;
        REQUIRE(!o);

        phi::Optional<int&> oo = o;
        REQUIRE(!oo);
    }

    {
        auto                i = 42;
        phi::Optional<int&> o = i;
        REQUIRE(o);
        REQUIRE(*o == 42);

        phi::Optional<int&> oo = o;
        REQUIRE(oo);
        REQUIRE(*oo == 42);
    }

    std::vector<foo> v;
    v.emplace_back();
    phi::Optional<std::vector<foo>> ov = std::move(v);
    REQUIRE(ov->size() == 1);
}

TEST_CASE("Optional emplace")
{
    phi::Optional<std::pair<std::pair<int, int>, std::pair<double, double>>> i;
    i.emplace(std::piecewise_construct, std::make_tuple(0, 2), std::make_tuple(3, 4));
    REQUIRE(i->first.first == 0);
    REQUIRE(i->first.second == 2);
    REQUIRE(i->second.first == 3);
    REQUIRE(i->second.second == 4);
}

constexpr int get_int(int)
{
    return 42;
}

constexpr phi::Optional<int> get_opt_int(int)
{
    return 42;
}

TEST_CASE("Optional monadic operations", "[monadic]")
{
    SECTION("map")
    { // lhs is empty
        phi::Optional<int> o1;
        auto               o1r = o1.map([](int i) { return i + 2; });
        STATIC_REQUIRE((std::is_same<decltype(o1r), phi::Optional<int>>::value));
        REQUIRE(!o1r);

        // lhs has value
        phi::Optional<int> o2  = 40;
        auto               o2r = o2.map([](int i) { return i + 2; });
        STATIC_REQUIRE((std::is_same<decltype(o2r), phi::Optional<int>>::value));
        REQUIRE(o2r.value() == 42);

        struct rval_call_map
        {
            double operator()(int) &&
            {
                return 42.0;
            };
        };

        // ensure that function object is forwarded
        phi::Optional<int> o3  = 42;
        auto               o3r = o3.map(rval_call_map{});
        STATIC_REQUIRE((std::is_same<decltype(o3r), phi::Optional<double>>::value));
        REQUIRE(o3r.value() == 42);

        // ensure that lhs is forwarded
        phi::Optional<int> o4  = 40;
        auto               o4r = std::move(o4).map([](int&& i) { return i + 2; });
        STATIC_REQUIRE((std::is_same<decltype(o4r), phi::Optional<int>>::value));
        REQUIRE(o4r.value() == 42);

        // ensure that lhs is const-propagated
        const phi::Optional<int> o5  = 40;
        auto                     o5r = o5.map([](const int& i) { return i + 2; });
        STATIC_REQUIRE((std::is_same<decltype(o5r), phi::Optional<int>>::value));
        REQUIRE(o5r.value() == 42);

        // test void return
        phi::Optional<int> o7  = 40;
        auto               f7  = [](const int&) { return; };
        auto               o7r = o7.map(f7);
        STATIC_REQUIRE((std::is_same<decltype(o7r), phi::Optional<phi::monostate>>::value));
        REQUIRE(o7r.has_value());

        // test each overload in turn
        phi::Optional<int> o8  = 42;
        auto               o8r = o8.map([](int) { return 42; });
        REQUIRE(*o8r == 42);

        phi::Optional<int> o9  = 42;
        auto               o9r = o9.map([](int) { return; });
        REQUIRE(o9r);

        phi::Optional<int> o12  = 42;
        auto               o12r = std::move(o12).map([](int) { return 42; });
        REQUIRE(*o12r == 42);

        phi::Optional<int> o13  = 42;
        auto               o13r = std::move(o13).map([](int) { return; });
        REQUIRE(o13r);

        const phi::Optional<int> o16  = 42;
        auto                     o16r = o16.map([](int) { return 42; });
        REQUIRE(*o16r == 42);

        const phi::Optional<int> o17  = 42;
        auto                     o17r = o17.map([](int) { return; });
        REQUIRE(o17r);

        const phi::Optional<int> o20  = 42;
        auto                     o20r = std::move(o20).map([](int) { return 42; });
        REQUIRE(*o20r == 42);

        const phi::Optional<int> o21  = 42;
        auto                     o21r = std::move(o21).map([](int) { return; });
        REQUIRE(o21r);

        phi::Optional<int> o24  = phi::nullopt;
        auto               o24r = o24.map([](int) { return 42; });
        REQUIRE(!o24r);

        phi::Optional<int> o25  = phi::nullopt;
        auto               o25r = o25.map([](int) { return; });
        REQUIRE(!o25r);

        phi::Optional<int> o28  = phi::nullopt;
        auto               o28r = std::move(o28).map([](int) { return 42; });
        REQUIRE(!o28r);

        phi::Optional<int> o29  = phi::nullopt;
        auto               o29r = std::move(o29).map([](int) { return; });
        REQUIRE(!o29r);

        const phi::Optional<int> o32  = phi::nullopt;
        auto                     o32r = o32.map([](int) { return 42; });
        REQUIRE(!o32r);

        const phi::Optional<int> o33  = phi::nullopt;
        auto                     o33r = o33.map([](int) { return; });
        REQUIRE(!o33r);

        const phi::Optional<int> o36  = phi::nullopt;
        auto                     o36r = std::move(o36).map([](int) { return 42; });
        REQUIRE(!o36r);

        const phi::Optional<int> o37  = phi::nullopt;
        auto                     o37r = std::move(o37).map([](int) { return; });
        REQUIRE(!o37r);

        // callable which returns a reference
        phi::Optional<int> o38  = 42;
        auto               o38r = o38.map([](int& i) -> const int& { return i; });
        REQUIRE(o38r);
        REQUIRE(*o38r == 42);

        int                 i   = 42;
        phi::Optional<int&> o39 = i;
        o39.map([](int& x) { x = 12; });
        REQUIRE(i == 12);
    }

    SECTION("map constexpr")
    {
        // test each overload in turn
        constexpr phi::Optional<int> o16  = 42;
        constexpr auto               o16r = o16.map(get_int);
        STATIC_REQUIRE(*o16r == 42);

        constexpr phi::Optional<int> o20  = 42;
        constexpr auto               o20r = std::move(o20).map(get_int);
        STATIC_REQUIRE(*o20r == 42);

        constexpr phi::Optional<int> o32  = phi::nullopt;
        constexpr auto               o32r = o32.map(get_int);
        STATIC_REQUIRE(!o32r);
        constexpr phi::Optional<int> o36  = phi::nullopt;
        constexpr auto               o36r = std::move(o36).map(get_int);
        STATIC_REQUIRE(!o36r);
    }

    SECTION("transform")
    { // lhs is empty
        phi::Optional<int> o1;
        auto               o1r = o1.transform([](int i) { return i + 2; });
        STATIC_REQUIRE((std::is_same<decltype(o1r), phi::Optional<int>>::value));
        REQUIRE(!o1r);

        // lhs has value
        phi::Optional<int> o2  = 40;
        auto               o2r = o2.transform([](int i) { return i + 2; });
        STATIC_REQUIRE((std::is_same<decltype(o2r), phi::Optional<int>>::value));
        REQUIRE(o2r.value() == 42);

        struct rval_call_transform
        {
            double operator()(int) &&
            {
                return 42.0;
            }
        };

        // ensure that function object is forwarded
        phi::Optional<int> o3  = 42;
        auto               o3r = o3.transform(rval_call_transform{});
        STATIC_REQUIRE((std::is_same<decltype(o3r), phi::Optional<double>>::value));
        REQUIRE(o3r.value() == 42);

        // ensure that lhs is forwarded
        phi::Optional<int> o4  = 40;
        auto               o4r = std::move(o4).transform([](int&& i) { return i + 2; });
        STATIC_REQUIRE((std::is_same<decltype(o4r), phi::Optional<int>>::value));
        REQUIRE(o4r.value() == 42);

        // ensure that lhs is const-propagated
        const phi::Optional<int> o5  = 40;
        auto                     o5r = o5.transform([](const int& i) { return i + 2; });
        STATIC_REQUIRE((std::is_same<decltype(o5r), phi::Optional<int>>::value));
        REQUIRE(o5r.value() == 42);

        // test void return
        phi::Optional<int> o7  = 40;
        auto               f7  = [](const int&) { return; };
        auto               o7r = o7.transform(f7);
        STATIC_REQUIRE((std::is_same<decltype(o7r), phi::Optional<phi::monostate>>::value));
        REQUIRE(o7r.has_value());

        // test each overload in turn
        phi::Optional<int> o8  = 42;
        auto               o8r = o8.transform([](int) { return 42; });
        REQUIRE(*o8r == 42);

        phi::Optional<int> o9  = 42;
        auto               o9r = o9.transform([](int) { return; });
        REQUIRE(o9r);

        phi::Optional<int> o12  = 42;
        auto               o12r = std::move(o12).transform([](int) { return 42; });
        REQUIRE(*o12r == 42);

        phi::Optional<int> o13  = 42;
        auto               o13r = std::move(o13).transform([](int) { return; });
        REQUIRE(o13r);

        const phi::Optional<int> o16  = 42;
        auto                     o16r = o16.transform([](int) { return 42; });
        REQUIRE(*o16r == 42);

        const phi::Optional<int> o17  = 42;
        auto                     o17r = o17.transform([](int) { return; });
        REQUIRE(o17r);

        const phi::Optional<int> o20  = 42;
        auto                     o20r = std::move(o20).transform([](int) { return 42; });
        REQUIRE(*o20r == 42);

        const phi::Optional<int> o21  = 42;
        auto                     o21r = std::move(o21).transform([](int) { return; });
        REQUIRE(o21r);

        phi::Optional<int> o24  = phi::nullopt;
        auto               o24r = o24.transform([](int) { return 42; });
        REQUIRE(!o24r);

        phi::Optional<int> o25  = phi::nullopt;
        auto               o25r = o25.transform([](int) { return; });
        REQUIRE(!o25r);

        phi::Optional<int> o28  = phi::nullopt;
        auto               o28r = std::move(o28).transform([](int) { return 42; });
        REQUIRE(!o28r);

        phi::Optional<int> o29  = phi::nullopt;
        auto               o29r = std::move(o29).transform([](int) { return; });
        REQUIRE(!o29r);

        const phi::Optional<int> o32  = phi::nullopt;
        auto                     o32r = o32.transform([](int) { return 42; });
        REQUIRE(!o32r);

        const phi::Optional<int> o33  = phi::nullopt;
        auto                     o33r = o33.transform([](int) { return; });
        REQUIRE(!o33r);

        const phi::Optional<int> o36  = phi::nullopt;
        auto                     o36r = std::move(o36).transform([](int) { return 42; });
        REQUIRE(!o36r);

        const phi::Optional<int> o37  = phi::nullopt;
        auto                     o37r = std::move(o37).transform([](int) { return; });
        REQUIRE(!o37r);

        // callable which returns a reference
        phi::Optional<int> o38  = 42;
        auto               o38r = o38.transform([](int& i) -> const int& { return i; });
        REQUIRE(o38r);
        REQUIRE(*o38r == 42);

        int                 i   = 42;
        phi::Optional<int&> o39 = i;
        o39.transform([](int& x) { x = 12; });
        REQUIRE(i == 12);
    }

    SECTION("transform constexpr")
    {
        // test each overload in turn
        constexpr phi::Optional<int> o16  = 42;
        constexpr auto               o16r = o16.transform(get_int);
        STATIC_REQUIRE(*o16r == 42);

        constexpr phi::Optional<int> o20  = 42;
        constexpr auto               o20r = std::move(o20).transform(get_int);
        STATIC_REQUIRE(*o20r == 42);

        constexpr phi::Optional<int> o32  = phi::nullopt;
        constexpr auto               o32r = o32.transform(get_int);
        STATIC_REQUIRE(!o32r);
        constexpr phi::Optional<int> o36  = phi::nullopt;
        constexpr auto               o36r = std::move(o36).transform(get_int);
        STATIC_REQUIRE(!o36r);
    }

    SECTION("and_then")
    {
        // lhs is empty
        phi::Optional<int> o1;
        auto               o1r = o1.and_then([](int) { return phi::Optional<float>{42}; });
        STATIC_REQUIRE((std::is_same<decltype(o1r), phi::Optional<float>>::value));
        REQUIRE(!o1r);

        // lhs has value
        phi::Optional<int> o2  = 12;
        auto               o2r = o2.and_then([](int) { return phi::Optional<float>{42}; });
        STATIC_REQUIRE((std::is_same<decltype(o2r), phi::Optional<float>>::value));
        REQUIRE(o2r.value() == 42.f);

        // lhs is empty, rhs returns empty
        phi::Optional<int> o3;
        auto               o3r = o3.and_then([](int) { return phi::Optional<float>{}; });
        STATIC_REQUIRE((std::is_same<decltype(o3r), phi::Optional<float>>::value));
        REQUIRE(!o3r);

        // rhs returns empty
        phi::Optional<int> o4  = 12;
        auto               o4r = o4.and_then([](int) { return phi::Optional<float>{}; });
        STATIC_REQUIRE((std::is_same<decltype(o4r), phi::Optional<float>>::value));
        REQUIRE(!o4r);

        struct rval_call_and_then
        {
            phi::Optional<double> operator()(int) &&
            {
                return phi::Optional<double>(42.0);
            };
        };

        // ensure that function object is forwarded
        phi::Optional<int> o5  = 42;
        auto               o5r = o5.and_then(rval_call_and_then{});
        STATIC_REQUIRE((std::is_same<decltype(o5r), phi::Optional<double>>::value));
        REQUIRE(o5r.value() == 42);

        // ensure that lhs is forwarded
        phi::Optional<int> o6 = 42;
        auto o6r = std::move(o6).and_then([](int&& i) { return phi::Optional<double>(i); });
        STATIC_REQUIRE((std::is_same<decltype(o6r), phi::Optional<double>>::value));
        REQUIRE(o6r.value() == 42);

        // ensure that function object is const-propagated
        const phi::Optional<int> o7 = 42;
        auto o7r = o7.and_then([](const int& i) { return phi::Optional<double>(i); });
        STATIC_REQUIRE((std::is_same<decltype(o7r), phi::Optional<double>>::value));
        REQUIRE(o7r.value() == 42);

        // test each overload in turn
        phi::Optional<int> o8  = 42;
        auto               o8r = o8.and_then([](int) { return phi::make_optional(42); });
        REQUIRE(*o8r == 42);

        phi::Optional<int> o9  = 42;
        auto               o9r = std::move(o9).and_then([](int) { return phi::make_optional(42); });
        REQUIRE(*o9r == 42);

        const phi::Optional<int> o10  = 42;
        auto                     o10r = o10.and_then([](int) { return phi::make_optional(42); });
        REQUIRE(*o10r == 42);

        const phi::Optional<int> o11 = 42;
        auto o11r = std::move(o11).and_then([](int) { return phi::make_optional(42); });
        REQUIRE(*o11r == 42);

        phi::Optional<int> o16  = phi::nullopt;
        auto               o16r = o16.and_then([](int) { return phi::make_optional(42); });
        REQUIRE(!o16r);

        phi::Optional<int> o17 = phi::nullopt;
        auto o17r = std::move(o17).and_then([](int) { return phi::make_optional(42); });
        REQUIRE(!o17r);

        const phi::Optional<int> o18  = phi::nullopt;
        auto                     o18r = o18.and_then([](int) { return phi::make_optional(42); });
        REQUIRE(!o18r);

        const phi::Optional<int> o19 = phi::nullopt;
        auto o19r = std::move(o19).and_then([](int) { return phi::make_optional(42); });
        REQUIRE(!o19r);

        int                 i = 3;
        phi::Optional<int&> o20{i};
        std::move(o20).and_then([](int& r) { return phi::Optional<int&>{++r}; });
        REQUIRE(o20);
        REQUIRE(i == 4);
    }

    SECTION("constexpr and_then")
    {
        constexpr phi::Optional<int> o10  = 42;
        constexpr auto               o10r = o10.and_then(get_opt_int);
        REQUIRE(*o10r == 42);

        constexpr phi::Optional<int> o11  = 42;
        constexpr auto               o11r = std::move(o11).and_then(get_opt_int);
        REQUIRE(*o11r == 42);

        constexpr phi::Optional<int> o18  = phi::nullopt;
        constexpr auto               o18r = o18.and_then(get_opt_int);
        REQUIRE(!o18r);

        constexpr phi::Optional<int> o19  = phi::nullopt;
        constexpr auto               o19r = std::move(o19).and_then(get_opt_int);
        REQUIRE(!o19r);
    }

    SECTION("or else")
    {
        phi::Optional<int> o1 = 42;
        REQUIRE(*(o1.or_else([] { return phi::make_optional(13); })) == 42);

        phi::Optional<int> o2;
        REQUIRE(*(o2.or_else([] { return phi::make_optional(13); })) == 13);
    }

    SECTION("disjunction")
    {
        phi::Optional<int> o1 = 42;
        phi::Optional<int> o2 = 12;
        phi::Optional<int> o3;

        REQUIRE(*o1.disjunction(o2) == 42);
        REQUIRE(*o1.disjunction(o3) == 42);
        REQUIRE(*o2.disjunction(o1) == 12);
        REQUIRE(*o2.disjunction(o3) == 12);
        REQUIRE(*o3.disjunction(o1) == 42);
        REQUIRE(*o3.disjunction(o2) == 12);
    }

    SECTION("conjunction")
    {
        phi::Optional<int> o1 = 42;
        REQUIRE(*o1.conjunction(42.0) == 42.0);
        REQUIRE(*o1.conjunction(std::string{"hello"}) == std::string{"hello"});

        phi::Optional<int> o2;
        REQUIRE(!o2.conjunction(42.0));
        REQUIRE(!o2.conjunction(std::string{"hello"}));
    }

    SECTION("map_or")
    {
        phi::Optional<int> o1 = 21;
        REQUIRE((o1.map_or([](int x) { return x * 2; }, 13)) == 42);

        phi::Optional<int> o2;
        REQUIRE((o2.map_or([](int x) { return x * 2; }, 13)) == 13);
    }

    SECTION("map_or_else")
    {
        phi::Optional<int> o1 = 21;
        REQUIRE((o1.map_or_else([](int x) { return x * 2; }, [] { return 13; })) == 42);

        phi::Optional<int> o2;
        REQUIRE((o2.map_or_else([](int x) { return x * 2; }, [] { return 13; })) == 13);
    }

    SECTION("take")
    {
        phi::Optional<int> o1 = 42;
        REQUIRE(*o1.take() == 42);
        REQUIRE(!o1);

        phi::Optional<int> o2;
        REQUIRE(!o2.take());
        REQUIRE(!o2);
    }

    struct foo
    {
        void non_const()
        {}
    };

    SECTION("Issue #1")
    {
        phi::Optional<foo> f = foo{};
        auto               l = [](auto&& x) { x.non_const(); };
        f.map(l);
    }

    struct overloaded
    {
        phi::Optional<int> operator()(foo&)
        {
            return 0;
        }
        phi::Optional<std::string> operator()(const foo&)
        {
            return "";
        }
    };

    SECTION("Issue #2")
    {
        phi::Optional<foo> f = foo{};
        auto               x = f.and_then(overloaded{});
    }
}

struct takes_init_and_variadic
{
    std::vector<int>     v;
    std::tuple<int, int> t;
    template <class... Args>
    takes_init_and_variadic(std::initializer_list<int> l, Args&&... args)
        : v(l)
        , t(std::forward<Args>(args)...)
    {}
};

TEST_CASE("In place", "[in_place]")
{
    phi::Optional<int> o1{phi::in_place};
    phi::Optional<int> o2(phi::in_place);
    REQUIRE(o1);
    REQUIRE(o1 == 0);
    REQUIRE(o2);
    REQUIRE(o2 == 0);

    phi::Optional<int> o3(phi::in_place, 42);
    REQUIRE(o3 == 42);

    phi::Optional<std::tuple<int, int>> o4(phi::in_place, 0, 1);
    REQUIRE(o4);
    REQUIRE(std::get<0>(*o4) == 0);
    REQUIRE(std::get<1>(*o4) == 1);

    phi::Optional<std::vector<int>> o5(phi::in_place, {0, 1});
    REQUIRE(o5);
    REQUIRE((*o5)[0] == 0);
    REQUIRE((*o5)[1] == 1);

    phi::Optional<takes_init_and_variadic> o6(phi::in_place, {0, 1}, 2, 3);
    REQUIRE(o6->v[0] == 0);
    REQUIRE(o6->v[1] == 1);
    REQUIRE(std::get<0>(o6->t) == 2);
    REQUIRE(std::get<1>(o6->t) == 3);
}

struct bar
{
    int& v()
    {
        return i;
    }
    int i = 0;
};

int& x(int& i)
{
    i = 42;
    return i;
}

TEST_CASE("issue 14")
{
    phi::Optional<bar> f = bar{};
    auto               v = f.map(&bar::v).map(x);
    static_assert(std::is_same<decltype(v), phi::Optional<int&>>::value, "Must return a reference");
    REQUIRE(f->i == 42);
    REQUIRE(*v == 42);
    REQUIRE((&f->i) == (&*v));
}

struct fail_on_copy_self
{
    int value;
    fail_on_copy_self(int v)
        : value(v)
    {}
    fail_on_copy_self(const fail_on_copy_self& other)
        : value(other.value)
    {
        REQUIRE(&other != this);
    }
};

TEST_CASE("issue 15")
{
    phi::Optional<fail_on_copy_self> o = fail_on_copy_self(42);

    o = o;
    REQUIRE(o->value == 42);
}

TEST_CASE("issue 33")
{
    int                 i = 0;
    int                 j = 0;
    phi::Optional<int&> a = i;
    a.emplace(j);
    *a = 42;
    REQUIRE(j == 42);
    REQUIRE(*a == 42);
    REQUIRE(a.has_value());
}

TEST_CASE("Make optional", "[make_optional]")
{
    auto o1 = phi::make_optional(42);
    auto o2 = phi::Optional<int>(42);

    constexpr bool is_same = std::is_same<decltype(o1), phi::Optional<int>>::value;
    REQUIRE(is_same);
    REQUIRE(o1 == o2);

    auto o3 = phi::make_optional<std::tuple<int, int, int, int>>(0, 1, 2, 3);
    REQUIRE(std::get<0>(*o3) == 0);
    REQUIRE(std::get<1>(*o3) == 1);
    REQUIRE(std::get<2>(*o3) == 2);
    REQUIRE(std::get<3>(*o3) == 3);

    auto o4 = phi::make_optional<std::vector<int>>({0, 1, 2, 3});
    REQUIRE(o4.value()[0] == 0);
    REQUIRE(o4.value()[1] == 1);
    REQUIRE(o4.value()[2] == 2);
    REQUIRE(o4.value()[3] == 3);

    auto o5 = phi::make_optional<takes_init_and_variadic>({0, 1}, 2, 3);
    REQUIRE(o5->v[0] == 0);
    REQUIRE(o5->v[1] == 1);
    REQUIRE(std::get<0>(o5->t) == 2);
    REQUIRE(std::get<1>(o5->t) == 3);

    auto i  = 42;
    auto o6 = phi::make_optional<int&>(i);
    REQUIRE((std::is_same<decltype(o6), phi::Optional<int&>>::value));
    REQUIRE(o6);
    REQUIRE(*o6 == 42);
}

TEST_CASE("Noexcept", "[noexcept]")
{
    phi::Optional<int> o1{4};
    phi::Optional<int> o2{42};

    SECTION("comparison with nullopt")
    {
        REQUIRE(noexcept(o1 == phi::nullopt));
        REQUIRE(noexcept(phi::nullopt == o1));
        REQUIRE(noexcept(o1 != phi::nullopt));
        REQUIRE(noexcept(phi::nullopt != o1));
        REQUIRE(noexcept(o1 < phi::nullopt));
        REQUIRE(noexcept(phi::nullopt < o1));
        REQUIRE(noexcept(o1 <= phi::nullopt));
        REQUIRE(noexcept(phi::nullopt <= o1));
        REQUIRE(noexcept(o1 > phi::nullopt));
        REQUIRE(noexcept(phi::nullopt > o1));
        REQUIRE(noexcept(o1 >= phi::nullopt));
        REQUIRE(noexcept(phi::nullopt >= o1));
    }

    SECTION("swap")
    {
        //TODO see why this fails
#if !defined(_MSC_VER) || _MSC_VER > 1900
        REQUIRE(noexcept(swap(o1, o2)) == noexcept(o1.swap(o2)));

        struct nothrow_swappable
        {
            nothrow_swappable& swap(const nothrow_swappable&) noexcept
            {
                return *this;
            }
        };

        struct throw_swappable
        {
            throw_swappable() = default;
            throw_swappable(const throw_swappable&)
            {}
            throw_swappable(throw_swappable&&)
            {}
            throw_swappable& swap(const throw_swappable&)
            {
                return *this;
            }
        };

        phi::Optional<nothrow_swappable> ont;
        phi::Optional<throw_swappable>   ot;

        REQUIRE(noexcept(ont.swap(ont)));
        REQUIRE(!noexcept(ot.swap(ot)));
#endif
    }

    SECTION("constructors")
    {
        //TODO see why this fails
#if !defined(_MSC_VER) || _MSC_VER > 1900
        REQUIRE(noexcept(phi::Optional<int>{}));
        REQUIRE(noexcept(phi::Optional<int>{phi::nullopt}));

        struct nothrow_move
        {
            nothrow_move(nothrow_move&&) noexcept = default;
        };

        struct throw_move
        {
            throw_move(throw_move&&)
            {}
        };

        using nothrow_opt = phi::Optional<nothrow_move>;
        using throw_opt   = phi::Optional<throw_move>;

        REQUIRE(std::is_nothrow_move_constructible<nothrow_opt>::value);
        REQUIRE(!std::is_nothrow_move_constructible<throw_opt>::value);
#endif
    }

    SECTION("assignment")
    {
        REQUIRE(noexcept(o1 = phi::nullopt));

        struct nothrow_move_assign
        {
            nothrow_move_assign()                               = default;
            nothrow_move_assign(nothrow_move_assign&&) noexcept = default;
            nothrow_move_assign& operator=(const nothrow_move_assign&) = default;
        };

        struct throw_move_assign
        {
            throw_move_assign() = default;
            throw_move_assign(throw_move_assign&&)
            {}
            throw_move_assign& operator=(const throw_move_assign&)
            {
                return *this;
            }
        };

        using nothrow_opt = phi::Optional<nothrow_move_assign>;
        using throw_opt   = phi::Optional<throw_move_assign>;

        REQUIRE(noexcept(std::declval<nothrow_opt>() = std::declval<nothrow_opt>()));
        REQUIRE(!noexcept(std::declval<throw_opt>() = std::declval<throw_opt>()));
    }

    SECTION("observers")
    {
        REQUIRE(noexcept(static_cast<bool>(o1)));
        REQUIRE(noexcept(o1.has_value()));
    }

    SECTION("modifiers")
    {
        REQUIRE(noexcept(o1.reset()));
    }
}

TEST_CASE("Nullopt", "[nullopt]")
{
    phi::Optional<int> o1 = phi::nullopt;
    phi::Optional<int> o2{phi::nullopt};
    phi::Optional<int> o3(phi::nullopt);
    phi::Optional<int> o4 = {phi::nullopt};

    REQUIRE(!o1);
    REQUIRE(!o2);
    REQUIRE(!o3);
    REQUIRE(!o4);

    REQUIRE(!std::is_default_constructible<phi::nullopt_t>::value);
}

struct move_detector
{
    move_detector() = default;
    move_detector(move_detector&& rhs)
    {
        rhs.been_moved = true;
    }
    bool been_moved = false;
};

TEST_CASE("Observers", "[observers]")
{
    phi::Optional<int>       o1 = 42;
    phi::Optional<int>       o2;
    const phi::Optional<int> o3 = 42;

    REQUIRE(*o1 == 42);
    REQUIRE(*o1 == o1.value());
    REQUIRE(o2.value_or(42) == 42);
    REQUIRE(o3.value() == 42);
    auto success = std::is_same<decltype(o1.value()), int&>::value;
    REQUIRE(success);
    success = std::is_same<decltype(o3.value()), const int&>::value;
    REQUIRE(success);
    success = std::is_same<decltype(std::move(o1).value()), int&&>::value;
    REQUIRE(success);

#ifndef TL_OPTIONAL_NO_CONSTRR
    success = std::is_same<decltype(std::move(o3).value()), const int&&>::value;
    REQUIRE(success);
#endif

    phi::Optional<move_detector> o4{phi::in_place};
    move_detector                o5 = std::move(o4).value();
    REQUIRE(o4->been_moved);
    REQUIRE(!o5.been_moved);
}

TEST_CASE("Relational ops", "[relops]")
{
    phi::Optional<int> o1{4};
    phi::Optional<int> o2{42};
    phi::Optional<int> o3{};

    SECTION("self simple")
    {
        REQUIRE(!(o1 == o2));
        REQUIRE(o1 == o1);
        REQUIRE(o1 != o2);
        REQUIRE(!(o1 != o1));
        REQUIRE(o1 < o2);
        REQUIRE(!(o1 < o1));
        REQUIRE(!(o1 > o2));
        REQUIRE(!(o1 > o1));
        REQUIRE(o1 <= o2);
        REQUIRE(o1 <= o1);
        REQUIRE(!(o1 >= o2));
        REQUIRE(o1 >= o1);
    }

    SECTION("nullopt simple")
    {
        REQUIRE(!(o1 == phi::nullopt));
        REQUIRE(!(phi::nullopt == o1));
        REQUIRE(o1 != phi::nullopt);
        REQUIRE(phi::nullopt != o1);
        REQUIRE(!(o1 < phi::nullopt));
        REQUIRE(phi::nullopt < o1);
        REQUIRE(o1 > phi::nullopt);
        REQUIRE(!(phi::nullopt > o1));
        REQUIRE(!(o1 <= phi::nullopt));
        REQUIRE(phi::nullopt <= o1);
        REQUIRE(o1 >= phi::nullopt);
        REQUIRE(!(phi::nullopt >= o1));

        REQUIRE(o3 == phi::nullopt);
        REQUIRE(phi::nullopt == o3);
        REQUIRE(!(o3 != phi::nullopt));
        REQUIRE(!(phi::nullopt != o3));
        REQUIRE(!(o3 < phi::nullopt));
        REQUIRE(!(phi::nullopt < o3));
        REQUIRE(!(o3 > phi::nullopt));
        REQUIRE(!(phi::nullopt > o3));
        REQUIRE(o3 <= phi::nullopt);
        REQUIRE(phi::nullopt <= o3);
        REQUIRE(o3 >= phi::nullopt);
        REQUIRE(phi::nullopt >= o3);
    }

    SECTION("with T simple")
    {
        REQUIRE(!(o1 == 1));
        REQUIRE(!(1 == o1));
        REQUIRE(o1 != 1);
        REQUIRE(1 != o1);
        REQUIRE(!(o1 < 1));
        REQUIRE(1 < o1);
        REQUIRE(o1 > 1);
        REQUIRE(!(1 > o1));
        REQUIRE(!(o1 <= 1));
        REQUIRE(1 <= o1);
        REQUIRE(o1 >= 1);
        REQUIRE(!(1 >= o1));

        REQUIRE(o1 == 4);
        REQUIRE(4 == o1);
        REQUIRE(!(o1 != 4));
        REQUIRE(!(4 != o1));
        REQUIRE(!(o1 < 4));
        REQUIRE(!(4 < o1));
        REQUIRE(!(o1 > 4));
        REQUIRE(!(4 > o1));
        REQUIRE(o1 <= 4);
        REQUIRE(4 <= o1);
        REQUIRE(o1 >= 4);
        REQUIRE(4 >= o1);
    }

    phi::Optional<std::string> o4{"hello"};
    phi::Optional<std::string> o5{"xyz"};

    SECTION("self complex")
    {
        REQUIRE(!(o4 == o5));
        REQUIRE(o4 == o4);
        REQUIRE(o4 != o5);
        REQUIRE(!(o4 != o4));
        REQUIRE(o4 < o5);
        REQUIRE(!(o4 < o4));
        REQUIRE(!(o4 > o5));
        REQUIRE(!(o4 > o4));
        REQUIRE(o4 <= o5);
        REQUIRE(o4 <= o4);
        REQUIRE(!(o4 >= o5));
        REQUIRE(o4 >= o4);
    }

    SECTION("nullopt complex")
    {
        REQUIRE(!(o4 == phi::nullopt));
        REQUIRE(!(phi::nullopt == o4));
        REQUIRE(o4 != phi::nullopt);
        REQUIRE(phi::nullopt != o4);
        REQUIRE(!(o4 < phi::nullopt));
        REQUIRE(phi::nullopt < o4);
        REQUIRE(o4 > phi::nullopt);
        REQUIRE(!(phi::nullopt > o4));
        REQUIRE(!(o4 <= phi::nullopt));
        REQUIRE(phi::nullopt <= o4);
        REQUIRE(o4 >= phi::nullopt);
        REQUIRE(!(phi::nullopt >= o4));

        REQUIRE(o3 == phi::nullopt);
        REQUIRE(phi::nullopt == o3);
        REQUIRE(!(o3 != phi::nullopt));
        REQUIRE(!(phi::nullopt != o3));
        REQUIRE(!(o3 < phi::nullopt));
        REQUIRE(!(phi::nullopt < o3));
        REQUIRE(!(o3 > phi::nullopt));
        REQUIRE(!(phi::nullopt > o3));
        REQUIRE(o3 <= phi::nullopt);
        REQUIRE(phi::nullopt <= o3);
        REQUIRE(o3 >= phi::nullopt);
        REQUIRE(phi::nullopt >= o3);
    }

    SECTION("with T complex")
    {
        REQUIRE(!(o4 == "a"));
        REQUIRE(!("a" == o4));
        REQUIRE(o4 != "a");
        REQUIRE("a" != o4);
        REQUIRE(!(o4 < "a"));
        REQUIRE("a" < o4);
        REQUIRE(o4 > "a");
        REQUIRE(!("a" > o4));
        REQUIRE(!(o4 <= "a"));
        REQUIRE("a" <= o4);
        REQUIRE(o4 >= "a");
        REQUIRE(!("a" >= o4));

        REQUIRE(o4 == "hello");
        REQUIRE("hello" == o4);
        REQUIRE(!(o4 != "hello"));
        REQUIRE(!("hello" != o4));
        REQUIRE(!(o4 < "hello"));
        REQUIRE(!("hello" < o4));
        REQUIRE(!(o4 > "hello"));
        REQUIRE(!("hello" > o4));
        REQUIRE(o4 <= "hello");
        REQUIRE("hello" <= o4);
        REQUIRE(o4 >= "hello");
        REQUIRE("hello" >= o4);
    }
}

TEST_CASE("Swap value", "[swap.value]")
{
    phi::Optional<int> o1 = 42;
    phi::Optional<int> o2 = 12;
    o1.swap(o2);
    CHECK(o1.value() == 12);
    CHECK(o2.value() == 42);
}

TEST_CASE("Swap value with null intialized", "[swap.value_nullopt]")
{
    phi::Optional<int> o1 = 42;
    phi::Optional<int> o2 = phi::nullopt;
    o1.swap(o2);
    CHECK(!o1.has_value());
    CHECK(o2.value() == 42);
}

TEST_CASE("Swap null intialized with value", "[swap.nullopt_value]")
{
    phi::Optional<int> o1 = phi::nullopt;
    phi::Optional<int> o2 = 42;
    o1.swap(o2);
    CHECK(o1.value() == 42);
    CHECK(!o2.has_value());
}
