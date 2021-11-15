#include <catch2/catch.hpp>

#include "ConstexprHelper.hpp"
#include "Phi/Config/Warning.hpp"
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/Math/Vector2.hpp>
#include <type_traits>

struct A
{
    bool f()
    {
        return true;
    }
};

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

TEST_CASE("ScopePtr", "[Core][ScopePtr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::ScopePtr<int>) == sizeof(int*));

        STATIC_REQUIRE(std::is_default_constructible<phi::ScopePtr<int>>::value);
        STATIC_REQUIRE_FALSE(std::is_copy_constructible<phi::ScopePtr<int>>::value);
        STATIC_REQUIRE(std::is_move_constructible<phi::ScopePtr<int>>::value);
        STATIC_REQUIRE_FALSE(std::is_copy_assignable<phi::ScopePtr<int>>::value);
        STATIC_REQUIRE(std::is_move_assignable<phi::ScopePtr<int>>::value);
    }

    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same<phi::ScopePtr<int>::this_type, phi::ScopePtr<int>>::value);
        STATIC_REQUIRE(std::is_same<phi::ScopePtr<int>::value_type, int>::value);
        STATIC_REQUIRE(std::is_same<phi::ScopePtr<int>::reference, int&>::value);
        STATIC_REQUIRE(std::is_same<phi::ScopePtr<int>::const_reference, const int&>::value);
        STATIC_REQUIRE(std::is_same<phi::ScopePtr<int>::pointer, int*>::value);
        STATIC_REQUIRE(std::is_same<phi::ScopePtr<int>::const_pointer, const int*>::value);
    }

    SECTION("ScopePtr()")
    {
        phi::ScopePtr<int> ptr;

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("ScopePtr(std::nullptr_t)")
    {
        phi::ScopePtr<int> ptr(nullptr);

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("ScopePtr(TypeT*)")
    {
        int*               raw_ptr = new int(23);
        phi::ScopePtr<int> ptr(raw_ptr);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(*ptr == 23);

        *raw_ptr = 19;

        CHECK(*ptr == 19);
    }

    SECTION("ScopePtr(ScopePtr&&)")
    {
        int* raw_ptr = new int(21);

        phi::ScopePtr<int> base(raw_ptr);
        phi::ScopePtr<int> ptr(std::move(base));

        CHECK_FALSE(base);
        CHECK(base.get() == nullptr);
        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("ScopePtr(NotNullScopePtr&&)")
    {
        int* raw_ptr = new int(33);

        phi::NotNullScopePtr<int> not_null(raw_ptr);
        phi::ScopePtr<int>        ptr(std::move(not_null));

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("operator=(ScopePtr&&)")
    {
        int* raw_ptr = new int(16);

        phi::ScopePtr<int> base(raw_ptr);
        phi::ScopePtr<int> ptr;

        ptr = std::move(base);

        CHECK_FALSE(base);
        CHECK(base.get() == nullptr);
        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(12);

        phi::ScopePtr<int> ptr2(raw_ptr2);

        ptr = std::move(ptr2);

        CHECK_FALSE(ptr2);
        CHECK(ptr2.get() == nullptr);
        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(NotNullScopePtr&&)")
    {
        int* raw_ptr = new int(21);

        phi::NotNullScopePtr<int> not_null(raw_ptr);
        phi::ScopePtr<int>        ptr;

        ptr = std::move(not_null);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("ScopePtr(TypeT*)")
    {
        int* raw_ptr = new int(21);

        phi::ScopePtr<int> ptr;

        ptr = raw_ptr;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(22);

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("ScopePtr(std::nullptr_t)")
    {
        phi::ScopePtr<int> ptr;

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr = new int(10);

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("clear")
    {
        phi::ScopePtr<int> ptr(new int(25));

        ptr.clear();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("leak_ptr")
    {
        int*               raw_ptr = new int(16);
        phi::ScopePtr<int> ptr(raw_ptr);

        int* leaked_ptr = ptr.leak_ptr();

        CHECK(leaked_ptr == raw_ptr);
        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        delete leaked_ptr;
    }

    SECTION("release_not_null")
    {
        int*               raw_ptr = new int(21);
        phi::ScopePtr<int> ptr(raw_ptr);

        phi::NotNullScopePtr<int> not_null = ptr.release_not_null();

        CHECK(not_null.get() == raw_ptr);
    }

    SECTION("reset")
    {
        phi::ScopePtr<int> ptr(new int(99));
        int*               raw_ptr = new int(1);

        ptr.reset(raw_ptr);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("swap")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::ScopePtr<int> ptr1(raw_ptr1);
        phi::ScopePtr<int> ptr2(raw_ptr2);

        ptr1.swap(ptr2);

        REQUIRE(ptr1);
        REQUIRE(ptr2);

        CHECK(ptr1.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr1);

        phi::swap(ptr1, ptr2);

        REQUIRE(ptr1);
        REQUIRE(ptr2);

        CHECK(ptr1.get() == raw_ptr1);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("operator Boolean")
    {
        phi::ScopePtr<int> false_ptr;
        phi::ScopePtr<int> true_ptr(new int(9));

        CHECK_FALSE(static_cast<phi::Boolean>(false_ptr));
        CHECK(static_cast<phi::Boolean>(true_ptr));
    }

    SECTION("operator TypeT*")
    {
        int*               raw_ptr = new int(12);
        phi::ScopePtr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);

        CHECK(new_ptr == raw_ptr);
    }

    SECTION("operator->")
    {
        phi::ScopePtr<A> ptr(new A);

        CHECK(ptr->f());
    }

    SECTION("operator*")
    {
        int*               raw_ptr = new int(0);
        phi::ScopePtr<int> ptr(raw_ptr);

        CHECK(*ptr == 0);

        *raw_ptr = 12;

        CHECK(*ptr == 12);

        *ptr = 9;

        CHECK(*ptr == 9);
        CHECK(*raw_ptr == 9);
    }

    SECTION("operator==")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::ScopePtr<int> ptr1(raw_ptr1);
        phi::ScopePtr<int> ptr2(raw_ptr2);
        phi::ScopePtr<int> null;

        CHECK_FALSE(ptr1 == ptr2);
        CHECK_FALSE(ptr1 == null);
        CHECK_FALSE(ptr2 == null);

        CHECK_FALSE(ptr1 == nullptr);
        CHECK_FALSE(ptr2 == nullptr);
        CHECK(null == nullptr);

        CHECK_FALSE(nullptr == ptr1);
        CHECK_FALSE(nullptr == ptr2);
        CHECK(nullptr == null);

        ptr2 = raw_ptr1;

        CHECK(ptr1 == ptr2);

        // Need to leak the pointer otherwise we get a double free
        ptr2.leak_ptr();
    }

    SECTION("operator!=")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::ScopePtr<int> ptr1(raw_ptr1);
        phi::ScopePtr<int> ptr2(raw_ptr2);
        phi::ScopePtr<int> null;

        CHECK(ptr1 != ptr2);
        CHECK(ptr1 != null);
        CHECK(ptr2 != null);

        CHECK(ptr1 != nullptr);
        CHECK(ptr2 != nullptr);
        CHECK_FALSE(null != nullptr);

        CHECK(nullptr != ptr1);
        CHECK(nullptr != ptr2);
        CHECK_FALSE(nullptr != null);

        ptr2 = raw_ptr1;

        CHECK_FALSE(ptr1 != ptr2);

        // Need to leak the pointer otherwise we get a double free
        ptr2.leak_ptr();
    }

    SECTION("make_scope")
    {
        phi::ScopePtr<int> int_ptr  = phi::make_scope<int>();
        phi::ScopePtr<int> int_ptr2 = phi::make_scope<int>(3);

        CHECK(*int_ptr2 == 3);

        phi::ScopePtr<phi::Vector2i32> vec2_ptr = phi::make_scope<phi::Vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }
}

TEST_CASE("NotNullScopePtr", "[Core][ScopePtr][NotNullScopePtr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::NotNullScopePtr<int>) == sizeof(int*));

        STATIC_REQUIRE_FALSE(std::is_default_constructible<phi::NotNullScopePtr<int>>::value);
        STATIC_REQUIRE_FALSE(std::is_copy_constructible<phi::NotNullScopePtr<int>>::value);
        STATIC_REQUIRE(std::is_move_constructible<phi::NotNullScopePtr<int>>::value);
        STATIC_REQUIRE_FALSE(std::is_copy_assignable<phi::NotNullScopePtr<int>>::value);
        STATIC_REQUIRE(std::is_move_assignable<phi::NotNullScopePtr<int>>::value);
    }

    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same<phi::NotNullScopePtr<int>::this_type,
                                    phi::NotNullScopePtr<int>>::value);
        STATIC_REQUIRE(std::is_same<phi::NotNullScopePtr<int>::value_type, int>::value);
        STATIC_REQUIRE(std::is_same<phi::NotNullScopePtr<int>::reference, int&>::value);
        STATIC_REQUIRE(std::is_same<phi::NotNullScopePtr<int>::const_reference, const int&>::value);
        STATIC_REQUIRE(std::is_same<phi::NotNullScopePtr<int>::pointer, int*>::value);
        STATIC_REQUIRE(std::is_same<phi::NotNullScopePtr<int>::const_pointer, const int*>::value);
    }

    SECTION("NotNullScopePtr(TypeT*)")
    {
        int*                      raw_ptr = new int(23);
        phi::NotNullScopePtr<int> ptr(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
        CHECK(*ptr == 23);

        *raw_ptr = 19;

        CHECK(*ptr == 19);
    }

    SECTION("NotNullScopePtr(NotNullScopePtr&&)")
    {
        int* raw_ptr = new int(21);

        phi::NotNullScopePtr<int> base(raw_ptr);
        phi::NotNullScopePtr<int> ptr(std::move(base));

        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("operator=(NotNullScopePtr&&)")
    {
        int* raw_ptr = new int(16);

        phi::NotNullScopePtr<int> base(raw_ptr);
        phi::NotNullScopePtr<int> ptr(new int(12));

        ptr = std::move(base);

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(12);

        phi::NotNullScopePtr<int> ptr2(raw_ptr2);

        ptr = std::move(ptr2);

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("NotNullScopePtr(TypeT*)")
    {
        int* raw_ptr = new int(21);

        phi::NotNullScopePtr<int> ptr(new int(23));

        ptr = raw_ptr;

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(22);

        ptr = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("leak_ptr")
    {
        int*                      raw_ptr = new int(16);
        phi::NotNullScopePtr<int> ptr(raw_ptr);

        int* leaked_ptr = ptr.leak_ptr();

        CHECK(leaked_ptr == raw_ptr);

        delete leaked_ptr;
    }

    SECTION("reset")
    {
        phi::NotNullScopePtr<int> ptr(new int(99));
        int*                      raw_ptr = new int(1);

        ptr.reset(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("swap")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::NotNullScopePtr<int> ptr1(raw_ptr1);
        phi::NotNullScopePtr<int> ptr2(raw_ptr2);

        ptr1.swap(ptr2);

        CHECK(ptr1.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr1);

        phi::swap(ptr1, ptr2);

        CHECK(ptr1.get() == raw_ptr1);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("operator TypeT*")
    {
        int*                      raw_ptr = new int(12);
        phi::NotNullScopePtr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);

        CHECK(new_ptr == raw_ptr);
    }

    SECTION("operator->")
    {
        phi::NotNullScopePtr<A> ptr(new A);

        CHECK(ptr->f());
    }

    SECTION("operator*")
    {
        int*                      raw_ptr = new int(0);
        phi::NotNullScopePtr<int> ptr(raw_ptr);

        CHECK(*ptr == 0);

        *raw_ptr = 12;

        CHECK(*ptr == 12);

        *ptr = 9;

        CHECK(*ptr == 9);
        CHECK(*raw_ptr == 9);
    }

    SECTION("operator==")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);
        int* raw_ptr3 = new int(3);

        phi::NotNullScopePtr<int> ptr1(raw_ptr1);
        phi::NotNullScopePtr<int> ptr2(raw_ptr2);
        phi::NotNullScopePtr<int> ptr3(raw_ptr3);

        CHECK_FALSE(ptr1 == ptr2);
        CHECK_FALSE(ptr1 == ptr3);
        CHECK_FALSE(ptr2 == ptr3);

        ptr2 = raw_ptr1;

        CHECK(ptr1 == ptr2);

        // Need to leak the pointer otherwise we get a double free
        ptr2.leak_ptr();
    }

    SECTION("operator!=")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);
        int* raw_ptr3 = new int(3);

        phi::ScopePtr<int> ptr1(raw_ptr1);
        phi::ScopePtr<int> ptr2(raw_ptr2);
        phi::ScopePtr<int> ptr3(raw_ptr3);

        CHECK(ptr1 != ptr2);
        CHECK(ptr1 != ptr3);
        CHECK(ptr2 != ptr3);

        ptr2 = raw_ptr1;

        CHECK_FALSE(ptr1 != ptr2);

        // Need to leak the pointer otherwise we get a double free
        ptr2.leak_ptr();
    }

    SECTION("make_scope")
    {
        phi::NotNullScopePtr<int> int_ptr  = phi::make_not_null_scope<int>();
        phi::NotNullScopePtr<int> int_ptr2 = phi::make_not_null_scope<int>(3);

        CHECK(*int_ptr2 == 3);

        phi::NotNullScopePtr<phi::Vector2i32> vec2_ptr =
                phi::make_not_null_scope<phi::Vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
