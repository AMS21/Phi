#include <phi/test/test_macros.hpp>

#include <phi/core/size_t.hpp>
#include <phi/core/sized_types.hpp>
#include <phi/type_traits/signed_int_of_size.hpp>

template <phi::size_t Size, typename TypeT>
void test_signed_int_of_size()
{
    CHECK_SAME_TYPE(typename phi::signed_int_of_size<Size>::type, TypeT);
    CHECK_SAME_TYPE(phi::signed_int_of_size_t<Size>, TypeT);

    STATIC_REQUIRE(sizeof(typename phi::signed_int_of_size<Size>::type) == Size);
    STATIC_REQUIRE(sizeof(phi::signed_int_of_size_t<Size>) == Size);
}

TEST_CASE("signed_int_of_size")
{
    test_signed_int_of_size<1, phi::int8_t>();
    test_signed_int_of_size<2, phi::int16_t>();
    test_signed_int_of_size<4, phi::int32_t>();
    test_signed_int_of_size<8, phi::int64_t>();
}
