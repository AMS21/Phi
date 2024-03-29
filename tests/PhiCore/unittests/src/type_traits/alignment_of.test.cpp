#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/platform.hpp>
#include <phi/type_traits/alignment_of.hpp>
#include <cstdint>
#include <type_traits>

template <typename TypeT, unsigned A>
void test_alignment_of()
{
    PHI_CONSTEXPR static unsigned alignof_result = alignof(TypeT);

    // Test that the golden value is correct
    STATIC_REQUIRE(alignof_result == A);

    STATIC_REQUIRE(phi::alignment_of<TypeT>::value == alignof_result);
    STATIC_REQUIRE(phi::alignment_of<TypeT>::value == A);
    STATIC_REQUIRE(phi::alignment_of<const TypeT>::value == A);
    STATIC_REQUIRE(phi::alignment_of<volatile TypeT>::value == A);
    STATIC_REQUIRE(phi::alignment_of<const volatile TypeT>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::alignment_of_v<TypeT> == alignof_result);
    STATIC_REQUIRE(phi::alignment_of_v<TypeT> == A);
    STATIC_REQUIRE(phi::alignment_of_v<const TypeT> == A);
    STATIC_REQUIRE(phi::alignment_of_v<volatile TypeT> == A);
    STATIC_REQUIRE(phi::alignment_of_v<const volatile TypeT> == A);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::alignment_of<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(phi::alignment_of<TypeT>::value == std::alignment_of<TypeT>::value);
}

TEST_CASE("alignment_of")
{
    PHI_CONSTEXPR unsigned ptr_size = sizeof(std::intptr_t);

    test_alignment_of<int&, 4>();
    test_alignment_of<int&&, 4>();
    test_alignment_of<class_type, 1>();
    test_alignment_of<empty, 1>();
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
    test_alignment_of<function_ptr, ptr_size>();
    test_alignment_of<member_object_ptr, ptr_size>();
    test_alignment_of<member_function_ptr, ptr_size>();
#endif
}
