#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_derived_from.hpp>

struct Base1
{};

struct Derived1 : Base1
{};

struct Derived2 : Base1
{};

struct DerivedPrivate : private Base1
{};

struct Derived3 : DerivedPrivate
{};

struct DerivedProtected : protected DerivedPrivate
{};

struct Derived4 : DerivedProtected
{};

struct Derived5 : Derived4
{};

enum Enumeration
{
    Yes,
    No
};

enum class ScopedEnumeration : int
{
    No,
    Yes
};

template <typename FromT, typename ToT>
void test_is_derived_from_impl()
{
#if PHI_HAS_WORKING_IS_DERIVED_FROM()
    STATIC_REQUIRE(phi::is_derived_from<FromT, ToT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_derived_from<FromT, ToT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_derived_from_v<FromT, ToT>);
    STATIC_REQUIRE_FALSE(phi::is_not_derived_from_v<FromT, ToT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_derived_from<FromT, ToT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_derived_from<FromT, ToT>);
#endif
}

template <typename FromT, typename ToT>
void test_is_not_derived_from_impl()
{
#if PHI_HAS_WORKING_IS_DERIVED_FROM()
    STATIC_REQUIRE_FALSE(phi::is_derived_from<FromT, ToT>::value);
    STATIC_REQUIRE(phi::is_not_derived_from<FromT, ToT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_derived_from_v<FromT, ToT>);
    STATIC_REQUIRE(phi::is_not_derived_from_v<FromT, ToT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_derived_from<FromT, ToT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_derived_from<FromT, ToT>);
#endif
}

template <typename FromT, typename ToT>
void test_is_derived_from()
{
    test_is_derived_from_impl<FromT, ToT>();
    test_is_derived_from_impl<FromT, const ToT>();
    test_is_derived_from_impl<FromT, volatile ToT>();
    test_is_derived_from_impl<FromT, const volatile ToT>();

    test_is_derived_from_impl<const FromT, ToT>();
    test_is_derived_from_impl<const FromT, const ToT>();
    test_is_derived_from_impl<const FromT, volatile ToT>();
    test_is_derived_from_impl<const FromT, const volatile ToT>();

    test_is_derived_from_impl<volatile FromT, ToT>();
    test_is_derived_from_impl<volatile FromT, const ToT>();
    test_is_derived_from_impl<volatile FromT, volatile ToT>();
    test_is_derived_from_impl<volatile FromT, const volatile ToT>();

    test_is_derived_from_impl<const volatile FromT, ToT>();
    test_is_derived_from_impl<const volatile FromT, const ToT>();
    test_is_derived_from_impl<const volatile FromT, volatile ToT>();
    test_is_derived_from_impl<const volatile FromT, const volatile ToT>();
}

template <typename FromT, typename ToT>
void test_is_not_derived_from()
{
    test_is_not_derived_from_impl<FromT, ToT>();
    test_is_not_derived_from_impl<FromT, const ToT>();
    test_is_not_derived_from_impl<FromT, volatile ToT>();
    test_is_not_derived_from_impl<FromT, const volatile ToT>();

    test_is_not_derived_from_impl<const FromT, ToT>();
    test_is_not_derived_from_impl<const FromT, const ToT>();
    test_is_not_derived_from_impl<const FromT, volatile ToT>();
    test_is_not_derived_from_impl<const FromT, const volatile ToT>();

    test_is_not_derived_from_impl<volatile FromT, ToT>();
    test_is_not_derived_from_impl<volatile FromT, const ToT>();
    test_is_not_derived_from_impl<volatile FromT, volatile ToT>();
    test_is_not_derived_from_impl<volatile FromT, const volatile ToT>();

    test_is_not_derived_from_impl<const volatile FromT, ToT>();
    test_is_not_derived_from_impl<const volatile FromT, const ToT>();
    test_is_not_derived_from_impl<const volatile FromT, volatile ToT>();
    test_is_not_derived_from_impl<const volatile FromT, const volatile ToT>();
}

