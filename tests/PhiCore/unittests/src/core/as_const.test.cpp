#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/extended_attributes.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/as_const.hpp>
#include <phi/type_traits/is_const.hpp>
#include <phi/type_traits/remove_reference.hpp>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")

struct S
{
    int i;
};

PHI_ATTRIBUTE_PURE bool operator==(const S& lhs, const S& rhs)
{
    return lhs.i == rhs.i;
}

bool operator==(const volatile S& lhs, const volatile S& rhs)
{
    return lhs.i == rhs.i;
}

template <typename TypeT>
void test_as_const(TypeT& type)
{
    STATIC_REQUIRE(phi::is_const<
                   typename phi::remove_reference<decltype(phi::as_const(type))>::type>::value);
    STATIC_REQUIRE(phi::is_const<typename phi::remove_reference<decltype(phi::as_const<TypeT>(
                           type))>::type>::value);
    STATIC_REQUIRE(phi::is_const<typename phi::remove_reference<decltype(phi::as_const<const TypeT>(
                           type))>::type>::value);
    STATIC_REQUIRE(phi::is_const<typename phi::remove_reference<
                           decltype(phi::as_const<volatile TypeT>(type))>::type>::value);
    STATIC_REQUIRE(phi::is_const<typename phi::remove_reference<
                           decltype(phi::as_const<const volatile TypeT>(type))>::type>::value);

    CHECK(phi::as_const(type) == type);
    CHECK(phi::as_const<TypeT>(type) == type);
    CHECK(phi::as_const<const TypeT>(type) == type);
    CHECK(phi::as_const<volatile TypeT>(type) == type);
    CHECK(phi::as_const<const volatile TypeT>(type) == type);

    CHECK_NOEXCEPT(phi::as_const(type));
    CHECK_NOEXCEPT(phi::as_const<TypeT>(type));
    CHECK_NOEXCEPT(phi::as_const<const TypeT>(type));
    CHECK_NOEXCEPT(phi::as_const<volatile TypeT>(type));
    CHECK_NOEXCEPT(phi::as_const<const volatile TypeT>(type));
}

TEST_CASE("as_const")
{
    bool   boolean        = true;
    char   character      = 'a';
    int    integer        = 3;
    double floating_point = 4.0;
    S      class_value{2};

    test_as_const(boolean);
    test_as_const(character);
    test_as_const(integer);
    test_as_const(floating_point);
    test_as_const(class_value);
}

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()
