#include <phi/test/test_macros.hpp>

#include <phi/type_traits/bool_constant.hpp>
#include <phi/type_traits/integral_constant.hpp>

#if PHI_HAS_FEATURE_ALIAS_TEMPLATES()

TEST_CASE("type_traits.bool_constant")
{
    using my_true_type  = phi::bool_constant<true>;
    using my_false_type = phi::bool_constant<false>;

    STATIC_REQUIRE(my_true_type::value == true);
    CHECK_SAME_TYPE(my_true_type, phi::true_type);
    CHECK_SAME_TYPE(my_true_type, phi::bool_constant<true>);
    CHECK_SAME_TYPE(my_true_type, phi::integral_constant<bool, true>);
    CHECK_SAME_TYPE(my_true_type::type, my_true_type);
    CHECK_SAME_TYPE(my_true_type::type, phi::true_type);
    CHECK_SAME_TYPE(my_true_type::type, phi::bool_constant<true>);
    CHECK_SAME_TYPE(my_true_type::type, phi::integral_constant<bool, true>);
    CHECK_SAME_TYPE(my_true_type::this_type, my_true_type);
    CHECK_SAME_TYPE(my_true_type::this_type, phi::true_type);
    CHECK_SAME_TYPE(my_true_type::this_type, phi::bool_constant<true>);
    CHECK_SAME_TYPE(my_true_type::this_type, phi::integral_constant<bool, true>);
    CHECK_SAME_TYPE(my_true_type::value_type, bool);
    STATIC_REQUIRE(my_true_type() == true);
    CHECK_NOEXCEPT(my_true_type());
    STATIC_REQUIRE(my_true_type::value != false);
    STATIC_REQUIRE(my_true_type{}());
    STATIC_REQUIRE(static_cast<bool>(my_true_type{}));

    STATIC_REQUIRE(my_false_type::value == false);
    CHECK_SAME_TYPE(my_false_type, phi::false_type);
    CHECK_SAME_TYPE(my_false_type, phi::bool_constant<false>);
    CHECK_SAME_TYPE(my_false_type, phi::integral_constant<bool, false>);
    CHECK_SAME_TYPE(my_false_type::type, my_false_type);
    CHECK_SAME_TYPE(my_false_type::type, phi::false_type);
    CHECK_SAME_TYPE(my_false_type::type, phi::bool_constant<false>);
    CHECK_SAME_TYPE(my_false_type::type, phi::integral_constant<bool, false>);
    CHECK_SAME_TYPE(my_false_type::this_type, my_false_type);
    CHECK_SAME_TYPE(my_false_type::this_type, phi::false_type);
    CHECK_SAME_TYPE(my_false_type::this_type, phi::bool_constant<false>);
    CHECK_SAME_TYPE(my_false_type::this_type, phi::integral_constant<bool, false>);
    CHECK_SAME_TYPE(my_false_type::value_type, bool);
    STATIC_REQUIRE(my_false_type() == false);
    CHECK_NOEXCEPT(my_false_type());
    STATIC_REQUIRE(my_false_type::value != true);
    STATIC_REQUIRE(my_false_type{}() == false);
    STATIC_REQUIRE_FALSE(static_cast<bool>(my_false_type{}));
}

#endif
