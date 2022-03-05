#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/core/flat_ptr.hpp>
#include <phi/core/move.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <phi/type_traits/is_copy_constructible.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_move_assignable.hpp>
#include <phi/type_traits/is_move_constructible.hpp>

struct A
{
    bool f()
    {
        return true;
    }
};

TEST_CASE("flat_ptr", "[Core][flat_ptr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::flat_ptr) == sizeof(void*));

#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
        STATIC_REQUIRE(phi::is_default_constructible<phi::flat_ptr>::value);
#endif
        STATIC_REQUIRE(phi::is_copy_constructible<phi::flat_ptr>::value);
        STATIC_REQUIRE(phi::is_move_constructible<phi::flat_ptr>::value);
        STATIC_REQUIRE(phi::is_copy_assignable<phi::flat_ptr>::value);
        STATIC_REQUIRE(phi::is_move_assignable<phi::flat_ptr>::value);
    }

    SECTION("Type aliases")
    {
        CHECK_SAME_TYPE(phi::flat_ptr::this_type, phi::flat_ptr);
        CHECK_SAME_TYPE(phi::flat_ptr::value_type, void*);
        CHECK_SAME_TYPE(phi::flat_ptr::not_null_type, phi::not_null_flat_ptr);
    }

    int val1 = 21;
    int val2 = 42;

    int* raw_ptr1 = &val1;
    int* raw_ptr2 = &val2;

    SECTION("flat_ptr()")
    {
        phi::flat_ptr ptr;

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("flat_ptr(nullptr_t)")
    {
        phi::flat_ptr ptr{nullptr};

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("flat_ptr(PtrT*)")
    {
        phi::flat_ptr ptr(raw_ptr1);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("flat_ptr(const flat_ptr&)")
    {
        phi::flat_ptr base(raw_ptr1);
        phi::flat_ptr ptr(base);

        REQUIRE(base);
        REQUIRE(ptr);

        CHECK(ptr.get() == base.get());
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("flat_ptr(flat_ptr&&)")
    {
        phi::flat_ptr base(raw_ptr1);
        phi::flat_ptr ptr(phi::move(base));

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("flat_ptr(const not_null_flat_ptr&)")
    {
        phi::not_null_flat_ptr not_null(raw_ptr1);
        phi::flat_ptr          ptr(not_null);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("flat_ptr(not_null_flat_ptr&&)")
    {
        phi::not_null_flat_ptr not_null(raw_ptr1);
        phi::flat_ptr          ptr(phi::move(not_null));

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("flat_ptr(nullptr_t)")
    {
        phi::flat_ptr ptr;

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr = raw_ptr1;
        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("operator=(const flat_ptr&)")
    {
        phi::flat_ptr base(raw_ptr1);
        phi::flat_ptr ptr;

        ptr = base;

        CHECK(base);
        CHECK(base.get() == raw_ptr1);

        phi::flat_ptr ptr2(raw_ptr2);

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(flat_ptr&&)")
    {
        phi::flat_ptr base(raw_ptr1);
        phi::flat_ptr ptr;

        ptr = phi::move(base);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr1);

        phi::flat_ptr ptr2(raw_ptr2);

        ptr = phi::move(ptr2);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(const not_null_flat_ptr&)")
    {
        phi::not_null_flat_ptr not_null(raw_ptr1);
        phi::flat_ptr          ptr;

        ptr = not_null;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("operator=(not_null_flat_ptr&&)")
    {
        phi::not_null_flat_ptr not_null(raw_ptr1);
        phi::flat_ptr          ptr;

        ptr = phi::move(not_null);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("operator=(TypeT*)")
    {
        phi::flat_ptr ptr;

        ptr = raw_ptr1;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr1);

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("clear")
    {
        phi::flat_ptr ptr(raw_ptr1);

        ptr.clear();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("release_not_null")
    {
        phi::flat_ptr ptr(raw_ptr1);

        phi::not_null_flat_ptr not_null = ptr.release_not_null();

        CHECK(not_null.get() == raw_ptr1);
    }

    SECTION("swap")
    {
        phi::flat_ptr ptr1(raw_ptr1);
        phi::flat_ptr ptr2(raw_ptr2);

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

    SECTION("operator bool")
    {
        phi::flat_ptr false_ptr;
        phi::flat_ptr true_ptr{raw_ptr1};

        CHECK_FALSE(false_ptr);
        CHECK(true_ptr);
    }

    SECTION("operator boolean")
    {
        phi::flat_ptr false_ptr;
        phi::flat_ptr true_ptr(raw_ptr1);

        CHECK_FALSE(static_cast<phi::boolean>(false_ptr));
        CHECK(static_cast<phi::boolean>(true_ptr));
    }

    SECTION("operator void*")
    {
        phi::flat_ptr ptr(raw_ptr1);

        void* new_ptr = static_cast<void*>(ptr);

        CHECK(new_ptr == raw_ptr1);
    }

    SECTION("operator const void*")
    {
        const phi::flat_ptr ptr(raw_ptr1);

        const void* new_ptr = static_cast<const void*>(ptr);

        CHECK(new_ptr == raw_ptr1);
    }

    SECTION("operator==")
    {
        phi::flat_ptr ptr1(raw_ptr1);
        phi::flat_ptr ptr2(raw_ptr2);
        phi::flat_ptr null;

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
    }

    SECTION("operator!=")
    {
        phi::flat_ptr ptr1(raw_ptr1);
        phi::flat_ptr ptr2(raw_ptr2);
        phi::flat_ptr null;

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
    }

    SECTION("std::hash")
    {
        phi::size_t null_hash = std::hash<phi::flat_ptr>{}(nullptr);
        phi::size_t ptr_hash  = std::hash<phi::flat_ptr>{}(raw_ptr1);

        CHECK(null_hash != ptr_hash);
        CHECK(null_hash == std::hash<void*>{}(nullptr));
        CHECK(ptr_hash == std::hash<void*>{}(raw_ptr1));
    }
}

TEST_CASE("not_null_flat_ptr", "[Core][flat_ptr][not_null_flat_ptr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::not_null_flat_ptr) == sizeof(void*));

#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
        STATIC_REQUIRE_FALSE(phi::is_default_constructible<phi::not_null_flat_ptr>::value);
#endif
        STATIC_REQUIRE(phi::is_copy_constructible<phi::not_null_flat_ptr>::value);
        STATIC_REQUIRE(phi::is_move_constructible<phi::not_null_flat_ptr>::value);
        STATIC_REQUIRE(phi::is_copy_assignable<phi::not_null_flat_ptr>::value);
        STATIC_REQUIRE(phi::is_move_assignable<phi::not_null_flat_ptr>::value);
    }

    SECTION("Type aliases")
    {
        CHECK_SAME_TYPE(phi::not_null_flat_ptr::this_type, phi::not_null_flat_ptr);
        CHECK_SAME_TYPE(phi::not_null_flat_ptr::value_type, void*);
    }

    int  val1     = 21;
    int  val2     = 42;
    int  val3     = 99;
    int* raw_ptr1 = &val1;
    int* raw_ptr2 = &val2;
    int* raw_ptr3 = &val3;

    SECTION("not_null_flat_ptr(TypeT*)")
    {
        phi::not_null_flat_ptr ptr(raw_ptr1);

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("not_null_flat_ptr(const not_null_flat_ptr&)")
    {
        phi::not_null_flat_ptr base(raw_ptr1);
        phi::not_null_flat_ptr ptr(base);

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("not_null_flat_ptr(not_null_flat_ptr&&)")
    {
        phi::not_null_flat_ptr base(raw_ptr1);
        phi::not_null_flat_ptr ptr(phi::move(base));

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("not_null_flat_ptr(TypeT*)")
    {
        phi::not_null_flat_ptr ptr(raw_ptr1);

        ptr = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(const not_null_flat_ptr&)")
    {
        phi::not_null_flat_ptr base(raw_ptr1);
        phi::not_null_flat_ptr ptr(raw_ptr2);

        ptr = base;

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("operator=(not_null_flat_ptr&&)")
    {
        phi::not_null_flat_ptr base(raw_ptr1);
        phi::not_null_flat_ptr ptr(raw_ptr2);

        ptr = phi::move(base);

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("swap")
    {
        phi::not_null_flat_ptr ptr1(raw_ptr1);
        phi::not_null_flat_ptr ptr2(raw_ptr2);

        ptr1.swap(ptr2);

        CHECK(ptr1.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr1);

        phi::swap(ptr1, ptr2);

        CHECK(ptr1.get() == raw_ptr1);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("operator==")
    {
        phi::not_null_flat_ptr ptr1(raw_ptr1);
        phi::not_null_flat_ptr ptr2(raw_ptr2);
        phi::not_null_flat_ptr ptr3(raw_ptr3);

        CHECK_FALSE(ptr1 == ptr2);
        CHECK_FALSE(ptr1 == ptr3);
        CHECK_FALSE(ptr2 == ptr3);

        ptr2 = raw_ptr1;

        CHECK(ptr1 == ptr2);
    }

    SECTION("operator!=")
    {
        phi::not_null_flat_ptr ptr1(raw_ptr1);
        phi::not_null_flat_ptr ptr2(raw_ptr2);
        phi::not_null_flat_ptr ptr3(raw_ptr3);

        CHECK(ptr1 != ptr2);
        CHECK(ptr1 != ptr3);
        CHECK(ptr2 != ptr3);

        ptr2 = raw_ptr1;

        CHECK_FALSE(ptr1 != ptr2);
    }

    SECTION("operator void*")
    {
        phi::not_null_flat_ptr ptr(raw_ptr1);

        void* new_ptr = static_cast<void*>(ptr);

        CHECK(new_ptr == raw_ptr1);
    }

    SECTION("operator const void*")
    {
        const phi::not_null_flat_ptr ptr(raw_ptr1);

        const void* new_ptr = static_cast<const void*>(ptr);

        CHECK(new_ptr == raw_ptr1);
    }

    SECTION("std::hash")
    {
        phi::size_t ptr1_hash = std::hash<phi::not_null_flat_ptr>{}(raw_ptr1);
        phi::size_t ptr2_hash = std::hash<phi::not_null_flat_ptr>{}(raw_ptr2);

        CHECK(ptr1_hash != ptr2_hash);
        CHECK(ptr1_hash == std::hash<void*>{}(raw_ptr1));
        CHECK(ptr2_hash == std::hash<void*>{}(raw_ptr2));
    }
}
