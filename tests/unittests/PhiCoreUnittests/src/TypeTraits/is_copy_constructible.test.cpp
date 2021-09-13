#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/Config/Compiler.hpp>
#include <Phi/TypeTraits/is_copy_constructible.hpp>

template <typename T>
void test_is_copy_constructible()
{
    STATIC_REQUIRE(phi::is_copy_constructible<T>::value);
    STATIC_REQUIRE(phi::is_copy_constructible<const T>::value);

    STATIC_REQUIRE(phi::is_copy_constructible_v<T>);
    STATIC_REQUIRE(phi::is_copy_constructible_v<const T>);
}

template <typename T>
void test_is_not_copy_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_copy_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_copy_constructible<const T>::value);

    STATIC_REQUIRE_FALSE(phi::is_copy_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_copy_constructible_v<const T>);
}

struct A
{
    A(const A&);
};

class B
{
    B(const B&);
};

struct C
{
    C(C&);              // not const
    void operator=(C&); // not const
};

TEST_CASE("is_copy_constructible")
{
    test_is_copy_constructible<A>();
    test_is_copy_constructible<int&>();
    test_is_copy_constructible<Union>();
    test_is_copy_constructible<Empty>();
    test_is_copy_constructible<int>();
    test_is_copy_constructible<float>();
    test_is_copy_constructible<double>();
    test_is_copy_constructible<int*>();
    test_is_copy_constructible<const int*>();
    test_is_copy_constructible<volatile int*>();
    test_is_copy_constructible<const volatile int*>();
    test_is_copy_constructible<int**>();
    test_is_copy_constructible<NotEmpty>();
    test_is_copy_constructible<bit_zero>();
    test_is_copy_constructible<Class>();
    test_is_copy_constructible<Struct>();
    test_is_copy_constructible<NonEmptyUnion>();
    test_is_copy_constructible<Enum>();
    test_is_copy_constructible<EnumSigned>();
    test_is_copy_constructible<EnumUnsigned>();
    test_is_copy_constructible<EnumClass>();
    test_is_copy_constructible<FunctionPtr>();
    test_is_copy_constructible<MemberObjectPtr>();
    test_is_copy_constructible<MemberFunctionPtr>();
    test_is_copy_constructible<AbstractTemplate<double>>();

    test_is_not_copy_constructible<char[3]>();
    test_is_not_copy_constructible<char[]>();
    test_is_not_copy_constructible<void>();
    test_is_not_copy_constructible<Abstract>();
    test_is_not_copy_constructible<B>();
    test_is_not_copy_constructible<C>();

    // GCC seems to be bugged when it comes to AbstractTemplate<int>
#if PHI_COMPILER_IS_NOT(GCC)
    test_is_not_copy_constructible<AbstractTemplate<int>>();
#endif
}
