#include <catch2/catch.hpp>

#include "Phi/Core/Nullptr.hpp"
#include "TestTypes.hpp"
#include <Phi/TypeTraits/extent.hpp>

template <typename T, unsigned A>
void test_extent()
{
    STATIC_REQUIRE(phi::extent<T>::value == A);
    STATIC_REQUIRE(phi::extent<const T>::value == A);
    STATIC_REQUIRE(phi::extent<volatile T>::value == A);
    STATIC_REQUIRE(phi::extent<const volatile T>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::extent_v<T> == A);
    STATIC_REQUIRE(phi::extent_v<const T> == A);
    STATIC_REQUIRE(phi::extent_v<volatile T> == A);
    STATIC_REQUIRE(phi::extent_v<const volatile T> == A);
#endif
}

template <typename T, unsigned Val, unsigned A>
void test_extent_var()
{
    STATIC_REQUIRE(phi::extent<T, Val>::value == A);
    STATIC_REQUIRE(phi::extent<const T, Val>::value == A);
    STATIC_REQUIRE(phi::extent<volatile T, Val>::value == A);
    STATIC_REQUIRE(phi::extent<const volatile T, Val>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::extent_v<T, Val> == A);
    STATIC_REQUIRE(phi::extent_v<const T, Val> == A);
    STATIC_REQUIRE(phi::extent_v<volatile T, Val> == A);
    STATIC_REQUIRE(phi::extent_v<const volatile T, Val> == A);
#endif
}

TEST_CASE("extent")
{
    test_extent<phi::nullptr_t, 0>();
    test_extent<void, 0>();
    test_extent<int&, 0>();
    test_extent<int&&, 0>();
    test_extent<int*, 0>();
    test_extent<const int*, 0>();
    test_extent<volatile int*, 0>();
    test_extent<const volatile int*, 0>();
    test_extent<int, 0>();
    test_extent<double, 0>();
    test_extent<bool, 0>();
    test_extent<unsigned, 0>();
    test_extent<Class, 0>();
    test_extent<Struct, 0>();
    test_extent<Empty, 0>();
    test_extent<Union, 0>();
    test_extent<bit_zero, 0>();
    test_extent<Abstract, 0>();
    test_extent<Enum, 0>();
    test_extent<EnumSigned, 0>();
    test_extent<EnumUnsigned, 0>();
    test_extent<EnumClass, 0>();
    test_extent<incomplete_type, 0>();
    test_extent<FunctionPtr, 0>();
    test_extent<MemberObjectPtr, 0>();
    test_extent<MemberFunctionPtr, 0>();

    test_extent<int[1], 1>();
    test_extent<int[2], 2>();
    test_extent<int[3], 3>();
    test_extent<int[1][4], 1>();
    test_extent<int[2][4], 2>();
    test_extent<int[3][4], 3>();
    test_extent<int[1][4][9], 1>();
    test_extent<int[2][4][9], 2>();
    test_extent<int[3][4][9], 3>();

    test_extent<int[], 0>();
    test_extent<int[][4], 0>();
    test_extent<int[][4][9], 0>();

    // Extent 1
    test_extent_var<int, 1, 0>();
    test_extent_var<int[], 1, 0>();
    test_extent_var<int[1], 1, 0>();
    test_extent_var<int[2], 1, 0>();
    test_extent_var<int[3], 1, 0>();
    test_extent_var<int[1][4], 1, 4>();
    test_extent_var<int[2][4], 1, 4>();
    test_extent_var<int[3][4], 1, 4>();
    test_extent_var<int[2][3], 1, 3>();
    test_extent_var<int[][4], 1, 4>();
    test_extent_var<int[1][4][5], 1, 4>();
    test_extent_var<int[2][4][5], 1, 4>();
    test_extent_var<int[3][4][5], 1, 4>();
    test_extent_var<int[2][3][5], 1, 3>();
    test_extent_var<int[][4][5], 1, 4>();

    // Extent 2
    test_extent_var<int, 2, 0>();
    test_extent_var<int[], 2, 0>();
    test_extent_var<int[1], 2, 0>();
    test_extent_var<int[2], 2, 0>();
    test_extent_var<int[3], 2, 0>();
    test_extent_var<int[1][4], 2, 0>();
    test_extent_var<int[2][4], 2, 0>();
    test_extent_var<int[3][4], 2, 0>();
    test_extent_var<int[2][3], 2, 0>();
    test_extent_var<int[][4], 2, 0>();
    test_extent_var<int[1][1][3], 2, 3>();
    test_extent_var<int[1][1][4], 2, 4>();
    test_extent_var<int[][1][3], 2, 3>();
    test_extent_var<int[][1][3][4], 2, 3>();
    test_extent_var<int[][1][3][5], 2, 3>();
}
