#include <catch2/catch_test_macros.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Core/ObserverPtr.hpp>
#include <type_traits>

TEST_CASE("ObserverPtr", "[Core][ObserverPtr]")
{
    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same_v<phi::ObserverPtr<int>::this_type, phi::ObserverPtr<int>>);
        STATIC_REQUIRE(
                std::is_same_v<phi::ObserverPtr<int>::not_null_type, phi::NotNullObserverPtr<int>>);
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

    SECTION("ObserverPtr(const NotNullObserverPtr&)")
    {
        int                          i = 66;
        phi::NotNullObserverPtr<int> not_null(&i);

        phi::ObserverPtr<int> ptr(not_null);

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 66);
    }

    SECTION("ObserverPtr(NotNullObserverPtr&&)")
    {
        int              i = 25;
        phi::ObserverPtr ptr{phi::NotNullObserverPtr<int>(&i)};

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 25);
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

    SECTION("operator=(const NotNullObserverPtr&)")
    {
        int                          i = 93;
        phi::NotNullObserverPtr<int> not_null(&i);

        phi::ObserverPtr<int> ptr = not_null;

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 93);
    }

    SECTION("operator=(NotNullObserverPtr&&)")
    {
        int                   i   = 92;
        phi::ObserverPtr<int> ptr = phi::NotNullObserverPtr<int>(&i);

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 92);
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

    SECTION("release_not_null")
    {
        int                   i = 63;
        phi::ObserverPtr<int> ptr(&i);

        phi::NotNullObserverPtr<int> not_null = ptr.release_not_null();

        CHECK(not_null.get() == &i);
        CHECK(*not_null == 63);
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

    SECTION("operator== NotNullObserverPtr")
    {
        int i = 5;
        int j = 7;

        phi::ObserverPtr<int>        null;
        phi::ObserverPtr<int>        ptr(&i);
        phi::NotNullObserverPtr<int> not_null(&j);

        CHECK_FALSE(null == ptr);
        CHECK_FALSE(null == not_null);
        CHECK_FALSE(ptr == not_null);

        CHECK_FALSE(ptr == null);
        CHECK_FALSE(not_null == null);
        CHECK_FALSE(not_null == ptr);

        ptr = &j;

        CHECK(ptr == not_null);
        CHECK(not_null == ptr);
    }

    SECTION("operator!= NotNullObserverPtr")
    {
        int i = 5;
        int j = 7;

        phi::ObserverPtr<int>        null;
        phi::ObserverPtr<int>        ptr(&i);
        phi::NotNullObserverPtr<int> not_null(&j);

        CHECK(null != ptr);
        CHECK(null != not_null);
        CHECK(ptr != not_null);

        CHECK(ptr != null);
        CHECK(not_null != null);
        CHECK(not_null != ptr);

        ptr = &j;

        CHECK_FALSE(ptr != not_null);
        CHECK_FALSE(not_null != ptr);
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

TEST_CASE("NotNullObserverPtr", "[Core][ObserverPtr][NotNullNotNullObserverPtr]")
{
    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same_v<phi::NotNullObserverPtr<int>::this_type,
                                      phi::NotNullObserverPtr<int>>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullObserverPtr<int>::value_type, int>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullObserverPtr<int>::reference, int&>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullObserverPtr<int>::const_reference, const int&>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullObserverPtr<int>::pointer, int*>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullObserverPtr<int>::const_pointer, const int*>);
    }

    SECTION("NotNullObserverPtr(TypeT*)")
    {
        int                          i = 22;
        phi::NotNullObserverPtr<int> ptr(&i);

        CHECK(ptr.get() == &i);
        CHECK(*ptr == 22);
    }

    SECTION("NotNullObserverPtr(const NotNullObserverPtr&)")
    {
        int                          i = 21;
        phi::NotNullObserverPtr<int> ptr1(&i);
        phi::NotNullObserverPtr<int> ptr2(ptr1);

        CHECK(ptr2.get() == &i);
        CHECK(ptr2.get() == ptr1.get());
        CHECK(*ptr2 == 21);
    }

    SECTION("NotNullObserverPtr(NotNullObserverPtr&&)")
    {
        int                          i = 19;
        phi::NotNullObserverPtr<int> ptr{phi::NotNullObserverPtr<int>(&i)};

        CHECK(ptr.get() == &i);
        CHECK(*ptr == 19);
    }

    SECTION("operator=(const NotNullObserverPtr&)")
    {
        int                          i = 16;
        phi::NotNullObserverPtr<int> base(&i);

        phi::NotNullObserverPtr<int> other = base;

        CHECK(other.get() == &i);
        CHECK(other.get() == base.get());
        CHECK(*other == 16);
    }

    SECTION("operator=(NotNullObserverPtr&&)")
    {
        int                          i = 29;
        int                          j = 17;
        phi::NotNullObserverPtr<int> ptr(&i);

        ptr = phi::NotNullObserverPtr<int>(&j);

        CHECK(ptr);
        CHECK(ptr.get() == &j);
        CHECK(*ptr == 17);
    }

    SECTION("operator=(TypeT*)")
    {
        int i = 11;
        int j = 23;

        phi::NotNullObserverPtr<int> ptr(&i);

        ptr = &j;

        CHECK(ptr);
        CHECK(ptr.get() == &j);
        CHECK(*ptr == 23);
    }

    SECTION("operator bool")
    {
        int                          i = 99;
        phi::NotNullObserverPtr<int> ptr(&i);
        CHECK(ptr);
    }

    SECTION("operator Boolean")
    {
        int                          i = 77;
        phi::NotNullObserverPtr<int> ptr(&i);

        CHECK(static_cast<phi::Boolean>(ptr));
    }

    SECTION("operator TypeT*")
    {
        int                          i = 55;
        phi::NotNullObserverPtr<int> ptr(&i);

        CHECK(static_cast<int*>(ptr) == &i);
    }

    SECTION("get")
    {
        int                          i = 42;
        phi::NotNullObserverPtr<int> ptr(&i);

        CHECK(ptr.get() == &i);
    }

    SECTION("reset")
    {
        int                          i = 19;
        int                          j = 666;
        phi::NotNullObserverPtr<int> ptr(&i);

        ptr.reset(&j);

        REQUIRE(ptr);
        CHECK(ptr.get() == &j);
        CHECK(*ptr == 666);
    }

    SECTION("swap")
    {
        int i = 1;
        int j = 2;

        phi::NotNullObserverPtr<int> p1 = &i;
        phi::NotNullObserverPtr<int> p2 = &j;

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

        phi::NotNullObserverPtr<int> p1 = &i;
        phi::NotNullObserverPtr<int> p2 = &j;
        phi::NotNullObserverPtr<int> p3 = &k;

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
    }

    SECTION("operator!=")
    {
        int i = 1;
        int j = 2;
        int k = 3;

        phi::NotNullObserverPtr<int> p1 = &i;
        phi::NotNullObserverPtr<int> p2 = &j;
        phi::NotNullObserverPtr<int> p3 = &k;

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
    }

    SECTION("hash")
    {
        int         i      = 62;
        int         j      = 14;
        std::size_t i_hash = std::hash<phi::NotNullObserverPtr<int>>{}(&i);
        std::size_t j_hash = std::hash<phi::NotNullObserverPtr<int>>{}(&j);

        CHECK(i_hash != j_hash);
        CHECK(i_hash == std::hash<int*>{}(&i));
        CHECK(j_hash == std::hash<int*>{}(&j));
    }
}

TEST_CASE("make_observer")
{
    int i = 23;

    auto ptr = phi::make_observer(&i);

    CHECK(ptr);
    CHECK(ptr.get() == &i);
}

TEST_CASE("make_not_null_observer")
{
    int i = 23;

    auto ptr = phi::make_not_null_observer(&i);

    CHECK(ptr.get() == &i);
}
