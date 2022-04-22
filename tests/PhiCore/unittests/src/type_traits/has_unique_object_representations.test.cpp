#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/type_traits/has_unique_object_representations.hpp>
#include <type_traits>

template <typename T>
void test_has_unique_object_representations_impl()
{
#if PHI_HAS_WORKING_HAS_UNIQUE_OBJECT_REPRESENTATIONS()
    STATIC_REQUIRE(phi::has_unique_object_representations<T>::value);
    STATIC_REQUIRE_FALSE(phi::has_no_unique_object_representations<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::has_unique_object_representations_v<T>);
    STATIC_REQUIRE_FALSE(phi::has_no_unique_object_representations_v<T>);
#    endif

    // Standard compatbility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::has_unique_object_representations<T>::value);
#    endif
#endif
}

template <typename T>
void test_has_unique_object_representations()
{
    test_has_unique_object_representations_impl<T>();
    test_has_unique_object_representations_impl<const T>();
    test_has_unique_object_representations_impl<volatile T>();
    test_has_unique_object_representations_impl<const volatile T>();
}

template <typename T>
void test_has_no_unique_object_representations_impl()
{
#if PHI_HAS_WORKING_HAS_UNIQUE_OBJECT_REPRESENTATIONS()
    STATIC_REQUIRE_FALSE(phi::has_unique_object_representations<T>::value);
    STATIC_REQUIRE(phi::has_no_unique_object_representations<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_unique_object_representations_v<T>);
    STATIC_REQUIRE(phi::has_no_unique_object_representations_v<T>);
#    endif

// Standard compatbility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::has_unique_object_representations<T>::value);
#    endif
#endif
}

template <typename T>
void test_has_no_unique_object_representations()
{
    test_has_no_unique_object_representations_impl<T>();
    test_has_no_unique_object_representations_impl<const T>();
    test_has_no_unique_object_representations_impl<volatile T>();
    test_has_no_unique_object_representations_impl<const volatile T>();
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

TEST_CASE("has_unique_object_representations")
{
    test_has_no_unique_object_representations<void>();
    test_has_no_unique_object_representations<Empty>();
    test_has_no_unique_object_representations<EmptyUnion>();
    test_has_no_unique_object_representations<NotEmpty>();
    test_has_no_unique_object_representations<BitZero>();
    test_has_no_unique_object_representations<Abstract>();
    test_has_no_unique_object_representations<B>();

    //  I would expect all three of these to have unique representations.
    //  I would also expect that there are systems where they do not.
    //     test_has_no_unique_object_representations<int&>();
    //     test_has_no_unique_object_representations<int *>();
    //     test_has_no_unique_object_representations<double>();

    test_has_unique_object_representations<unsigned>();
    test_has_unique_object_representations<NonEmptyUnion>();
    test_has_unique_object_representations<char[3]>();
    test_has_unique_object_representations<char[]>();
}
