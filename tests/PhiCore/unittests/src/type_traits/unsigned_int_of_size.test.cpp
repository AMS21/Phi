#include <phi/test/test_macros.hpp>

#include <phi/core/size_t.hpp>
#include <phi/core/sized_types.hpp>
#include <phi/type_traits/unsigned_int_of_size.hpp>

template <phi::size_t Size, typename T>
void test_unsigned_int_of_size()
{
    CHECK_SAME_TYPE(typename phi::unsigned_int_of_size<Size>::type, T);
    CHECK_SAME_TYPE(phi::unsigned_int_of_size_t<Size>, T);
}

TEST_CASE("signed_int_of_size")
{
    test_unsigned_int_of_size<1, phi::uint8_t>();
    test_unsigned_int_of_size<2, phi::uint16_t>();
    test_unsigned_int_of_size<4, phi::uint32_t>();
    test_unsigned_int_of_size<8, phi::uint64_t>();
}
