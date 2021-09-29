#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/is_copy_assignable.hpp>

template <typename T>
void test_is_copy_assignable()
{
    STATIC_REQUIRE(phi::is_copy_assignable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_copy_assignable_v<T>);
#endif
}

template <typename T>
void test_is_not_copy_assignable()
{
    STATIC_REQUIRE_FALSE(phi::is_copy_assignable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_copy_assignable_v<T>);
#endif
}

struct A
{
    A();
};

class B
{
    B& operator=(const B&);
};

struct C
{
    void operator=(C&); // not const
};

TEST_CASE("is_copy_assignable")
{
    test_is_copy_assignable<int>();
    test_is_copy_assignable<int&>();
    test_is_copy_assignable<A>();
    test_is_copy_assignable<bit_zero>();
    test_is_copy_assignable<Union>();
    test_is_copy_assignable<NotEmpty>();
    test_is_copy_assignable<Empty>();
    test_is_copy_assignable<Class>();
    test_is_copy_assignable<Struct>();
    test_is_copy_assignable<NonEmptyUnion>();
    test_is_copy_assignable<Enum>();
    test_is_copy_assignable<EnumSigned>();
    test_is_copy_assignable<EnumUnsigned>();
    test_is_copy_assignable<EnumClass>();
    test_is_copy_assignable<FunctionPtr>();
    test_is_copy_assignable<MemberObjectPtr>();
    test_is_copy_assignable<MemberFunctionPtr>();

    test_is_not_copy_assignable<const int>();
    test_is_not_copy_assignable<int[]>();
    test_is_not_copy_assignable<int[3]>();
    test_is_not_copy_assignable<B>();
    test_is_not_copy_assignable<void>();
    test_is_not_copy_assignable<C>();
    test_is_not_copy_assignable<incomplete_type>();
}
