#include <Phi/Test/TestMacros.hpp>

#include <Phi/TypeTraits/copy_const.hpp>

TEST_CASE("copy_const")
{
    CHECK_SAME_TYPE(typename phi::copy_const<int, float>::type, float);
    CHECK_SAME_TYPE(typename phi::copy_const<volatile int, float>::type, float);
    CHECK_SAME_TYPE(typename phi::copy_const<int, volatile float>::type, volatile float);
    CHECK_SAME_TYPE(typename phi::copy_const<volatile int, volatile float>::type, volatile float);

    CHECK_SAME_TYPE(typename phi::copy_const<int, const float>::type, const float);
    CHECK_SAME_TYPE(typename phi::copy_const<const int, float>::type, const float);
    CHECK_SAME_TYPE(typename phi::copy_const<const int, const float>::type, const float);

    CHECK_SAME_TYPE(typename phi::copy_const<const volatile int, float>::type, const float);
    CHECK_SAME_TYPE(typename phi::copy_const<int, const volatile float>::type,
                    const volatile float);
    CHECK_SAME_TYPE(typename phi::copy_const<const volatile int, const volatile float>::type,
                    const volatile float);

    CHECK_SAME_TYPE(typename phi::copy_const<const int, volatile float>::type,
                    const volatile float);

    CHECK_SAME_TYPE(typename phi::copy_const_t<int, float>, float);
    CHECK_SAME_TYPE(typename phi::copy_const_t<volatile int, float>, float);
    CHECK_SAME_TYPE(typename phi::copy_const_t<int, volatile float>, volatile float);
    CHECK_SAME_TYPE(typename phi::copy_const_t<volatile int, volatile float>, volatile float);

    CHECK_SAME_TYPE(typename phi::copy_const_t<int, const float>, const float);
    CHECK_SAME_TYPE(typename phi::copy_const_t<const int, float>, const float);
    CHECK_SAME_TYPE(typename phi::copy_const_t<const int, const float>, const float);

    CHECK_SAME_TYPE(typename phi::copy_const_t<const volatile int, float>, const float);
    CHECK_SAME_TYPE(typename phi::copy_const_t<int, const volatile float>, const volatile float);
    CHECK_SAME_TYPE(typename phi::copy_const_t<const volatile int, const volatile float>,
                    const volatile float);

    CHECK_SAME_TYPE(typename phi::copy_const_t<const int, volatile float>, const volatile float);
}
