#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/type_traits/is_pointer_interconvertible_base_of.hpp>
#include <type_traits>

template <typename B, typename D>
void test_is_pointer_interconvertible_base_of()
{
#if PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_BASE_OF()
    STATIC_REQUIRE(phi::is_pointer_interconvertible_base_of<B, D>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_pointer_interconvertible_base_of<B, D>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_pointer_interconvertible_base_of_v<B, D>);
    STATIC_REQUIRE_FALSE(phi::is_not_pointer_interconvertible_base_of_v<B, D>);
#    endif

    // Standard compatibililty
#    if PHI_CPP_STANDARD_IS_ATLEAST(20)
    STATIC_REQUIRE(std::is_pointer_interconvertible_base_of<B, D>::value);
#    endif
#endif
}

template <typename B, typename D>
void test_is_not_pointer_interconvertible_base_of()
{
#if PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_BASE_OF()
    STATIC_REQUIRE_FALSE(phi::is_pointer_interconvertible_base_of<B, D>::value);
    STATIC_REQUIRE(phi::is_not_pointer_interconvertible_base_of<B, D>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_pointer_interconvertible_base_of_v<B, D>);
    STATIC_REQUIRE(phi::is_not_pointer_interconvertible_base_of_v<B, D>);
#    endif

    // Standard compatibililty
#    if PHI_CPP_STANDARD_IS_ATLEAST(20)
    STATIC_REQUIRE_FALSE(std::is_pointer_interconvertible_base_of<B, D>::value);
#    endif
#endif
}

struct B
{};

struct D : B
{
    int i;
};

struct E : D
{};
// E is not standard-layout

struct D1 : B
{};

struct D2 : B
{};

struct D3 : D1, D2
{};
// B is ambiguously derived

union U;

struct I; // incomplete

struct Foo
{};

struct Bar
{};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunused-private-field")

class Baz : Foo, public Bar
{
    int x;
};

class NonStdLayout : public Baz
{
    int y;
};

PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("is_pointer_interconvertible_base_of")
{
    test_is_not_pointer_interconvertible_base_of<void, void>();
    test_is_not_pointer_interconvertible_base_of<void*, void*>();
    test_is_not_pointer_interconvertible_base_of<void*, int*>();
    test_is_not_pointer_interconvertible_base_of<int*, int*>();
    test_is_not_pointer_interconvertible_base_of<int, int>();

    test_is_pointer_interconvertible_base_of<B, B>();
    test_is_pointer_interconvertible_base_of<B, const B>();
    test_is_pointer_interconvertible_base_of<const B, B>();
    test_is_pointer_interconvertible_base_of<const B, const B>();

    test_is_pointer_interconvertible_base_of<B, D>();
    test_is_pointer_interconvertible_base_of<B, const D>();
    test_is_pointer_interconvertible_base_of<const B, D>();
    test_is_pointer_interconvertible_base_of<const B, const D>();

    test_is_not_pointer_interconvertible_base_of<D, B>();
    test_is_not_pointer_interconvertible_base_of<E, B>();
    test_is_not_pointer_interconvertible_base_of<B, D3>();
    test_is_not_pointer_interconvertible_base_of<U, U>();
    test_is_not_pointer_interconvertible_base_of<U, D>();

    test_is_pointer_interconvertible_base_of<I, I>();
    test_is_pointer_interconvertible_base_of<I, const I>();

    #if PHI_COMPILER_IS(MSVC)
    test_is_not_pointer_interconvertible_base_of<Bar, Baz>();
    #else
    test_is_pointer_interconvertible_base_of<Bar, Baz>();
    #endif
    test_is_pointer_interconvertible_base_of<Foo, Baz>();
    test_is_not_pointer_interconvertible_base_of<Baz, NonStdLayout>();
    test_is_pointer_interconvertible_base_of<NonStdLayout, NonStdLayout>();
}
