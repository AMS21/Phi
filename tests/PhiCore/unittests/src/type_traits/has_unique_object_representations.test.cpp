#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/type_traits/has_unique_object_representations.hpp>
#include <type_traits>

template <typename TypeT>
void test_has_unique_object_representations_impl()
{
#if PHI_HAS_WORKING_HAS_UNIQUE_OBJECT_REPRESENTATIONS()
    STATIC_REQUIRE(phi::has_unique_object_representations<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::has_no_unique_object_representations<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::has_unique_object_representations_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::has_no_unique_object_representations_v<TypeT>);
#    endif

    // Standard compatbility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::has_unique_object_representations<TypeT>::value);
#    endif
#endif
}

template <typename TypeT>
void test_has_unique_object_representations()
{
    test_has_unique_object_representations_impl<TypeT>();
    test_has_unique_object_representations_impl<const TypeT>();
    test_has_unique_object_representations_impl<volatile TypeT>();
    test_has_unique_object_representations_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_has_no_unique_object_representations_impl()
{
#if PHI_HAS_WORKING_HAS_UNIQUE_OBJECT_REPRESENTATIONS()
    STATIC_REQUIRE_FALSE(phi::has_unique_object_representations<TypeT>::value);
    STATIC_REQUIRE(phi::has_no_unique_object_representations<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_unique_object_representations_v<TypeT>);
    STATIC_REQUIRE(phi::has_no_unique_object_representations_v<TypeT>);
#    endif

// Standard compatbility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::has_unique_object_representations<TypeT>::value);
#    endif
#endif
}

template <typename TypeT>
void test_has_no_unique_object_representations()
{
    test_has_no_unique_object_representations_impl<TypeT>();
    test_has_no_unique_object_representations_impl<const TypeT>();
    test_has_no_unique_object_representations_impl<volatile TypeT>();
    test_has_no_unique_object_representations_impl<const volatile TypeT>();
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
    test_has_no_unique_object_representations<empty>();
    test_has_no_unique_object_representations<EmptyUnion>();
    test_has_no_unique_object_representations<not_empty>();
    test_has_no_unique_object_representations<bit_zero>();
    test_has_no_unique_object_representations<abstract>();
    test_has_no_unique_object_representations<B>();

    //  I would expect all three of these to have unique representations.
    //  I would also expect that there are systems where they do not.
    //     test_has_no_unique_object_representations<int&>();
    //     test_has_no_unique_object_representations<int *>();
    //     test_has_no_unique_object_representations<double>();

    test_has_unique_object_representations<unsigned>();
    test_has_unique_object_representations<non_empty_union>();
    test_has_unique_object_representations<char[3]>();
    test_has_unique_object_representations<char[]>();
}
