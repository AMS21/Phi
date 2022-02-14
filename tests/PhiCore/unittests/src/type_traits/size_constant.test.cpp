#include "phi/core/size_t.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include <phi/test/test_macros.hpp>

#include <phi/type_traits/size_constant.hpp>

TEST_CASE("type_traits.size_constant")
{
    using size0_type = phi::size_constant<0u>;
    using size1_type = phi::size_constant<1u>;

    CHECK_NOT_SAME_TYPE(size0_type, size1_type);

    STATIC_REQUIRE(size0_type::value == 0u);
    CHECK_SAME_TYPE(size0_type::type, phi::size_constant<0u>);
    CHECK_SAME_TYPE(size0_type::type, phi::integral_constant<phi::size_t, 0u>);
    CHECK_SAME_TYPE(size0_type::this_type, phi::size_constant<0u>);
    CHECK_SAME_TYPE(size0_type::this_type, phi::integral_constant<phi::size_t, 0u>);
    CHECK_SAME_TYPE(size0_type::value_type, phi::size_t);
    STATIC_REQUIRE(size0_type() == 0u);
    CHECK_NOEXCEPT(size0_type());

    STATIC_REQUIRE(size1_type::value == 1u);
    CHECK_SAME_TYPE(size1_type::type, phi::size_constant<1u>);
    CHECK_SAME_TYPE(size1_type::type, phi::integral_constant<phi::size_t, 1u>);
    CHECK_SAME_TYPE(size1_type::this_type, phi::size_constant<1u>);
    CHECK_SAME_TYPE(size1_type::this_type, phi::integral_constant<phi::size_t, 1u>);
    CHECK_SAME_TYPE(size1_type::value_type, phi::size_t);
    STATIC_REQUIRE(size1_type() == 1u);
    CHECK_NOEXCEPT(size1_type());
}
