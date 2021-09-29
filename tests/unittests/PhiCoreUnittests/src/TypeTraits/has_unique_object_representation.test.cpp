#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/TypeTraits/has_unique_object_representations.hpp>

template <class T>
void test_has_unique_object_representations()
{
    STATIC_REQUIRE(phi::has_unique_object_representations<T>::value);
    STATIC_REQUIRE(phi::has_unique_object_representations<const T>::value);
    STATIC_REQUIRE(phi::has_unique_object_representations<volatile T>::value);
    STATIC_REQUIRE(phi::has_unique_object_representations<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::has_unique_object_representations_v<T>);
    STATIC_REQUIRE(phi::has_unique_object_representations_v<const T>);
    STATIC_REQUIRE(phi::has_unique_object_representations_v<volatile T>);
    STATIC_REQUIRE(phi::has_unique_object_representations_v<const volatile T>);
#endif
}

template <class T>
void test_has_not_has_unique_object_representations()
{
    STATIC_REQUIRE(!phi::has_unique_object_representations<T>::value);
    STATIC_REQUIRE(!phi::has_unique_object_representations<const T>::value);
    STATIC_REQUIRE(!phi::has_unique_object_representations<volatile T>::value);
    STATIC_REQUIRE(!phi::has_unique_object_representations<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(!phi::has_unique_object_representations_v<T>);
    STATIC_REQUIRE(!phi::has_unique_object_representations_v<const T>);
    STATIC_REQUIRE(!phi::has_unique_object_representations_v<volatile T>);
    STATIC_REQUIRE(!phi::has_unique_object_representations_v<const volatile T>);
#endif
}

union EmptyUnion
{};

struct A
{
    ~A();
    unsigned foo;
};

struct B
{
    char bar;
    int  foo;
};

TEST_CASE("has_unique_object_representation")
{
    test_has_not_has_unique_object_representations<void>();
    test_has_not_has_unique_object_representations<Empty>();
    test_has_not_has_unique_object_representations<EmptyUnion>();
    test_has_not_has_unique_object_representations<NotEmpty>();
    test_has_not_has_unique_object_representations<bit_zero>();
    test_has_not_has_unique_object_representations<Abstract>();
    test_has_not_has_unique_object_representations<B>();

    //  I would expect all three of these to have unique representations.
    //  I would also expect that there are systems where they do not.
    //     test_has_not_has_unique_object_representations<int&>();
    //     test_has_not_has_unique_object_representations<int *>();
    //     test_has_not_has_unique_object_representations<double>();

    test_has_unique_object_representations<unsigned>();
    test_has_unique_object_representations<NonEmptyUnion>();
    test_has_unique_object_representations<char[3]>();
    test_has_unique_object_representations<char[]>();
}