TEST_CASE("is_derived_from")
{
    { // Fundamentals shouldn't be derived from anything
        test_is_not_derived_from<int, long>();
        test_is_not_derived_from<signed char, char>();
        test_is_not_derived_from<double, Base1>();

        test_is_not_derived_from<int, Enumeration>();
        test_is_not_derived_from<int, ScopedEnumeration>();

        test_is_not_derived_from<void, void>();
        test_is_not_derived_from<int, int>();
    }
    { // Nothing should be derived from a fundamental type
        test_is_not_derived_from<Enumeration, int>();
        test_is_not_derived_from<ScopedEnumeration, int>();

        test_is_not_derived_from<Base1, int>();
        test_is_not_derived_from<Base1, double>();
        test_is_not_derived_from<Derived1, char>();
        test_is_not_derived_from<DerivedPrivate, long long>();
    }
    { // Other built-in things shouldn't have derivations
        test_is_not_derived_from<Enumeration, Enumeration>();
        test_is_not_derived_from<ScopedEnumeration, ScopedEnumeration>();

        test_is_not_derived_from<Enumeration, ScopedEnumeration>();
        test_is_not_derived_from<ScopedEnumeration, Enumeration>();

        test_is_not_derived_from<Base1[5], Base1>();
        test_is_not_derived_from<Derived1[5], Base1>();

        test_is_not_derived_from<Base1, Base1[5]>();
        test_is_not_derived_from<Derived1, Base1[5]>();
    }

    { // Base1 is the subject.
        test_is_derived_from<Base1, Base1>();

        test_is_not_derived_from<Base1, void>();
        test_is_not_derived_from<Base1, DerivedPrivate>();
        test_is_not_derived_from<Base1, DerivedProtected>();
        test_is_not_derived_from<Base1, Derived1>();
        test_is_not_derived_from<Base1, Derived2>();
        test_is_not_derived_from<Base1, Derived3>();
        test_is_not_derived_from<Base1, Derived4>();
    }

    { // Derived1 is the subject.
        test_is_derived_from<Derived1, Base1>();
        test_is_derived_from<Derived1, Derived1>();

        //test_is_not_derived_from_pointer<Derived1, void>();
        test_is_not_derived_from<Derived1, DerivedPrivate>();
        test_is_not_derived_from<Derived1, DerivedProtected>();
        test_is_not_derived_from<Derived1, Derived2>();
        test_is_not_derived_from<Derived1, Derived3>();
        test_is_not_derived_from<Derived1, Derived4>();
    }

    { // Derived2 is the subject.
        test_is_derived_from<Derived2, Base1>();
        test_is_derived_from<Derived2, Derived2>();

        test_is_not_derived_from<Derived2, DerivedPrivate>();
        test_is_not_derived_from<Derived2, DerivedProtected>();
        test_is_not_derived_from<Derived2, Derived1>();
        test_is_not_derived_from<Derived2, Derived3>();
        test_is_not_derived_from<Derived2, Derived4>();
    }

    { // DerivedPrivate is the subject.
        test_is_derived_from<DerivedPrivate, DerivedPrivate>();

        test_is_not_derived_from<DerivedPrivate, Base1>();
        test_is_not_derived_from<DerivedPrivate, DerivedProtected>();
        test_is_not_derived_from<DerivedPrivate, Derived1>();
        test_is_not_derived_from<DerivedPrivate, Derived2>();
        test_is_not_derived_from<DerivedPrivate, Derived3>();
        test_is_not_derived_from<DerivedPrivate, Derived4>();
    }

    { // Derived3 is the subject.
        test_is_derived_from<Derived3, DerivedPrivate>();
        test_is_derived_from<Derived3, Derived3>();

        test_is_not_derived_from<Derived3, Base1>();
        test_is_not_derived_from<Derived3, DerivedProtected>();
        test_is_not_derived_from<Derived3, Derived1>();
        test_is_not_derived_from<Derived3, Derived2>();
        test_is_not_derived_from<Derived3, Derived4>();
    }

    { // DerivedProtected is the subject.
        test_is_derived_from<DerivedProtected, DerivedProtected>();

        //test_is_not_derived_from_pointer<DerivedProtected, Base1>();
        //test_is_not_derived_from_pointer<DerivedProtected, DerivedPrivate>();
        //test_is_not_derived_from_pointer<DerivedProtected, Derived1>();
        //test_is_not_derived_from_pointer<DerivedProtected, Derived2>();
        //test_is_not_derived_from_pointer<DerivedProtected, Derived3>();
        //test_is_not_derived_from_pointer<DerivedProtected, Derived4>();
    }

    { // Derived4 is the subject.
        test_is_derived_from<Derived4, DerivedProtected>();
        test_is_derived_from<Derived4, Derived4>();

        test_is_not_derived_from<Derived4, Base1>();
        test_is_not_derived_from<Derived4, DerivedPrivate>();
        test_is_not_derived_from<Derived4, Derived1>();
        test_is_not_derived_from<Derived4, Derived2>();
        test_is_not_derived_from<Derived4, Derived3>();
    }

    { // Derived5 is the subject.
        test_is_derived_from<Derived5, DerivedProtected>();
        test_is_derived_from<Derived5, Derived4>();
        test_is_derived_from<Derived5, Derived5>();

        test_is_not_derived_from<Derived5, Base1>();
        test_is_not_derived_from<Derived5, DerivedPrivate>();
        test_is_not_derived_from<Derived5, Derived1>();
        test_is_not_derived_from<Derived5, Derived2>();
        test_is_not_derived_from<Derived5, Derived3>();
    }
}
