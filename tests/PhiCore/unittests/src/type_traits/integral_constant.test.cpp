#include <phi/test/test_macros.hpp>

#include <phi/type_traits/integral_constant.hpp>

enum class MyEnum
{
    Value1 = 0,
    Value2
};

TEST_CASE("type_traits.integral_constant")
{
    using two_t = phi::integral_constant<int, 2>;

    STATIC_REQUIRE(two_t::value == 2);
    STATIC_REQUIRE(two_t() == 2);
    CHECK_SAME_TYPE(two_t::value_type, int);
    CHECK_SAME_TYPE(two_t::type, two_t);
    CHECK_SAME_TYPE(two_t::type, phi::integral_constant<int, 2>);
    CHECK_SAME_TYPE(two_t::this_type, two_t);
    CHECK_SAME_TYPE(two_t::this_type, phi::integral_constant<int, 2>);
    CHECK_NOEXCEPT(two_t());
    STATIC_REQUIRE(two_t{}() == 2);

    constexpr two_t two = two_t{};
    STATIC_REQUIRE(two == 2);
    STATIC_REQUIRE(two() == 2);
    CHECK_NOEXCEPT(two());
    STATIC_REQUIRE(static_cast<int>(two) == 2);

    using four_t = phi::integral_constant<int, 4>;

    STATIC_REQUIRE(four_t::value == 4);
    STATIC_REQUIRE(four_t() == 4);
    CHECK_SAME_TYPE(four_t::value_type, int);
    CHECK_SAME_TYPE(four_t::type, four_t);
    CHECK_SAME_TYPE(four_t::type, phi::integral_constant<int, 4>);
    CHECK_SAME_TYPE(four_t::this_type, four_t);
    CHECK_SAME_TYPE(four_t::this_type, phi::integral_constant<int, 4>);
    CHECK_NOEXCEPT(four_t());
    STATIC_REQUIRE(four_t{}() == 4);

    constexpr four_t four = four_t{};
    STATIC_REQUIRE(four == 4);
    STATIC_REQUIRE(four() == 4);
    CHECK_NOEXCEPT(four());
    STATIC_REQUIRE(static_cast<int>(four) == 4);

    CHECK_NOT_SAME_TYPE(two_t, four_t);
    STATIC_REQUIRE((two_t::value * 2) == four_t::value);

    using val1 = phi::integral_constant<MyEnum, MyEnum::Value1>;
    using val2 = phi::integral_constant<MyEnum, MyEnum::Value2>;

    STATIC_REQUIRE(val1::value != val2::value);
    CHECK_NOT_SAME_TYPE(val1, val2);
}

TEST_CASE("type_traits.true_type")
{
    STATIC_REQUIRE(phi::true_type::value == true);
    CHECK_SAME_TYPE(phi::true_type::type, phi::true_type);
    CHECK_SAME_TYPE(phi::true_type::type, phi::bool_constant<true>);
    CHECK_SAME_TYPE(phi::true_type::type, phi::integral_constant<bool, true>);
    CHECK_SAME_TYPE(phi::true_type::this_type, phi::true_type);
    CHECK_SAME_TYPE(phi::true_type::this_type, phi::bool_constant<true>);
    CHECK_SAME_TYPE(phi::true_type::this_type, phi::integral_constant<bool, true>);
    CHECK_SAME_TYPE(phi::true_type::value_type, bool);
    STATIC_REQUIRE(phi::true_type() == true);
    CHECK_NOEXCEPT(phi::true_type());
    STATIC_REQUIRE(phi::true_type{}());

    STATIC_REQUIRE(phi::true_type::value != false);

    constexpr phi::true_type true1;
    constexpr phi::true_type true2 = true1;
    STATIC_REQUIRE(true1);
    STATIC_REQUIRE(true2);
    STATIC_REQUIRE(static_cast<bool>(true1));
    STATIC_REQUIRE(static_cast<bool>(true2));
}

TEST_CASE("type_traits.false_type")
{
    STATIC_REQUIRE(phi::false_type::value == false);
    CHECK_SAME_TYPE(phi::false_type::type, phi::false_type);
    CHECK_SAME_TYPE(phi::false_type::type, phi::bool_constant<false>);
    CHECK_SAME_TYPE(phi::false_type::type, phi::integral_constant<bool, false>);
    CHECK_SAME_TYPE(phi::false_type::this_type, phi::false_type);
    CHECK_SAME_TYPE(phi::false_type::this_type, phi::bool_constant<false>);
    CHECK_SAME_TYPE(phi::false_type::this_type, phi::integral_constant<bool, false>);
    CHECK_SAME_TYPE(phi::false_type::value_type, bool);
    STATIC_REQUIRE(phi::false_type() == false);
    CHECK_NOEXCEPT(phi::false_type());
    STATIC_REQUIRE_FALSE(phi::false_type{}());

    STATIC_REQUIRE(phi::false_type::value != true);

    constexpr phi::false_type false1;
    constexpr phi::false_type false2 = false1;
    STATIC_REQUIRE_FALSE(false1);
    STATIC_REQUIRE_FALSE(false2);
    STATIC_REQUIRE_FALSE(static_cast<bool>(false1));
    STATIC_REQUIRE_FALSE(static_cast<bool>(false2));
}
