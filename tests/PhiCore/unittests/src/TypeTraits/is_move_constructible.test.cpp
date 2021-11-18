#include <Phi/Test/TestMacros.hpp>

#include "TestTypes.hpp"
#include <Phi/Config/Compiler.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_move_constructible.hpp>

template <typename T>
void test_is_move_constructible()
{
    STATIC_REQUIRE(phi::is_move_constructible<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_move_constructible_v<T>);
#endif
}

template <typename T>
void test_is_not_move_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_move_constructible<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_move_constructible_v<T>);
#endif
}

struct A
{
    A(const A&);
};

struct B
{
    B(B&&);
};

struct C
{
    C() = delete;
};

struct D
{
    D(const D&) = delete;
};

struct E
{
    E(E&&) = delete;
};

struct F
{
    F& operator=(const F&) = delete;
};

struct G
{
    G& operator=(G&&) = delete;
};

struct H
{
    H() = default;

    H(const H&) = default;
    H(H&&)      = default;

    H& operator=(const H&) = default;
    H& operator=(H&&) = default;
};

TEST_CASE("is_move_constructible")
{
    test_is_move_constructible<phi::nullptr_t>();
    test_is_move_constructible<const phi::nullptr_t>();
    test_is_move_constructible<volatile phi::nullptr_t>();
    test_is_move_constructible<const volatile phi::nullptr_t>();
    test_is_move_constructible<bool>();
    test_is_move_constructible<short>();
    test_is_move_constructible<int>();
    test_is_move_constructible<const int>();
    test_is_move_constructible<volatile int>();
    test_is_move_constructible<const volatile int>();
    test_is_move_constructible<float>();
    test_is_move_constructible<double>();
    test_is_move_constructible<int&>();
    test_is_move_constructible<const int&>();
    test_is_move_constructible<volatile int&>();
    test_is_move_constructible<const volatile int&>();
    test_is_move_constructible<int&&>();
    test_is_move_constructible<const int&&>();
    test_is_move_constructible<volatile int&&>();
    test_is_move_constructible<const volatile int&&>();
    test_is_move_constructible<int*>();
    test_is_move_constructible<const int*>();
    test_is_move_constructible<volatile int*>();
    test_is_move_constructible<const volatile int*>();
    test_is_move_constructible<int**>();
    test_is_move_constructible<void*>();
    test_is_move_constructible<Class>();
    test_is_move_constructible<const Class>();
    test_is_move_constructible<Empty>();
    test_is_move_constructible<Union>();
    test_is_move_constructible<NotEmpty>();
    test_is_move_constructible<NonEmptyUnion>();
    test_is_move_constructible<bit_zero>();
    test_is_move_constructible<bit_one>();
    test_is_move_constructible<AbstractTemplate<double>>();
    test_is_move_constructible<Enum>();
    test_is_move_constructible<EnumSigned>();
    test_is_move_constructible<EnumUnsigned>();
    test_is_move_constructible<EnumClass>();
    test_is_move_constructible<FunctionPtr>();
    test_is_move_constructible<MemberObjectPtr>();
    test_is_move_constructible<MemberFunctionPtr>();

    test_is_not_move_constructible<char[3]>();
    test_is_not_move_constructible<volatile Class>();
    test_is_not_move_constructible<const volatile Class>();
    test_is_not_move_constructible<Abstract>();
    test_is_not_move_constructible<Function>();

    test_is_move_constructible<A>();
    test_is_move_constructible<const A>();
    test_is_not_move_constructible<volatile A>();
    test_is_not_move_constructible<const volatile A>();

    test_is_move_constructible<B>();
    test_is_not_move_constructible<const B>();
    test_is_not_move_constructible<volatile B>();
    test_is_not_move_constructible<const volatile B>();

    test_is_move_constructible<C>();
    test_is_move_constructible<const C>();
    test_is_not_move_constructible<volatile C>();
    test_is_not_move_constructible<const volatile C>();

    test_is_not_move_constructible<D>();
    test_is_not_move_constructible<const D>();
    test_is_not_move_constructible<volatile D>();
    test_is_not_move_constructible<const volatile D>();

    test_is_not_move_constructible<E>();
    test_is_not_move_constructible<const E>();
    test_is_not_move_constructible<volatile E>();
    test_is_not_move_constructible<const volatile E>();

    test_is_move_constructible<F>();
    test_is_move_constructible<const F>();
    test_is_not_move_constructible<volatile F>();
    test_is_not_move_constructible<const volatile F>();

    test_is_not_move_constructible<G>();
    test_is_not_move_constructible<const G>();
    test_is_not_move_constructible<volatile G>();
    test_is_not_move_constructible<const volatile G>();

    test_is_move_constructible<H>();
    test_is_move_constructible<const H>();
    test_is_not_move_constructible<volatile H>();
    test_is_not_move_constructible<const volatile H>();

#if !PHI_HAS_BUG_GCC_102305()
    // Test GCC bug 102305 (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305)
    test_is_not_move_constructible<AbstractTemplate<int>>();
#endif

    // Incomplete types only work with the intrinsic functions
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_move_constructible<void>();
    test_is_not_move_constructible<const void>();
    test_is_not_move_constructible<volatile void>();
    test_is_not_move_constructible<const volatile void>();

    test_is_not_move_constructible<char[]>();
#endif
}
