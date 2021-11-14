#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_move_assignable.hpp>

template <typename T>
void test_is_move_assignable()
{
    STATIC_REQUIRE(phi::is_move_assignable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_move_assignable_v<T>);
#endif
}

template <typename T>
void test_is_not_move_assignable()
{
    STATIC_REQUIRE_FALSE(phi::is_move_assignable<T>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_move_assignable_v<T>);
#endif
}

struct A
{
    A();
};

struct B
{
    B(B&&) = delete;
};

struct C
{
    C& operator=(C&&) = delete;
};

struct D
{
    D() = delete;
};

struct E
{
    E(const E&);
};

struct F
{
    F(F&&);
};

struct G
{
    G& operator=(G&&);
};

TEST_CASE("is_move_assignable")
{
    test_is_move_assignable<phi::nullptr_t>();
    test_is_move_assignable<void*>();
    test_is_move_assignable<int*>();
    test_is_move_assignable<const int*>();
    test_is_move_assignable<volatile int*>();
    test_is_move_assignable<const volatile int*>();
    test_is_move_assignable<int**>();
    test_is_move_assignable<int>();
    test_is_move_assignable<volatile int>();
    test_is_move_assignable<short>();
    test_is_move_assignable<float>();
    test_is_move_assignable<double>();
    test_is_move_assignable<Class>();
    test_is_move_assignable<Empty>();
    test_is_move_assignable<NotEmpty>();
    test_is_move_assignable<Union>();
    test_is_move_assignable<NonEmptyUnion>();
    test_is_move_assignable<bit_zero>();
    test_is_move_assignable<bit_one>();
    test_is_move_assignable<Abstract>();
    test_is_move_assignable<AbstractTemplate<int>>();
    test_is_move_assignable<AbstractTemplate<double>>();
    test_is_move_assignable<Enum>();
    test_is_move_assignable<EnumSigned>();
    test_is_move_assignable<EnumUnsigned>();
    test_is_move_assignable<EnumClass>();
    test_is_move_assignable<FunctionPtr>();
    test_is_move_assignable<MemberObjectPtr>();
    test_is_move_assignable<MemberFunctionPtr>();

    test_is_not_move_assignable<Function>();
    test_is_not_move_assignable<void>();
    test_is_not_move_assignable<const int>();
    test_is_not_move_assignable<const short>();
    test_is_not_move_assignable<const float>();
    test_is_not_move_assignable<const double>();
    test_is_not_move_assignable<int[]>();
    test_is_not_move_assignable<int[3]>();

    test_is_move_assignable<A>();
    test_is_not_move_assignable<B>();
    test_is_not_move_assignable<C>();
    test_is_move_assignable<D>();
    test_is_move_assignable<E>();
    test_is_not_move_assignable<F>();
    test_is_move_assignable<G>();
}
