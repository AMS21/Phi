#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/nodiscard.hpp>
#include <phi/core/assert.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/ignore.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/move.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_nothrow_assignable.hpp>
#include <phi/type_traits/is_nothrow_constructible.hpp>
#include <phi/type_traits/is_trivial.hpp>
#include <phi/type_traits/is_trivially_copy_assignable.hpp>
#include <phi/type_traits/is_trivially_copy_constructible.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <phi/type_traits/is_trivially_default_constructible.hpp>
#include <phi/type_traits/is_trivially_destructible.hpp>
#include <phi/type_traits/is_trivially_move_assignable.hpp>
#include <phi/type_traits/is_trivially_move_constructible.hpp>
#include <vector>

struct A
{};

enum E
{
};

PHI_NODISCARD constexpr int nodiscard_func()
{
    return 21;
}

constexpr bool test_ignore()
{
    {
        const phi::ignore_t<unsigned char>& res = (phi::ignore = 42);
        PHI_RELEASE_ASSERT(&res == &phi::ignore);
    }
    {
        phi::ignore_t<unsigned char> copy  = phi::ignore;
        phi::ignore_t<unsigned char> moved = phi::move(copy);
        ((void)moved);
    }
    {
        phi::ignore_t<unsigned char> copy  = phi::ignore;
        copy                               = phi::ignore;
        phi::ignore_t<unsigned char> moved = phi::ignore;
        moved                              = phi::move(copy);
    }
    {
        phi::ignore = 42;
        phi::ignore = phi::move(phi::ignore);
        phi::ignore = nodiscard_func();
        phi::ignore = phi::boolean{true};
    }

    return true;
}

TEST_CASE("core.ignore")
{
    using Type = decltype(phi::ignore);

    constexpr Type& ignore_v = phi::ignore;
    ((void)ignore_v);

    REQUIRE(test_ignore());
    STATIC_REQUIRE(test_ignore());

    // Triviality
    STATIC_REQUIRE(phi::is_trivial<Type>::value);
    STATIC_REQUIRE(phi::is_trivially_default_constructible<Type>::value);
    STATIC_REQUIRE(phi::is_trivially_destructible<Type>::value);

    STATIC_REQUIRE(phi::is_trivially_copy_constructible<Type>::value);
    STATIC_REQUIRE(phi::is_trivially_move_constructible<Type>::value);
    STATIC_REQUIRE(phi::is_trivially_copyable<Type>::value);

    // Assignment is noexcept
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::nullptr_t>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, bool>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, char>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, signed char>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, unsigned char>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, short>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, unsigned short>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, int>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, unsigned int>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, long>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, unsigned long>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, long long>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, unsigned long long>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, float>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, double>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, long double>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, char8_t>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, char16_t>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, char32_t>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, wchar_t>::value);

    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::boolean>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<signed char>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<unsigned char>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<short>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<unsigned short>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<int>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<unsigned int>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<long>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<unsigned long>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<long long>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::integer<unsigned long long>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::floating_point<float>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::floating_point<double>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::floating_point<long double>>::value);

    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, std::vector<int>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, phi::scope_ptr<int>>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, A>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<Type, E>::value);
}
