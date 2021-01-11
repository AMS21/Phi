#include <catch2/catch_test_macros.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Core/ObserverPtr.hpp>
#include <type_traits>

TEST_CASE("ObserverPtr", "[Core][ObserverPtr]")
{
    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same_v<phi::ObserverPtr<int>::this_type, phi::ObserverPtr<int>>);
        STATIC_REQUIRE(std::is_same_v<phi::ObserverPtr<int>::value_type, int>);
        STATIC_REQUIRE(std::is_same_v<phi::ObserverPtr<int>::reference, int&>);
        STATIC_REQUIRE(std::is_same_v<phi::ObserverPtr<int>::const_reference, const int&>);
        STATIC_REQUIRE(std::is_same_v<phi::ObserverPtr<int>::pointer, int*>);
        STATIC_REQUIRE(std::is_same_v<phi::ObserverPtr<int>::const_pointer, const int*>);
    }

    SECTION("ObserverPtr()")
    {
        CONSTEXPR_RUNTIME phi::ObserverPtr<int> ptr;

        STATIC_REQUIRE_FALSE(ptr);
        STATIC_REQUIRE(ptr.get() == nullptr);
    }

    SECTION("ObserverPtr(std::nullptr_t)")
    {
        CONSTEXPR_RUNTIME phi::ObserverPtr<int> ptr(nullptr);

        STATIC_REQUIRE_FALSE(ptr);
        STATIC_REQUIRE(ptr.get() == nullptr);
    }

    SECTION("ObserverPtr(TypeT*)")
    {
        int                   i = 22;
        phi::ObserverPtr<int> ptr(&i);

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 22);
    }

    SECTION("ObserverPtr(const ObserverPtr&)")
    {
        int                   i = 21;
        phi::ObserverPtr<int> ptr1(&i);
        phi::ObserverPtr<int> ptr2(ptr1);

        CHECK(ptr2);
        CHECK(ptr2.get() == &i);
        CHECK(ptr2.get() == ptr1.get());
        CHECK(*ptr2 == 21);
    }

    SECTION("ObserverPtr(ObserverPtr&&)")
    {
        int                   i = 19;
        phi::ObserverPtr<int> ptr{phi::ObserverPtr<int>(&i)};

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 19);
    }

    SECTION("operator=(const ObserverPtr&)")
    {
        int                   i = 16;
        phi::ObserverPtr<int> base(&i);

        phi::ObserverPtr<int> other = base;

        CHECK(other);
        CHECK(other.get() == &i);
        CHECK(other.get() == base.get());
        CHECK(*other == 16);
    }

    SECTION("operator=(ObserverPtr&&)")
    {
        int                   i = 29;
        phi::ObserverPtr<int> ptr;

        ptr = phi::ObserverPtr<int>(&i);

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 29);
    }

    SECTION("operator=(std::nullptr_t)")
    {
        int                   i = 8;
        phi::ObserverPtr<int> ptr(&i);

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("operator=(TypeT*)")
    {
        int i = 23;

        phi::ObserverPtr<int> ptr;

        ptr = &i;

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 23);
    }

    SECTION("operator bool")
    {
        int                   i = 99;
        phi::ObserverPtr<int> true_ptr(&i);
        phi::ObserverPtr<int> false_ptr(nullptr);

        CHECK(true_ptr);
        CHECK_FALSE(false_ptr);
    }

    SECTION("operator Boolean")
    {
        int                   i = 77;
        phi::ObserverPtr<int> true_ptr(&i);
        phi::ObserverPtr<int> false_ptr(nullptr);

        CHECK(static_cast<phi::Boolean>(true_ptr));
        CHECK_FALSE(static_cast<phi::Boolean>(false_ptr));
    }

    SECTION("operator TypeT*")
    {
        int                   i = 55;
        phi::ObserverPtr<int> ptr(&i);

        CHECK(static_cast<int*>(ptr) == &i);
    }

    SECTION("get")
    {
        int                   i = 42;
        phi::ObserverPtr<int> ptr;

        CHECK(ptr.get() == nullptr);

        ptr = &i;

        CHECK(ptr.get() == &i);
    }

    SECTION("release")
    {
        int                   i = 25;
        phi::ObserverPtr<int> ptr(&i);

        int* i_ptr = ptr.release();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        REQUIRE(i_ptr);
        CHECK(i_ptr == &i);
    }

    SECTION("reset")
    {
        int                   i = 19;
        int                   j = 666;
        phi::ObserverPtr<int> ptr(&i);

        ptr.reset();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr.reset(&j);

        REQUIRE(ptr);
        CHECK(ptr.get() == &j);
        CHECK(*ptr == 666);
    }

    SECTION("swap")
    {
        int i = 1;
        int j = 2;

        phi::ObserverPtr<int> p1 = &i;
        phi::ObserverPtr<int> p2 = &j;

        p1.swap(p2);

        REQUIRE(p1);
        REQUIRE(p2);
        CHECK(p1.get() == &j);
        CHECK(p2.get() == &i);
    }

    SECTION("operator==")
    {
        int i = 1;
        int j = 2;
        int k = 3;

        phi::ObserverPtr<int> p1 = &i;
        phi::ObserverPtr<int> p2 = &j;
        phi::ObserverPtr<int> p3 = &k;

        CHECK(p1 == p1);
        CHECK(p2 == p2);
        CHECK(p3 == p3);

        CHECK_FALSE(p1 == nullptr);
        CHECK_FALSE(p2 == nullptr);
        CHECK_FALSE(p3 == nullptr);
        CHECK_FALSE(nullptr == p1);
        CHECK_FALSE(nullptr == p2);
        CHECK_FALSE(nullptr == p3);

        CHECK_FALSE(p1 == p2);
        CHECK_FALSE(p1 == p3);
        CHECK_FALSE(p2 == p3);

        p2 = &k;

        CHECK_FALSE(p1 == p2);
        CHECK_FALSE(p1 == p3);
        CHECK(p2 == p3);

        p1 = nullptr;

        CHECK(p1 == nullptr);
        CHECK(nullptr == p1);

        CHECK_FALSE(p1 == p2);
        CHECK_FALSE(p1 == p3);

        p3.reset();

        CHECK(p1 == p3);
    }

    SECTION("operator!=")
    {
        int i = 1;
        int j = 2;
        int k = 3;

        phi::ObserverPtr<int> p1 = &i;
        phi::ObserverPtr<int> p2 = &j;
        phi::ObserverPtr<int> p3 = &k;

        CHECK_FALSE(p1 != p1);
        CHECK_FALSE(p2 != p2);
        CHECK_FALSE(p3 != p3);

        CHECK(p1 != nullptr);
        CHECK(p2 != nullptr);
        CHECK(p3 != nullptr);
        CHECK(nullptr != p1);
        CHECK(nullptr != p2);
        CHECK(nullptr != p3);

        CHECK(p1 != p2);
        CHECK(p1 != p3);
        CHECK(p2 != p3);

        p2 = &k;

        CHECK(p1 != p2);
        CHECK(p1 != p3);
        CHECK_FALSE(p2 != p3);

        p1 = nullptr;

        CHECK_FALSE(p1 != nullptr);
        CHECK_FALSE(nullptr != p1);

        CHECK(p1 != p2);
        CHECK(p1 != p3);

        p3.reset();

        CHECK_FALSE(p1 != p3);
    }

    SECTION("hash")
    {
        int         i         = 62;
        std::size_t null_hash = std::hash<phi::ObserverPtr<int>>{}(nullptr);
        std::size_t i_hash    = std::hash<phi::ObserverPtr<int>>{}(&i);

        CHECK(null_hash != i_hash);
        CHECK(null_hash == std::hash<int*>{}(nullptr));
        CHECK(i_hash == std::hash<int*>{}(&i));
    }
}

TEST_CASE("make_observer")
{
    int i = 23;

    auto ptr = phi::make_observer(&i);

    CHECK(ptr);
    CHECK(ptr.get() == &i);
}
