#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/platform.hpp>
#include <phi/type_traits/alignment_of.hpp>
#include <cstdint>
#include <type_traits>

template <typename T, unsigned A>
void test_alignment_of()
{
    constexpr static unsigned alignof_result = alignof(T);

    // Test that the golden value is correct
    STATIC_REQUIRE(alignof_result == A);

    STATIC_REQUIRE(phi::alignment_of<T>::value == alignof_result);
    STATIC_REQUIRE(phi::alignment_of<T>::value == A);
    STATIC_REQUIRE(phi::alignment_of<const T>::value == A);
    STATIC_REQUIRE(phi::alignment_of<volatile T>::value == A);
    STATIC_REQUIRE(phi::alignment_of<const volatile T>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::alignment_of_v<T> == alignof_result);
    STATIC_REQUIRE(phi::alignment_of_v<T> == A);
    STATIC_REQUIRE(phi::alignment_of_v<const T> == A);
    STATIC_REQUIRE(phi::alignment_of_v<volatile T> == A);
    STATIC_REQUIRE(phi::alignment_of_v<const volatile T> == A);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::alignment_of<T>);

    // Standard compatibility
    STATIC_REQUIRE(phi::alignment_of<T>::value == std::alignment_of<T>::value);
}

TEST_CASE("alignment_of")
{
    constexpr unsigned ptr_size = sizeof(std::intptr_t);

    test_alignment_of<int&, 4>();
    test_alignment_of<int&&, 4>();
    test_alignment_of<Class, 1>();
    test_alignment_of<Empty, 1>();
    test_alignment_of<int*, ptr_size>();
    test_alignment_of<const int*, ptr_size>();
    test_alignment_of<volatile int*, ptr_size>();
    test_alignment_of<const volatile int*, ptr_size>();
    test_alignment_of<char[3], 1>();
    test_alignment_of<char[], 1>();
    test_alignment_of<int, 4>();
    // The test case below is a hack. It's hard to detect what golden value
    // we should expect. In most cases it should be 8. But in i386 builds
    // with Clang >= 8 or GCC >= 8 the value is '4'.
    test_alignment_of<double, alignof(double)>();
#if (defined(__ppc__) && !defined(__ppc64__))
    test_alignment_of<bool, 4>(); // 32-bit PPC has four byte bool
#else
    test_alignment_of<bool, 1>();
#endif
    test_alignment_of<unsigned, 4>();

#if PHI_COMPILER_IS(WINCLANG)
#else
    test_alignment_of<FunctionPtr, ptr_size>();
    test_alignment_of<MemberObjectPtr, ptr_size>();
    test_alignment_of<MemberFunctionPtr, ptr_size>();
#endif
}
