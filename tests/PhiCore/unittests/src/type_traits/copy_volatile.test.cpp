#include <phi/test/test_macros.hpp>

#include <phi/type_traits/copy_volatile.hpp>
#include <phi/type_traits/is_same.hpp>

TEST_CASE("copy_volatile")
{
    CHECK_SAME_TYPE(typename phi::copy_volatile<int, float>::type, float);
    CHECK_SAME_TYPE(typename phi::copy_volatile<volatile int, float>::type, volatile float);
    CHECK_SAME_TYPE(typename phi::copy_volatile<int, volatile float>::type, volatile float);
    CHECK_SAME_TYPE(typename phi::copy_volatile<volatile int, volatile float>::type,
                    volatile float);

    CHECK_SAME_TYPE(typename phi::copy_volatile<int, const float>::type, const float);
    CHECK_SAME_TYPE(typename phi::copy_volatile<const int, float>::type, float);
    CHECK_SAME_TYPE(typename phi::copy_volatile<const int, const float>::type, const float);

    CHECK_SAME_TYPE(typename phi::copy_volatile<const volatile int, float>::type, volatile float);
    CHECK_SAME_TYPE(typename phi::copy_volatile<int, const volatile float>::type,
                    const volatile float);
    CHECK_SAME_TYPE(typename phi::copy_volatile<const volatile int, const volatile float>::type,
                    const volatile float);

    CHECK_SAME_TYPE(typename phi::copy_volatile<volatile int, const float>::type,
                    const volatile float);
}

TEST_CASE("copy_volatile_t")
{
    CHECK_SAME_TYPE(typename phi::copy_volatile_t<int, float>, float);
    CHECK_SAME_TYPE(typename phi::copy_volatile_t<volatile int, float>, volatile float);
    CHECK_SAME_TYPE(typename phi::copy_volatile_t<int, volatile float>, volatile float);
    CHECK_SAME_TYPE(typename phi::copy_volatile_t<volatile int, volatile float>, volatile float);

    CHECK_SAME_TYPE(typename phi::copy_volatile_t<int, const float>, const float);
    CHECK_SAME_TYPE(typename phi::copy_volatile_t<const int, float>, float);
    CHECK_SAME_TYPE(typename phi::copy_volatile_t<const int, const float>, const float);

    CHECK_SAME_TYPE(typename phi::copy_volatile_t<const volatile int, float>, volatile float);
    CHECK_SAME_TYPE(typename phi::copy_volatile_t<int, const volatile float>, const volatile float);
    CHECK_SAME_TYPE(typename phi::copy_volatile_t<const volatile int, const volatile float>,
                    const volatile float);

    CHECK_SAME_TYPE(typename phi::copy_volatile_t<volatile int, const float>, const volatile float);
}
