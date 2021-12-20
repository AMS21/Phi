#include <phi/test/test_macros.hpp>

#include "phi/core/nullptr_t.hpp"
#include "test_types.hpp"
#include <phi/type_traits/is_empty.hpp>

template <typename T>
void test_is_empty()
{
    STATIC_REQUIRE(phi::is_empty<T>::value);
    STATIC_REQUIRE(phi::is_empty<const T>::value);
    STATIC_REQUIRE(phi::is_empty<volatile T>::value);
    STATIC_REQUIRE(phi::is_empty<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_empty_v<T>);
    STATIC_REQUIRE(phi::is_empty_v<const T>);
    STATIC_REQUIRE(phi::is_empty_v<volatile T>);
    STATIC_REQUIRE(phi::is_empty_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_empty()
{
    STATIC_REQUIRE_FALSE(phi::is_empty<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_empty<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_empty<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_empty<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_empty_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_empty_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_empty_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_empty_v<const volatile T>);
#endif
}

class VirtualFn
{
    virtual ~VirtualFn();
};

struct NotEmptyBase : public NotEmpty
{};

struct EmptyBase : public Empty
{};

struct VirtualBase : virtual Empty
{};

struct StaticMember
{
    static int foo;
};

struct NonStaticMember
{
    int foo;
};

TEST_CASE("is_empty")
{
    test_is_not_empty<phi::nullptr_t>();
    test_is_not_empty<void>();
    test_is_not_empty<int&>();
    test_is_not_empty<int&&>();
    test_is_not_empty<int>();
    test_is_not_empty<short>();
    test_is_not_empty<float>();
    test_is_not_empty<double>();
    test_is_not_empty<int*>();
    test_is_not_empty<const int*>();
    test_is_not_empty<volatile int*>();
    test_is_not_empty<const volatile int*>();
    test_is_not_empty<int**>();
    test_is_not_empty<char[3]>();
    test_is_not_empty<char[]>();
    test_is_not_empty<Union>();
    test_is_not_empty<NotEmpty>();
    test_is_not_empty<VirtualFn>();
    test_is_not_empty<VirtualBase>();
    test_is_not_empty<NotEmptyBase>();
    test_is_not_empty<NonStaticMember>();
#if PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    test_is_empty<bit_one>();
#else
    test_is_not_empty<bit_one>();
#endif
    test_is_not_empty<NonEmptyUnion>();
    test_is_not_empty<Abstract>();
    test_is_not_empty<AbstractTemplate<int>>();
    test_is_not_empty<Enum>();
    test_is_not_empty<EnumSigned>();
    test_is_not_empty<EnumUnsigned>();
    test_is_not_empty<EnumClass>();
    test_is_not_empty<Function>();
    test_is_not_empty<FunctionPtr>();
    test_is_not_empty<MemberObjectPtr>();
    test_is_not_empty<MemberFunctionPtr>();

    test_is_empty<Class>();
    test_is_empty<Empty>();
    test_is_empty<EmptyBase>();
    test_is_empty<StaticMember>();
    test_is_empty<bit_zero>();
    test_is_empty<AbstractTemplate<double>>();
}
