#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/core/observer_ptr.hpp>
#include <type_traits>

TEST_CASE("observer_ptr", "[Core][observer_ptr]")
{
    SECTION("Type aliases")
    {
        STATIC_REQUIRE(
                std::is_same<phi::observer_ptr<int>::this_type, phi::observer_ptr<int>>::value);
        STATIC_REQUIRE(std::is_same<phi::observer_ptr<int>::not_null_type,
                                    phi::not_null_observer_ptr<int>>::value);
        STATIC_REQUIRE(std::is_same<phi::observer_ptr<int>::value_type, int>::value);
        STATIC_REQUIRE(std::is_same<phi::observer_ptr<int>::reference, int&>::value);
        STATIC_REQUIRE(std::is_same<phi::observer_ptr<int>::const_reference, const int&>::value);
        STATIC_REQUIRE(std::is_same<phi::observer_ptr<int>::pointer, int*>::value);
        STATIC_REQUIRE(std::is_same<phi::observer_ptr<int>::const_pointer, const int*>::value);
    }

    SECTION("observer_ptr()")
    {
        CONSTEXPR_RUNTIME phi::observer_ptr<int> ptr;

        STATIC_REQUIRE_FALSE(ptr);
        STATIC_REQUIRE(ptr.get() == nullptr);
    }

    SECTION("observer_ptr(std::nullptr_t)")
    {
        CONSTEXPR_RUNTIME phi::observer_ptr<int> ptr(nullptr);

        STATIC_REQUIRE_FALSE(ptr);
        STATIC_REQUIRE(ptr.get() == nullptr);
    }

    SECTION("observer_ptr(TypeT*)")
    {
        int                    i = 22;
        phi::observer_ptr<int> ptr(&i);

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 22);
    }

    SECTION("observer_ptr(const observer_ptr&)")
    {
        int                    i = 21;
        phi::observer_ptr<int> ptr1(&i);
        phi::observer_ptr<int> ptr2(ptr1);

        CHECK(ptr2);
        CHECK(ptr2.get() == &i);
        CHECK(ptr2.get() == ptr1.get());
        CHECK(*ptr2 == 21);
    }

    SECTION("observer_ptr(observer_ptr&&)")
    {
        int                    i = 19;
        phi::observer_ptr<int> ptr{phi::observer_ptr<int>(&i)};

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 19);
    }

    SECTION("observer_ptr(const not_null_observer_ptr&)")
    {
        int                             i = 66;
        phi::not_null_observer_ptr<int> not_null(&i);

        phi::observer_ptr<int> ptr(not_null);

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 66);
    }

    SECTION("observer_ptr(not_null_observer_ptr&&)")
    {
        int                    i = 25;
        phi::observer_ptr<int> ptr{phi::not_null_observer_ptr<int>(&i)};

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 25);
    }

    SECTION("operator=(const observer_ptr&)")
    {
        int                    i = 16;
        phi::observer_ptr<int> base(&i);

        phi::observer_ptr<int> other = base;

        CHECK(other);
        CHECK(other.get() == &i);
        CHECK(other.get() == base.get());
        CHECK(*other == 16);
    }

    SECTION("operator=(observer_ptr&&)")
    {
        int                    i = 29;
        phi::observer_ptr<int> ptr;

        ptr = phi::observer_ptr<int>(&i);

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 29);
    }

    SECTION("operator=(const not_null_observer_ptr&)")
    {
        int                             i = 93;
        phi::not_null_observer_ptr<int> not_null(&i);

        phi::observer_ptr<int> ptr = not_null;

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 93);
    }

    SECTION("operator=(not_null_observer_ptr&&)")
    {
        int                    i   = 92;
        phi::observer_ptr<int> ptr = phi::not_null_observer_ptr<int>(&i);

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 92);
    }

    SECTION("operator=(std::nullptr_t)")
    {
        int                    i = 8;
        phi::observer_ptr<int> ptr(&i);

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("operator=(TypeT*)")
    {
        int i = 23;

        phi::observer_ptr<int> ptr;

        ptr = &i;

        CHECK(ptr);
        CHECK(ptr.get() == &i);
        CHECK(*ptr == 23);
    }

    SECTION("operator bool")
    {
        int                    i = 99;
        phi::observer_ptr<int> true_ptr(&i);
        phi::observer_ptr<int> false_ptr(nullptr);

        CHECK(true_ptr);
        CHECK_FALSE(false_ptr);
    }

    SECTION("operator boolean")
    {
        int                    i = 77;
        phi::observer_ptr<int> true_ptr(&i);
        phi::observer_ptr<int> false_ptr(nullptr);

        CHECK(static_cast<phi::boolean>(true_ptr));
        CHECK_FALSE(static_cast<phi::boolean>(false_ptr));
    }

    SECTION("operator TypeT*")
    {
        int                    i = 55;
        phi::observer_ptr<int> ptr(&i);

        CHECK(static_cast<int*>(ptr) == &i);
    }

    SECTION("get")
    {
        int                    i = 42;
        phi::observer_ptr<int> ptr;

        CHECK(ptr.get() == nullptr);

        ptr = &i;

        CHECK(ptr.get() == &i);
    }

    SECTION("release")
    {
        int                    i = 25;
        phi::observer_ptr<int> ptr(&i);

        int* i_ptr = ptr.release();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        REQUIRE(i_ptr);
        CHECK(i_ptr == &i);
    }

    SECTION("release_not_null")
    {
        int                    i = 63;
        phi::observer_ptr<int> ptr(&i);

        phi::not_null_observer_ptr<int> not_null = ptr.release_not_null();

        CHECK(not_null.get() == &i);
        CHECK(*not_null == 63);
    }

    SECTION("reset")
    {
        int                    i = 19;
        int                    j = 666;
        phi::observer_ptr<int> ptr(&i);

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

        phi::observer_ptr<int> p1 = &i;
        phi::observer_ptr<int> p2 = &j;

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

        phi::observer_ptr<int> p1 = &i;
        phi::observer_ptr<int> p2 = &j;
        phi::observer_ptr<int> p3 = &k;

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

        phi::observer_ptr<int> p1 = &i;
        phi::observer_ptr<int> p2 = &j;
        phi::observer_ptr<int> p3 = &k;

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

    SECTION("operator== not_null_observer_ptr")
    {
        int i = 5;
        int j = 7;

        phi::observer_ptr<int>          null;
        phi::observer_ptr<int>          ptr(&i);
        phi::not_null_observer_ptr<int> not_null(&j);

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

    SECTION("operator!= not_null_observer_ptr")
    {
        int i = 5;
        int j = 7;

        phi::observer_ptr<int>          null;
        phi::observer_ptr<int>          ptr(&i);
        phi::not_null_observer_ptr<int> not_null(&j);

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
        std::size_t null_hash = std::hash<phi::observer_ptr<int>>{}(nullptr);
        std::size_t i_hash    = std::hash<phi::observer_ptr<int>>{}(&i);

        CHECK(null_hash != i_hash);
        CHECK(null_hash == std::hash<int*>{}(nullptr));
        CHECK(i_hash == std::hash<int*>{}(&i));
    }
}

TEST_CASE("not_null_observer_ptr", "[Core][observer_ptr][NotNullnot_null_observer_ptr]")
{
    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same<phi::not_null_observer_ptr<int>::this_type,
                                    phi::not_null_observer_ptr<int>>::value);
        STATIC_REQUIRE(std::is_same<phi::not_null_observer_ptr<int>::value_type, int>::value);
        STATIC_REQUIRE(std::is_same<phi::not_null_observer_ptr<int>::reference, int&>::value);
        STATIC_REQUIRE(
                std::is_same<phi::not_null_observer_ptr<int>::const_reference, const int&>::value);
        STATIC_REQUIRE(std::is_same<phi::not_null_observer_ptr<int>::pointer, int*>::value);
        STATIC_REQUIRE(
                std::is_same<phi::not_null_observer_ptr<int>::const_pointer, const int*>::value);
    }

    SECTION("not_null_observer_ptr(TypeT*)")
    {
        int                             i = 22;
        phi::not_null_observer_ptr<int> ptr(&i);

        CHECK(ptr.get() == &i);
        CHECK(*ptr == 22);
    }

    SECTION("not_null_observer_ptr(const not_null_observer_ptr&)")
    {
        int                             i = 21;
        phi::not_null_observer_ptr<int> ptr1(&i);
        phi::not_null_observer_ptr<int> ptr2(ptr1);

        CHECK(ptr2.get() == &i);
        CHECK(ptr2.get() == ptr1.get());
        CHECK(*ptr2 == 21);
    }

    SECTION("not_null_observer_ptr(not_null_observer_ptr&&)")
    {
        int                             i = 19;
        phi::not_null_observer_ptr<int> ptr{phi::not_null_observer_ptr<int>(&i)};

        CHECK(ptr.get() == &i);
        CHECK(*ptr == 19);
    }

    SECTION("operator=(const not_null_observer_ptr&)")
    {
        int                             i = 16;
        phi::not_null_observer_ptr<int> base(&i);

        phi::not_null_observer_ptr<int> other = base;

        CHECK(other.get() == &i);
        CHECK(other.get() == base.get());
        CHECK(*other == 16);
    }

    SECTION("operator=(not_null_observer_ptr&&)")
    {
        int                             i = 29;
        int                             j = 17;
        phi::not_null_observer_ptr<int> ptr(&i);

        ptr = phi::not_null_observer_ptr<int>(&j);

        CHECK(ptr.get() == &j);
        CHECK(*ptr == 17);
    }

    SECTION("operator=(TypeT*)")
    {
        int i = 11;
        int j = 23;

        phi::not_null_observer_ptr<int> ptr(&i);

        ptr = &j;

        CHECK(ptr.get() == &j);
        CHECK(*ptr == 23);
    }

    SECTION("operator TypeT*")
    {
        int                             i = 55;
        phi::not_null_observer_ptr<int> ptr(&i);

        CHECK(static_cast<int*>(ptr) == &i);
    }

    SECTION("get")
    {
        int                             i = 42;
        phi::not_null_observer_ptr<int> ptr(&i);

        CHECK(ptr.get() == &i);
    }

    SECTION("reset")
    {
        int                             i = 19;
        int                             j = 666;
        phi::not_null_observer_ptr<int> ptr(&i);

        ptr.reset(&j);

        CHECK(ptr.get() == &j);
        CHECK(*ptr == 666);
    }

    SECTION("swap")
    {
        int i = 1;
        int j = 2;

        phi::not_null_observer_ptr<int> p1 = &i;
        phi::not_null_observer_ptr<int> p2 = &j;

        p1.swap(p2);

        CHECK(p1.get() == &j);
        CHECK(p2.get() == &i);
    }

    SECTION("operator==")
    {
        int i = 1;
        int j = 2;
        int k = 3;

        phi::not_null_observer_ptr<int> p1 = &i;
        phi::not_null_observer_ptr<int> p2 = &j;
        phi::not_null_observer_ptr<int> p3 = &k;

        CHECK(p1 == p1);
        CHECK(p2 == p2);
        CHECK(p3 == p3);

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

        phi::not_null_observer_ptr<int> p1 = &i;
        phi::not_null_observer_ptr<int> p2 = &j;
        phi::not_null_observer_ptr<int> p3 = &k;

        CHECK_FALSE(p1 != p1);
        CHECK_FALSE(p2 != p2);
        CHECK_FALSE(p3 != p3);

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
        std::size_t i_hash = std::hash<phi::not_null_observer_ptr<int>>{}(&i);
        std::size_t j_hash = std::hash<phi::not_null_observer_ptr<int>>{}(&j);

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
