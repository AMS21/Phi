#include <catch2/catch_test_macros.hpp>

#include "ConstexprHelper.hpp"
#include "Noexcept.hpp"
#include <Phi/TypeTraits/integral_constant.hpp>
#include <Phi/TypeTraits/is_same.hpp>

enum class MyEnum
{
    Value1 = 0,
    Value2
};

TEST_CASE("integral_constant")
{
    using two_t = phi::integral_constant<int, 2>;

    STATIC_REQUIRE(two_t::value == 2);
    STATIC_REQUIRE(two_t() == 2);
    STATIC_REQUIRE(phi::is_same_v<two_t::value_type, int>);
    STATIC_REQUIRE(phi::is_same_v<two_t::type, two_t>);
    STATIC_REQUIRE(phi::is_same_v<two_t::this_type, two_t>);
    CHECK_NOEXCEPT(two_t());

    using four_t = phi::integral_constant<int, 4>;

    STATIC_REQUIRE(four_t::value == 4);
    STATIC_REQUIRE(four_t() == 4);
    STATIC_REQUIRE(phi::is_same_v<four_t::value_type, int>);
    STATIC_REQUIRE(phi::is_same_v<four_t::type, four_t>);
    STATIC_REQUIRE(phi::is_same_v<four_t::this_type, four_t>);
    CHECK_NOEXCEPT(four_t());

    STATIC_REQUIRE_FALSE(phi::is_same_v<two_t, four_t>);
    STATIC_REQUIRE((two_t::value * 2) == four_t::value);

    using val1 = phi::integral_constant<MyEnum, MyEnum::Value1>;
    using val2 = phi::integral_constant<MyEnum, MyEnum::Value2>;

    STATIC_REQUIRE(val1::value != val2::value);
    STATIC_REQUIRE(phi::is_same_v<val2, val2>);
}

TEST_CASE("type_traits.bool_constant")
{
    using my_true_type  = phi::bool_constant<true>;
    using my_false_type = phi::bool_constant<false>;

    STATIC_REQUIRE(my_true_type::value == true);
    STATIC_REQUIRE(phi::is_same_v<my_true_type::type, my_true_type>);
    STATIC_REQUIRE(phi::is_same_v<my_true_type::this_type, my_true_type>);
    STATIC_REQUIRE(phi::is_same_v<my_true_type::value_type, bool>);
    STATIC_REQUIRE(my_true_type() == true);
    STATIC_REQUIRE(my_true_type::value != false);

    STATIC_REQUIRE(my_false_type::value == false);
    STATIC_REQUIRE(phi::is_same_v<my_false_type::type, my_false_type>);
    STATIC_REQUIRE(phi::is_same_v<my_false_type::this_type, my_false_type>);
    STATIC_REQUIRE(phi::is_same_v<my_false_type::value_type, bool>);
    STATIC_REQUIRE(my_false_type() == false);
    STATIC_REQUIRE(my_false_type::value != true);
}

TEST_CASE("type_traits.true_type")
{
    STATIC_REQUIRE(phi::true_type::value == true);
    STATIC_REQUIRE(phi::is_same_v<phi::true_type::type, phi::true_type>);
    STATIC_REQUIRE(phi::is_same_v<phi::true_type::this_type, phi::true_type>);
    STATIC_REQUIRE(phi::is_same_v<phi::true_type::value_type, bool>);
    STATIC_REQUIRE(phi::true_type() == true);

    STATIC_REQUIRE(phi::true_type::value != false);

    CONSTEXPR_RUNTIME phi::true_type t1;
    CONSTEXPR_RUNTIME phi::true_type t2 = t1;
    STATIC_REQUIRE(t1);
    STATIC_REQUIRE(t2);
}

TEST_CASE("type_traits.false_type")
{
    STATIC_REQUIRE(phi::false_type::value == false);
    STATIC_REQUIRE(phi::is_same_v<phi::false_type::type, phi::false_type>);
    STATIC_REQUIRE(phi::is_same_v<phi::false_type::this_type, phi::false_type>);
    STATIC_REQUIRE(phi::is_same_v<phi::false_type::value_type, bool>);
    STATIC_REQUIRE(phi::false_type() == false);

    STATIC_REQUIRE(phi::false_type::value != true);

    CONSTEXPR_RUNTIME phi::false_type f1;
    CONSTEXPR_RUNTIME phi::false_type f2 = f1;
    STATIC_REQUIRE_FALSE(f1);
    STATIC_REQUIRE_FALSE(f2);
}
