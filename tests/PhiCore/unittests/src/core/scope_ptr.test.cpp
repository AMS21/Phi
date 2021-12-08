#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include "phi/compiler_support/warning.hpp"
#include <phi/core/scope_ptr.hpp>
#include <phi/math/vector2.hpp>
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

TEST_CASE("scope_ptr", "[Core][scope_ptr]")
{
    // scope_ptr
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::scope_ptr<int>) == sizeof(int*));

        STATIC_REQUIRE(std::is_default_constructible<phi::scope_ptr<int>>::value);
        STATIC_REQUIRE_FALSE(std::is_copy_constructible<phi::scope_ptr<int>>::value);
        STATIC_REQUIRE(std::is_move_constructible<phi::scope_ptr<int>>::value);
        STATIC_REQUIRE_FALSE(std::is_copy_assignable<phi::scope_ptr<int>>::value);
        STATIC_REQUIRE(std::is_move_assignable<phi::scope_ptr<int>>::value);
    }

    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same<phi::scope_ptr<int>::this_type, phi::scope_ptr<int>>::value);
        STATIC_REQUIRE(std::is_same<phi::scope_ptr<int>::value_type, int>::value);
        STATIC_REQUIRE(std::is_same<phi::scope_ptr<int>::reference, int&>::value);
        STATIC_REQUIRE(std::is_same<phi::scope_ptr<int>::const_reference, const int&>::value);
        STATIC_REQUIRE(std::is_same<phi::scope_ptr<int>::pointer, int*>::value);
        STATIC_REQUIRE(std::is_same<phi::scope_ptr<int>::const_pointer, const int*>::value);
    }

    SECTION("scope_ptr()")
    {
        phi::scope_ptr<int> ptr;

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("scope_ptr(std::nullptr_t)")
    {
        phi::scope_ptr<int> ptr(nullptr);

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("scope_ptr(TypeT*)")
    {
        int*                raw_ptr = new int(23);
        phi::scope_ptr<int> ptr(raw_ptr);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(*ptr == 23);

        *raw_ptr = 19;

        CHECK(*ptr == 19);
    }

    SECTION("scope_ptr(scope_ptr&&)")
    {
        int* raw_ptr = new int(21);

        phi::scope_ptr<int> base(raw_ptr);
        phi::scope_ptr<int> ptr(std::move(base));

        CHECK_FALSE(base);
        CHECK(base.get() == nullptr);
        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("scope_ptr(not_null_scope_ptr&&)")
    {
        int* raw_ptr = new int(33);

        phi::not_null_scope_ptr<int> not_null(raw_ptr);
        phi::scope_ptr<int>          ptr(std::move(not_null));

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("operator=(scope_ptr&&)")
    {
        int* raw_ptr = new int(16);

        phi::scope_ptr<int> base(raw_ptr);
        phi::scope_ptr<int> ptr;

        ptr = std::move(base);

        CHECK_FALSE(base);
        CHECK(base.get() == nullptr);
        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(12);

        phi::scope_ptr<int> ptr2(raw_ptr2);

        ptr = std::move(ptr2);

        CHECK_FALSE(ptr2);
        CHECK(ptr2.get() == nullptr);
        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(not_null_scope_ptr&&)")
    {
        int* raw_ptr = new int(21);

        phi::not_null_scope_ptr<int> not_null(raw_ptr);
        phi::scope_ptr<int>          ptr;

        ptr = std::move(not_null);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("scope_ptr(TypeT*)")
    {
        int* raw_ptr = new int(21);

        phi::scope_ptr<int> ptr;

        ptr = raw_ptr;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(22);

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("scope_ptr(std::nullptr_t)")
    {
        phi::scope_ptr<int> ptr;

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
        phi::scope_ptr<int> ptr(new int(25));

        ptr.clear();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("leak_ptr")
    {
        int*                raw_ptr = new int(16);
        phi::scope_ptr<int> ptr(raw_ptr);

        int* leaked_ptr = ptr.leak_ptr();

        CHECK(leaked_ptr == raw_ptr);
        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        delete leaked_ptr;
    }

    SECTION("release_not_null")
    {
        int*                raw_ptr = new int(21);
        phi::scope_ptr<int> ptr(raw_ptr);

        phi::not_null_scope_ptr<int> not_null = ptr.release_not_null();

        CHECK(not_null.get() == raw_ptr);
    }

    SECTION("reset")
    {
        phi::scope_ptr<int> ptr(new int(99));
        int*                raw_ptr = new int(1);

        ptr.reset(raw_ptr);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("swap")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);

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

    SECTION("operator boolean")
    {
        phi::scope_ptr<int> false_ptr;
        phi::scope_ptr<int> true_ptr(new int(9));

        CHECK_FALSE(static_cast<phi::boolean>(false_ptr));
        CHECK(static_cast<phi::boolean>(true_ptr));
    }

    SECTION("operator TypeT*")
    {
        int*                raw_ptr = new int(12);
        phi::scope_ptr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);

        CHECK(new_ptr == raw_ptr);
    }

    SECTION("operator->")
    {
        phi::scope_ptr<A> ptr(new A);

        CHECK(ptr->f());
    }

    SECTION("operator*")
    {
        int*                raw_ptr = new int(0);
        phi::scope_ptr<int> ptr(raw_ptr);

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

        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);
        phi::scope_ptr<int> null;

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

        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);
        phi::scope_ptr<int> null;

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
        phi::scope_ptr<int> int_ptr  = phi::make_scope<int>();
        phi::scope_ptr<int> int_ptr2 = phi::make_scope<int>(3);

        CHECK(*int_ptr2 == 3);

        phi::scope_ptr<phi::vector2i32> vec2_ptr = phi::make_scope<phi::vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }

    // not_null_scope_ptr
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::not_null_scope_ptr<int>) == sizeof(int*));

        STATIC_REQUIRE_FALSE(std::is_default_constructible<phi::not_null_scope_ptr<int>>::value);
        STATIC_REQUIRE_FALSE(std::is_copy_constructible<phi::not_null_scope_ptr<int>>::value);
        STATIC_REQUIRE(std::is_move_constructible<phi::not_null_scope_ptr<int>>::value);
        STATIC_REQUIRE_FALSE(std::is_copy_assignable<phi::not_null_scope_ptr<int>>::value);
        STATIC_REQUIRE(std::is_move_assignable<phi::not_null_scope_ptr<int>>::value);
    }

    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same<phi::not_null_scope_ptr<int>::this_type,
                                    phi::not_null_scope_ptr<int>>::value);
        STATIC_REQUIRE(std::is_same<phi::not_null_scope_ptr<int>::value_type, int>::value);
        STATIC_REQUIRE(std::is_same<phi::not_null_scope_ptr<int>::reference, int&>::value);
        STATIC_REQUIRE(
                std::is_same<phi::not_null_scope_ptr<int>::const_reference, const int&>::value);
        STATIC_REQUIRE(std::is_same<phi::not_null_scope_ptr<int>::pointer, int*>::value);
        STATIC_REQUIRE(
                std::is_same<phi::not_null_scope_ptr<int>::const_pointer, const int*>::value);
    }

    SECTION("not_null_scope_ptr(TypeT*)")
    {
        int*                         raw_ptr = new int(23);
        phi::not_null_scope_ptr<int> ptr(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
        CHECK(*ptr == 23);

        *raw_ptr = 19;

        CHECK(*ptr == 19);
    }

    SECTION("not_null_scope_ptr(not_null_scope_ptr&&)")
    {
        int* raw_ptr = new int(21);

        phi::not_null_scope_ptr<int> base(raw_ptr);
        phi::not_null_scope_ptr<int> ptr(std::move(base));

        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("operator=(not_null_scope_ptr&&)")
    {
        int* raw_ptr = new int(16);

        phi::not_null_scope_ptr<int> base(raw_ptr);
        phi::not_null_scope_ptr<int> ptr(new int(12));

        ptr = std::move(base);

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(12);

        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);

        ptr = std::move(ptr2);

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("not_null_scope_ptr(TypeT*)")
    {
        int* raw_ptr = new int(21);

        phi::not_null_scope_ptr<int> ptr(new int(23));

        ptr = raw_ptr;

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(22);

        ptr = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("leak_ptr")
    {
        int*                         raw_ptr = new int(16);
        phi::not_null_scope_ptr<int> ptr(raw_ptr);

        int* leaked_ptr = ptr.leak_ptr();

        CHECK(leaked_ptr == raw_ptr);

        delete leaked_ptr;
    }

    SECTION("reset")
    {
        phi::not_null_scope_ptr<int> ptr(new int(99));
        int*                         raw_ptr = new int(1);

        ptr.reset(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("swap")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::not_null_scope_ptr<int> ptr1(raw_ptr1);
        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);

        ptr1.swap(ptr2);

        CHECK(ptr1.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr1);

        phi::swap(ptr1, ptr2);

        CHECK(ptr1.get() == raw_ptr1);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("operator TypeT*")
    {
        int*                         raw_ptr = new int(12);
        phi::not_null_scope_ptr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);

        CHECK(new_ptr == raw_ptr);
    }

    SECTION("operator->")
    {
        phi::not_null_scope_ptr<A> ptr(new A);

        CHECK(ptr->f());
    }

    SECTION("operator*")
    {
        int*                         raw_ptr = new int(0);
        phi::not_null_scope_ptr<int> ptr(raw_ptr);

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

        phi::not_null_scope_ptr<int> ptr1(raw_ptr1);
        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);
        phi::not_null_scope_ptr<int> ptr3(raw_ptr3);

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

        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);
        phi::scope_ptr<int> ptr3(raw_ptr3);

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
        phi::not_null_scope_ptr<int> int_ptr  = phi::make_not_null_scope<int>();
        phi::not_null_scope_ptr<int> int_ptr2 = phi::make_not_null_scope<int>(3);

        CHECK(*int_ptr2 == 3);

        phi::not_null_scope_ptr<phi::vector2i32> vec2_ptr =
                phi::make_not_null_scope<phi::vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
