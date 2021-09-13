#include <catch2/catch_test_macros.hpp>

#include "TestTypes.hpp"
#include <Phi/Config/Compiler.hpp>
#include <Phi/TypeTraits/is_constructible.hpp>

struct A
{
    explicit A(int);
    A(int, double);
    A(int, long, double);

private:
    A(char);
};

struct Base
{};

struct Derived : public Base
{};

class AbstractFunc
{
    virtual ~AbstractFunc();
    virtual void foo() = 0;
};

class AbstractDestructor
{
    virtual ~AbstractDestructor() = 0;
};

struct PrivateDtor
{
    PrivateDtor(int)
    {}

private:
    ~PrivateDtor()
    {}
};

struct S
{
    template <typename T>
    explicit operator T() const;
};

template <typename To>
struct ImplicitTo
{
    operator To();
};

template <typename To>
struct ExplicitTo
{
    explicit operator To();
};

template <typename T>
void test_is_constructible()
{
    STATIC_REQUIRE(phi::is_constructible<T>::value);
    STATIC_REQUIRE(phi::is_constructible_v<T>);
}

template <typename T, typename A0>
void test_is_constructible()
{
    STATIC_REQUIRE(phi::is_constructible<T, A0>::value);
    STATIC_REQUIRE(phi::is_constructible_v<T, A0>);
}

template <typename T, typename A0, typename A1>
void test_is_constructible()
{
    STATIC_REQUIRE(phi::is_constructible<T, A0, A1>::value);
    STATIC_REQUIRE(phi::is_constructible_v<T, A0, A1>);
}

template <typename T, typename A0, typename A1, typename A2>
void test_is_constructible()
{
    STATIC_REQUIRE(phi::is_constructible<T, A0, A1, A2>::value);
    STATIC_REQUIRE(phi::is_constructible_v<T, A0, A1, A2>);
}

template <typename T>
void test_is_not_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_constructible_v<T>);
}

template <typename T, typename A0>
void test_is_not_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_constructible<T, A0>::value);
    STATIC_REQUIRE_FALSE(phi::is_constructible_v<T, A0>);
}

TEST_CASE("is_constructible")
{
    using B = Base;
    using D = Derived;

    test_is_constructible<int>();
    test_is_constructible<int, const int>();
    test_is_constructible<A, int>();
    test_is_constructible<A, int, double>();
    test_is_constructible<A, int, long, double>();
    test_is_constructible<int&, int&>();

    test_is_not_constructible<A>();
    test_is_not_constructible<A, char>();

    test_is_not_constructible<A, void>();
    test_is_not_constructible<int, void()>();
    test_is_not_constructible<int, void (&)()>();
    test_is_not_constructible<int, void() const>();
    test_is_not_constructible<int&, void>();
    test_is_not_constructible<int&, void()>();
    test_is_not_constructible<int&, void() const>();
    test_is_not_constructible<int&, void (&)()>();

    test_is_not_constructible<void>();
    test_is_not_constructible<const void>(); // LWG 2738
    test_is_not_constructible<volatile void>();
    test_is_not_constructible<const volatile void>();
    test_is_not_constructible<int&>();
    test_is_not_constructible<Abstract>();
    test_is_not_constructible<AbstractFunc>();
    test_is_not_constructible<AbstractDestructor>();
    test_is_constructible<int, S>();
    test_is_not_constructible<int&, S>();

    test_is_constructible<void (&)(), void (&)()>();
    test_is_constructible<void (&)(), void()>();
    test_is_constructible<void(&&)(), void(&&)()>();
    test_is_constructible<void(&&)(), void()>();
    test_is_constructible<void(&&)(), void (&)()>();

    test_is_constructible<int const&, int>();
    test_is_constructible<int const&, int&&>();

    test_is_constructible<int&&, double&>();
    test_is_constructible<void (&)(), void(&&)()>();

    test_is_not_constructible<int&, int>();
    test_is_not_constructible<int&, int const&>();
    test_is_not_constructible<int&, int&&>();

    test_is_constructible<int&&, int>();
    test_is_constructible<int&&, int&&>();
    test_is_not_constructible<int&&, int&>();
    test_is_not_constructible<int&&, int const&&>();

    test_is_constructible<Base, Derived>();
    test_is_constructible<Base&, Derived&>();
    test_is_not_constructible<Derived&, Base&>();
    test_is_constructible<Base const&, Derived const&>();
#if PHI_COMPILER_IS_NOT(GCC)
    test_is_not_constructible<Derived const&, Base const&>();
    test_is_not_constructible<Derived const&, Base>();
#endif

    test_is_constructible<Base&&, Derived>();
    test_is_constructible<Base&&, Derived&&>();
#if PHI_COMPILER_IS_NOT(GCC)
    test_is_not_constructible<Derived&&, Base&&>();
    test_is_not_constructible<Derived&&, Base>();
#endif

    // test that T must also be destructible
    test_is_constructible<PrivateDtor&, PrivateDtor&>();
    test_is_not_constructible<PrivateDtor, int>();

    test_is_not_constructible<void() const, void() const>();
    test_is_not_constructible<void() const, void*>();

    test_is_constructible<int&, ImplicitTo<int&>>();
    test_is_constructible<const int&, ImplicitTo<int&&>>();
    test_is_constructible<int&&, ImplicitTo<int&&>>();
    test_is_constructible<const int&, ImplicitTo<int>>();

    test_is_not_constructible<B&&, B&>();
    test_is_not_constructible<B&&, D&>();
    test_is_constructible<B&&, ImplicitTo<D&&>>();
    test_is_constructible<B&&, ImplicitTo<D&&>&>();
    test_is_constructible<int&&, double&>();
    test_is_constructible<const int&, ImplicitTo<int&>&>();
    test_is_constructible<const int&, ImplicitTo<int&>>();
    test_is_constructible<const int&, ExplicitTo<int&>&>();
    test_is_constructible<const int&, ExplicitTo<int&>>();

    test_is_constructible<const int&, ExplicitTo<int&>&>();
    test_is_constructible<const int&, ExplicitTo<int&>>();

    // Binding through reference-compatible type is required to perform
    // direct-initialization as described in [over.match.ref] p. 1 b. 1:
    //
    // But the rvalue to lvalue reference binding isn't allowed according to
    // [over.match.ref] despite Clang accepting it.
    test_is_constructible<int&, ExplicitTo<int&>>();
#if PHI_COMPILER_IS_NOT(GCC)
    test_is_constructible<const int&, ExplicitTo<int&&>>();
#endif

    test_is_constructible<int&&, ExplicitTo<int&&>>();

#if PHI_COMPILER_IS(CLANG)
    // FIXME Clang and GCC disagree on the validity of this expression.
    test_is_constructible<const int&, ExplicitTo<int>>();
    test_is_constructible<int&&, ExplicitTo<int>>();
#else
    test_is_not_constructible<const int&, ExplicitTo<int>>();
    test_is_not_constructible<int&&, ExplicitTo<int>>();
#endif

    // Binding through temporary behaves like copy-initialization,
    // see [dcl.init.ref] p. 5, very last sub-bullet:
    test_is_not_constructible<const int&, ExplicitTo<double&&>>();
    test_is_not_constructible<int&&, ExplicitTo<double&&>>();

    test_is_not_constructible<void()>();
    test_is_not_constructible<void() const>();
    test_is_not_constructible<void() volatile>();
    test_is_not_constructible<void()&>();
    test_is_not_constructible<void() &&>();
}
