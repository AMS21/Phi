#include <phi/test/test_macros.hpp>

#include <phi/type_traits/detail/yes_no_type.hpp>

TEST_CASE("yes no type")
{
    STATIC_REQUIRE(sizeof(phi::detail::yes_type) == 1);
    STATIC_REQUIRE(sizeof(phi::detail::no_type) == 8);

    STATIC_REQUIRE(sizeof(phi::detail::yes_type) == phi::detail::sizeof_yes_type);
    STATIC_REQUIRE(sizeof(phi::detail::no_type) == phi::detail::sizeof_no_type);

    STATIC_REQUIRE(phi::detail::sizeof_yes_type != phi::detail::sizeof_no_type);
    STATIC_REQUIRE(sizeof(phi::detail::yes_type) != sizeof(phi::detail::no_type));
    CHECK_NOT_SAME_TYPE(phi::detail::yes_type, phi::detail::no_type);
}
