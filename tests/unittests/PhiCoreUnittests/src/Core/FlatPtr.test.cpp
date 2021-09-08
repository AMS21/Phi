#include <catch2/catch_test_macros.hpp>

#include "ConstexprHelper.hpp"
#include <Phi/Core/FlatPtr.hpp>
#include <type_traits>

struct A
{
    bool f()
    {
        return true;
    }
};

TEST_CASE("FlatPtr", "[Core][FlatPtr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::FlatPtr) == sizeof(void*));

        STATIC_REQUIRE(std::is_default_constructible<phi::FlatPtr>::value);
        STATIC_REQUIRE(std::is_copy_constructible<phi::FlatPtr>::value);
        STATIC_REQUIRE(std::is_move_constructible<phi::FlatPtr>::value);
        STATIC_REQUIRE(std::is_copy_assignable<phi::FlatPtr>::value);
        STATIC_REQUIRE(std::is_move_assignable<phi::FlatPtr>::value);
    }

    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same<phi::FlatPtr::this_type, phi::FlatPtr>::value);
        STATIC_REQUIRE(std::is_same<phi::FlatPtr::value_type, void*>::value);
        STATIC_REQUIRE(std::is_same<phi::FlatPtr::not_null_type, phi::NotNullFlatPtr>::value);
    }

    int val1 = 21;
    int val2 = 42;

    int* raw_ptr1 = &val1;
    int* raw_ptr2 = &val2;

    SECTION("FlatPtr()")
    {
        phi::FlatPtr ptr;

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("FlatPtr(std::nullptr_t)")
    {
        phi::FlatPtr ptr(nullptr);

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("FlatPtr(PtrT*)")
    {
        phi::FlatPtr ptr(raw_ptr1);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("FlatPtr(const FlatPtr&)")
    {
        phi::FlatPtr base(raw_ptr1);
        phi::FlatPtr ptr(base);

        REQUIRE(base);
        REQUIRE(ptr);

        CHECK(ptr.get() == base.get());
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("FlatPtr(FlatPtr&&)")
    {
        phi::FlatPtr base(raw_ptr1);
        phi::FlatPtr ptr(std::move(base));

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("FlatPtr(const NotNullFlatPtr&)")
    {
        phi::NotNullFlatPtr not_null(raw_ptr1);
        phi::FlatPtr        ptr(not_null);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("FlatPtr(NotNullFlatPtr&&)")
    {
        phi::NotNullFlatPtr not_null(raw_ptr1);
        phi::FlatPtr        ptr(std::move(not_null));

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("FlatPtr(std::nullptr_t)")
    {
        phi::FlatPtr ptr;

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr = raw_ptr1;
        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("operator=(const FlatPtr&)")
    {
        phi::FlatPtr base(raw_ptr1);
        phi::FlatPtr ptr;

        ptr = base;

        CHECK(base);
        CHECK(base.get() == raw_ptr1);

        phi::FlatPtr ptr2(raw_ptr2);

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(FlatPtr&&)")
    {
        phi::FlatPtr base(raw_ptr1);
        phi::FlatPtr ptr;

        ptr = std::move(base);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr1);

        phi::FlatPtr ptr2(raw_ptr2);

        ptr = std::move(ptr2);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(const NotNullFlatPtr&)")
    {
        phi::NotNullFlatPtr not_null(raw_ptr1);
        phi::FlatPtr        ptr;

        ptr = not_null;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("operator=(NotNullFlatPtr&&)")
    {
        phi::NotNullFlatPtr not_null(raw_ptr1);
        phi::FlatPtr        ptr;

        ptr = std::move(not_null);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("operator=(TypeT*)")
    {
        phi::FlatPtr ptr;

        ptr = raw_ptr1;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr1);

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("clear")
    {
        phi::FlatPtr ptr(raw_ptr1);

        ptr.clear();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("release_not_null")
    {
        phi::FlatPtr ptr(raw_ptr1);

        phi::NotNullFlatPtr not_null = ptr.release_not_null();

        CHECK(not_null.get() == raw_ptr1);
    }

    SECTION("swap")
    {
        phi::FlatPtr ptr1(raw_ptr1);
        phi::FlatPtr ptr2(raw_ptr2);

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
        phi::FlatPtr false_ptr;
        phi::FlatPtr true_ptr{raw_ptr1};

        CHECK_FALSE(false_ptr);
        CHECK(true_ptr);
    }

    SECTION("operator Boolean")
    {
        phi::FlatPtr false_ptr;
        phi::FlatPtr true_ptr(raw_ptr1);

        CHECK_FALSE(static_cast<phi::Boolean>(false_ptr));
        CHECK(static_cast<phi::Boolean>(true_ptr));
    }

    SECTION("operator void*")
    {
        phi::FlatPtr ptr(raw_ptr1);

        void* new_ptr = static_cast<void*>(ptr);

        CHECK(new_ptr == raw_ptr1);
    }

    SECTION("operator const void*")
    {
        const phi::FlatPtr ptr(raw_ptr1);

        const void* new_ptr = static_cast<const void*>(ptr);

        CHECK(new_ptr == raw_ptr1);
    }

    SECTION("operator==")
    {
        phi::FlatPtr ptr1(raw_ptr1);
        phi::FlatPtr ptr2(raw_ptr2);
        phi::FlatPtr null;

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
        phi::FlatPtr ptr1(raw_ptr1);
        phi::FlatPtr ptr2(raw_ptr2);
        phi::FlatPtr null;

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
        std::size_t null_hash = std::hash<phi::FlatPtr>{}(nullptr);
        std::size_t ptr_hash  = std::hash<phi::FlatPtr>{}(raw_ptr1);

        CHECK(null_hash != ptr_hash);
        CHECK(null_hash == std::hash<void*>{}(nullptr));
        CHECK(ptr_hash == std::hash<void*>{}(raw_ptr1));
    }
}

TEST_CASE("NotNullFlatPtr", "[Core][FlatPtr][NotNullFlatPtr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::NotNullFlatPtr) == sizeof(void*));

        STATIC_REQUIRE_FALSE(std::is_default_constructible<phi::NotNullFlatPtr>::value);
        STATIC_REQUIRE(std::is_copy_constructible<phi::NotNullFlatPtr>::value);
        STATIC_REQUIRE(std::is_move_constructible<phi::NotNullFlatPtr>::value);
        STATIC_REQUIRE(std::is_copy_assignable<phi::NotNullFlatPtr>::value);
        STATIC_REQUIRE(std::is_move_assignable<phi::NotNullFlatPtr>::value);
    }

    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same<phi::NotNullFlatPtr::this_type, phi::NotNullFlatPtr>::value);
        STATIC_REQUIRE(std::is_same<phi::NotNullFlatPtr::value_type, void*>::value);
    }

    int  val1     = 21;
    int  val2     = 42;
    int  val3     = 99;
    int* raw_ptr1 = &val1;
    int* raw_ptr2 = &val2;
    int* raw_ptr3 = &val3;

    SECTION("NotNullFlatPtr(TypeT*)")
    {
        phi::NotNullFlatPtr ptr(raw_ptr1);

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("NotNullFlatPtr(const NotNullFlatPtr&)")
    {
        phi::NotNullFlatPtr base(raw_ptr1);
        phi::NotNullFlatPtr ptr(base);

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("NotNullFlatPtr(NotNullFlatPtr&&)")
    {
        phi::NotNullFlatPtr base(raw_ptr1);
        phi::NotNullFlatPtr ptr(std::move(base));

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("NotNullFlatPtr(TypeT*)")
    {
        phi::NotNullFlatPtr ptr(raw_ptr1);

        ptr = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(const NotNullFlatPtr&)")
    {
        phi::NotNullFlatPtr base(raw_ptr1);
        phi::NotNullFlatPtr ptr(raw_ptr2);

        ptr = base;

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("operator=(NotNullFlatPtr&&)")
    {
        phi::NotNullFlatPtr base(raw_ptr1);
        phi::NotNullFlatPtr ptr(raw_ptr2);

        ptr = std::move(base);

        CHECK(ptr.get() == raw_ptr1);
    }

    SECTION("swap")
    {
        phi::NotNullFlatPtr ptr1(raw_ptr1);
        phi::NotNullFlatPtr ptr2(raw_ptr2);

        ptr1.swap(ptr2);

        CHECK(ptr1.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr1);

        phi::swap(ptr1, ptr2);

        CHECK(ptr1.get() == raw_ptr1);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("operator==")
    {
        phi::NotNullFlatPtr ptr1(raw_ptr1);
        phi::NotNullFlatPtr ptr2(raw_ptr2);
        phi::NotNullFlatPtr ptr3(raw_ptr3);

        CHECK_FALSE(ptr1 == ptr2);
        CHECK_FALSE(ptr1 == ptr3);
        CHECK_FALSE(ptr2 == ptr3);

        ptr2 = raw_ptr1;

        CHECK(ptr1 == ptr2);
    }

    SECTION("operator!=")
    {
        phi::NotNullFlatPtr ptr1(raw_ptr1);
        phi::NotNullFlatPtr ptr2(raw_ptr2);
        phi::NotNullFlatPtr ptr3(raw_ptr3);

        CHECK(ptr1 != ptr2);
        CHECK(ptr1 != ptr3);
        CHECK(ptr2 != ptr3);

        ptr2 = raw_ptr1;

        CHECK_FALSE(ptr1 != ptr2);
    }

    SECTION("operator void*")
    {
        phi::NotNullFlatPtr ptr(raw_ptr1);

        void* new_ptr = static_cast<void*>(ptr);

        CHECK(new_ptr == raw_ptr1);
    }

    SECTION("operator const void*")
    {
        const phi::NotNullFlatPtr ptr(raw_ptr1);

        const void* new_ptr = static_cast<const void*>(ptr);

        CHECK(new_ptr == raw_ptr1);
    }

    SECTION("std::hash")
    {
        std::size_t ptr1_hash = std::hash<phi::NotNullFlatPtr>{}(raw_ptr1);
        std::size_t ptr2_hash = std::hash<phi::NotNullFlatPtr>{}(raw_ptr2);

        CHECK(ptr1_hash != ptr2_hash);
        CHECK(ptr1_hash == std::hash<void*>{}(raw_ptr1));
        CHECK(ptr2_hash == std::hash<void*>{}(raw_ptr2));
    }
}
