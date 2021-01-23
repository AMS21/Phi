#include <catch2/catch_test_macros.hpp>

#include <Phi/Core/RefPtr.hpp>
#include <Phi/Math/Vector2.hpp>
#include <thread>
#include <type_traits>
#include <vector>

struct A
{
    bool f()
    {
        return true;
    }
};

constexpr phi::u64 NumberOfTestThreads{120u};

TEST_CASE("RefPtr", "[Core][RefPtr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::RefPtr<int>) == sizeof(int*) * 2);

        STATIC_REQUIRE(std::is_default_constructible_v<phi::RefPtr<int>>);
        STATIC_REQUIRE(std::is_copy_constructible_v<phi::RefPtr<int>>);
        STATIC_REQUIRE(std::is_move_constructible_v<phi::RefPtr<int>>);
        STATIC_REQUIRE(std::is_copy_assignable_v<phi::RefPtr<int>>);
        STATIC_REQUIRE(std::is_move_assignable_v<phi::RefPtr<int>>);
    }

    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same_v<phi::RefPtr<int>::this_type, phi::RefPtr<int>>);
        STATIC_REQUIRE(std::is_same_v<phi::RefPtr<int>::value_type, int>);
        STATIC_REQUIRE(std::is_same_v<phi::RefPtr<int>::reference, int&>);
        STATIC_REQUIRE(std::is_same_v<phi::RefPtr<int>::const_reference, const int&>);
        STATIC_REQUIRE(std::is_same_v<phi::RefPtr<int>::pointer, int*>);
        STATIC_REQUIRE(std::is_same_v<phi::RefPtr<int>::const_pointer, const int*>);
    }

    SECTION("No race condition")
    {
        phi::RefPtr<int> ptr = phi::make_ref<int>(21);

        std::vector<std::thread> threads;
        threads.reserve(NumberOfTestThreads.get());

        // Create all threads
        for (phi::usize i{0u}; i < NumberOfTestThreads; ++i)
        {
            threads.emplace_back(std::thread([ptr] { phi::RefPtr<int> copy = ptr; }));
        }

        // Wait for all threads to join
        for (auto& thread : threads)
        {
            thread.join();
        }

        phi::usize use_count = ptr.use_count();

        CAPTURE(use_count);

        CHECK(bool(use_count == 1u));
    }

    SECTION("RefPtr()")
    {
        phi::RefPtr<int> ptr;

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("RefPtr(std::nullptr_t)")
    {
        phi::RefPtr<int> ptr(nullptr);

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);
    }

    SECTION("RefPtr(TypeT*)")
    {
        int*             raw_ptr = new int(22);
        phi::RefPtr<int> ptr(raw_ptr);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("RefPtr(const RefPtr&)")
    {
        int*             raw_ptr = new int(33);
        phi::RefPtr<int> ptr(raw_ptr);
        phi::RefPtr<int> copy(ptr);

        REQUIRE(ptr);
        REQUIRE(copy);
        CHECK(copy.get() == raw_ptr);
        CHECK(ptr == copy);
    }

    SECTION("RefPtr(RefPtr&&)")
    {
        int*             raw_ptr = new int(12);
        phi::RefPtr<int> base(raw_ptr);
        phi::RefPtr<int> copy(std::move(base));

        CHECK_FALSE(base);
        CHECK(base.get() == nullptr);
        CHECK(copy);
        CHECK(copy.get() == raw_ptr);
    }

    SECTION("RefPtr(const NotNullRefPtr&)")
    {
        int*               raw_ptr = new int(21);
        phi::NotNullRefPtr not_null(raw_ptr);
        phi::RefPtr        ptr(not_null);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.get() == not_null.get());
    }

    SECTION("RefPtr(NotNullRefPtr&&)")
    {
        int*                    raw_ptr = new int(21);
        phi::NotNullRefPtr<int> not_null(raw_ptr);
        phi::RefPtr<int>        ptr(std::move(not_null));

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("operator=(std::nullptr_t)")
    {
        phi::RefPtr<int> ptr(new int(21));

        CHECK(ptr);

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("operator=(TypeT*)")
    {
        phi::RefPtr<int> ptr(new int(21));
        int*             raw_ptr = new int(33);
        int*             null    = nullptr;

        ptr = raw_ptr;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        ptr = null;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        int* raw_ptr2 = new int(44);
        ptr           = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(const RefPtr&)")
    {
        int*             raw_ptr  = new int(21);
        int*             raw_ptr2 = new int(22);
        phi::RefPtr<int> ptr(raw_ptr);
        phi::RefPtr<int> ptr2(raw_ptr2);

        ptr = ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);

        ptr = phi::RefPtr<int>();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        int* raw_ptr3 = new int(44);
        ptr           = raw_ptr3;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr3);
    }

    SECTION("operator=(RefPtr&&)")
    {
        int*             raw_ptr  = new int(21);
        int*             raw_ptr2 = new int(22);
        phi::RefPtr<int> ptr(raw_ptr);
        phi::RefPtr<int> ptr2(raw_ptr2);

        ptr = std::move(ptr2);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);

        int* raw_ptr3 = new int(23);
        ptr           = phi::RefPtr<int>(raw_ptr3);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr3);

        ptr = phi::RefPtr<int>();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        int* raw_ptr4 = new int(24);

        ptr = phi::RefPtr<int>(raw_ptr4);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr4);
    }

    SECTION("operator=(const NotNullRefPtr&)")
    {
        int*                    raw_ptr  = new int(21);
        int*                    raw_ptr2 = new int(22);
        phi::RefPtr<int>        ptr(raw_ptr);
        phi::NotNullRefPtr<int> not_null(raw_ptr2);

        ptr = not_null;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);

        ptr.clear();

        int* raw_ptr3 = new int(44);
        ptr           = phi::NotNullRefPtr<int>(raw_ptr3);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr3);
    }

    SECTION("operator=(NotNullRefPtr&&)")
    {
        // int*                    raw_ptr  = new int(21);
        // int*                    raw_ptr2 = new int(22);
        // phi::RefPtr<int>        ptr(raw_ptr);
        // phi::NotNullRefPtr<int> not_null(raw_ptr2);

        // ptr = std::move(not_null);

        // CHECK(ptr);
        // CHECK(ptr.get() == raw_ptr2);

        // int*                    raw_ptr3 = new int(23);
        // phi::NotNullRefPtr<int> not_null2(raw_ptr3);
        // ptr = std::move(not_null2);

        // CHECK(ptr);
        // CHECK(ptr.get() == raw_ptr3);

        // ptr.clear();

        // int*                    raw_ptr4 = new int(24);
        // phi::NotNullRefPtr<int> not_null3(raw_ptr4);
        // ptr = std::move(not_null3);

        // CHECK(ptr);
        // CHECK(ptr.get() == raw_ptr4);
    }

    SECTION("clear")
    {
        phi::RefPtr<int> ptr;

        ptr.clear();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr = new int(23);
        ptr.clear();

        CHECK(ptr.get() == nullptr);
    }

    SECTION("reset")
    {
        phi::RefPtr<int> ptr;

        int* raw_ptr = new int(21);
        ptr.reset(raw_ptr);

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(22);
        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);

        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);

        ptr.reset(nullptr);

        CHECK(ptr.get() == nullptr);
    }

    SECTION("swap")
    {
        int*             raw_ptr  = new int(21);
        int*             raw_ptr2 = new int(22);
        phi::RefPtr<int> ptr(raw_ptr);
        phi::RefPtr<int> ptr2(raw_ptr2);

        ptr.swap(ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr);

        swap(ptr, ptr2);

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("use_count")
    {
        int*             raw_ptr = new int(22);
        phi::RefPtr<int> ptr(raw_ptr);

        REQUIRE(ptr);
        CHECK(bool(ptr.use_count() == 1u));

        {
            phi::RefPtr<int> shared_ptr_1(ptr);

            CHECK(bool(ptr.use_count() == 2u));

            {
                phi::RefPtr<int> shared_ptr_2(ptr);

                CHECK(bool(ptr.use_count() == 3u));
                {
                    phi::RefPtr<int> shared_ptr_3(ptr);

                    CHECK(bool(ptr.use_count() == 4u));
                }

                CHECK(bool(ptr.use_count() == 3u));

                phi::RefPtr<int> shared_ptr_4(ptr);

                CHECK(bool(ptr.use_count() == 4u));
            }

            CHECK(bool(ptr.use_count() == 2u));
        }

        CHECK(bool(ptr.use_count() == 1u));

        phi::RefPtr<int> null;

        CHECK(bool(null.use_count() == 0u));
    }

    SECTION("operator TypeT*")
    {
        int*             raw_ptr = new int(12);
        phi::RefPtr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);

        CHECK(new_ptr == raw_ptr);
    }

    SECTION("operator->")
    {
        phi::RefPtr<A> ptr(new A);

        CHECK(ptr->f());
    }

    SECTION("operator*")
    {
        int*             raw_ptr = new int(0);
        phi::RefPtr<int> ptr(raw_ptr);

        CHECK(*ptr == 0);

        *raw_ptr = 12;

        CHECK(*ptr == 12);

        *ptr = 9;

        CHECK(*ptr == 9);
        CHECK(*raw_ptr == 9);
    }

    SECTION("operator==")
    {
        phi::RefPtr<int> ptr1(new int(1));
        phi::RefPtr<int> ptr2(new int(2));
        phi::RefPtr<int> null;

        CHECK_FALSE(ptr1 == ptr2);
        CHECK_FALSE(ptr1 == null);
        CHECK_FALSE(ptr2 == null);

        CHECK_FALSE(ptr1 == nullptr);
        CHECK_FALSE(ptr2 == nullptr);
        CHECK(null == nullptr);

        CHECK_FALSE(nullptr == ptr1);
        CHECK_FALSE(nullptr == ptr2);
        CHECK(nullptr == null);

        ptr2 = ptr1;

        CHECK(ptr1 == ptr2);
    }

    SECTION("operator!=")
    {
        phi::RefPtr<int> ptr1(new int(1));
        phi::RefPtr<int> ptr2(new int(2));
        phi::RefPtr<int> null;

        CHECK(ptr1 != ptr2);
        CHECK(ptr1 != null);
        CHECK(ptr2 != null);

        CHECK(ptr1 != nullptr);
        CHECK(ptr2 != nullptr);
        CHECK_FALSE(null != nullptr);

        CHECK(nullptr != ptr1);
        CHECK(nullptr != ptr2);
        CHECK_FALSE(nullptr != null);

        ptr2 = ptr1;

        CHECK_FALSE(ptr1 != ptr2);
    }

    SECTION("make_ref")
    {
        phi::RefPtr<int> int_ptr  = phi::make_ref<int>();
        phi::RefPtr<int> int_ptr2 = phi::make_ref<int>(3);

        CHECK(*int_ptr2 == 3);

        phi::RefPtr<phi::Vector2i32> vec2_ptr = phi::make_ref<phi::Vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }
}

TEST_CASE("NotNullRefPtr", "[Core][RefPtr][RefPtr][NotNullRefPtr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::NotNullRefPtr<int>) == sizeof(int*) * 2);

        STATIC_REQUIRE_FALSE(std::is_default_constructible_v<phi::NotNullRefPtr<int>>);
        STATIC_REQUIRE(std::is_copy_constructible_v<phi::NotNullRefPtr<int>>);
        STATIC_REQUIRE(std::is_move_constructible_v<phi::NotNullRefPtr<int>>);
        STATIC_REQUIRE(std::is_copy_assignable_v<phi::NotNullRefPtr<int>>);
        STATIC_REQUIRE(std::is_move_assignable_v<phi::NotNullRefPtr<int>>);
    }

    SECTION("Type aliases")
    {
        STATIC_REQUIRE(std::is_same_v<phi::NotNullRefPtr<int>::this_type, phi::NotNullRefPtr<int>>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullRefPtr<int>::value_type, int>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullRefPtr<int>::reference, int&>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullRefPtr<int>::const_reference, const int&>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullRefPtr<int>::pointer, int*>);
        STATIC_REQUIRE(std::is_same_v<phi::NotNullRefPtr<int>::const_pointer, const int*>);
    }

    SECTION("No race condition")
    {
        phi::NotNullRefPtr<int> ptr = phi::make_not_null_ref<int>(21);

        std::vector<std::thread> threads;
        threads.reserve(NumberOfTestThreads.get());

        // Create all threads
        for (phi::usize i{0u}; i < NumberOfTestThreads; ++i)
        {
            threads.emplace_back(std::thread([ptr] { phi::NotNullRefPtr<int> copy = ptr; }));
        }

        // Wait for all threads to join
        for (auto&& thread : threads)
        {
            thread.join();
        }

        phi::usize use_count = ptr.use_count();

        CAPTURE(use_count);

        CHECK(bool(use_count == 1u));
    }

    SECTION("NotNullRefPtr(TypeT*)")
    {
        int*                    raw_ptr = new int(22);
        phi::NotNullRefPtr<int> ptr(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("NotNullRefPtr(const NotNullRefPtr&)")
    {
        int*                    raw_ptr = new int(33);
        phi::NotNullRefPtr<int> ptr(raw_ptr);
        phi::NotNullRefPtr<int> copy(ptr);

        CHECK(copy.get() == raw_ptr);
        CHECK(ptr == copy);
    }

    SECTION("NotNullRefPtr(NotNullRefPtr&&)")
    {
        int*                    raw_ptr = new int(12);
        phi::NotNullRefPtr<int> base(raw_ptr);
        phi::NotNullRefPtr<int> copy(std::move(base));

        CHECK(copy.get() == raw_ptr);
    }

    SECTION("operator=(TypeT*)")
    {
        phi::NotNullRefPtr<int> ptr(new int(21));
        int*                    raw_ptr = new int(33);

        ptr = raw_ptr;

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(44);
        ptr           = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(const NotNullRefPtr&)")
    {
        int*                    raw_ptr  = new int(21);
        int*                    raw_ptr2 = new int(22);
        phi::NotNullRefPtr<int> ptr(raw_ptr);
        phi::NotNullRefPtr<int> ptr2(raw_ptr2);

        ptr = ptr2;

        CHECK(ptr.get() == raw_ptr2);

        int* raw_ptr3 = new int(44);
        ptr           = raw_ptr3;

        CHECK(ptr.get() == raw_ptr3);
    }

    SECTION("operator=(NotNullRefPtr&&)")
    {
        int*                    raw_ptr  = new int(21);
        int*                    raw_ptr2 = new int(22);
        phi::NotNullRefPtr<int> ptr(raw_ptr);
        phi::NotNullRefPtr<int> ptr2(raw_ptr2);

        ptr = std::move(ptr2);

        CHECK(ptr.get() == raw_ptr2);

        int* raw_ptr3 = new int(23);
        ptr           = phi::NotNullRefPtr<int>(raw_ptr3);

        CHECK(ptr.get() == raw_ptr3);

        int* raw_ptr4 = new int(24);

        ptr = phi::NotNullRefPtr<int>(raw_ptr4);

        CHECK(ptr.get() == raw_ptr4);
    }

    SECTION("reset")
    {
        phi::NotNullRefPtr<int> ptr(new int(20));

        int* raw_ptr = new int(21);
        ptr.reset(raw_ptr);

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(22);
        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);

        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("swap")
    {
        int*                    raw_ptr  = new int(21);
        int*                    raw_ptr2 = new int(22);
        phi::NotNullRefPtr<int> ptr(raw_ptr);
        phi::NotNullRefPtr<int> ptr2(raw_ptr2);

        ptr.swap(ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr);

        swap(ptr, ptr2);

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("use_count")
    {
        int*                    raw_ptr = new int(22);
        phi::NotNullRefPtr<int> ptr(raw_ptr);

        CHECK(bool(ptr.use_count() == 1u));

        {
            phi::NotNullRefPtr<int> shared_ptr_1(ptr);

            CHECK(bool(ptr.use_count() == 2u));

            {
                phi::NotNullRefPtr<int> shared_ptr_2(ptr);

                CHECK(bool(ptr.use_count() == 3u));
                {
                    phi::NotNullRefPtr<int> shared_ptr_3(ptr);

                    CHECK(bool(ptr.use_count() == 4u));
                }

                CHECK(bool(ptr.use_count() == 3u));

                phi::NotNullRefPtr<int> shared_ptr_4(ptr);

                CHECK(bool(ptr.use_count() == 4u));
            }

            CHECK(bool(ptr.use_count() == 2u));
        }

        CHECK(bool(ptr.use_count() == 1u));
    }

    SECTION("operator TypeT*")
    {
        int*                    raw_ptr = new int(12);
        phi::NotNullRefPtr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);

        CHECK(new_ptr == raw_ptr);
    }

    SECTION("operator->")
    {
        phi::NotNullRefPtr<A> ptr(new A);

        CHECK(ptr->f());
    }

    SECTION("operator*")
    {
        int*                    raw_ptr = new int(0);
        phi::NotNullRefPtr<int> ptr(raw_ptr);

        CHECK(*ptr == 0);

        *raw_ptr = 12;

        CHECK(*ptr == 12);

        *ptr = 9;

        CHECK(*ptr == 9);
        CHECK(*raw_ptr == 9);
    }

    SECTION("operator==")
    {
        phi::NotNullRefPtr<int> ptr1(new int(1));
        phi::NotNullRefPtr<int> ptr2(new int(2));

        CHECK_FALSE(ptr1 == ptr2);

        ptr2 = ptr1;

        CHECK(ptr1 == ptr2);
    }

    SECTION("operator!=")
    {
        phi::NotNullRefPtr<int> ptr1(new int(1));
        phi::NotNullRefPtr<int> ptr2(new int(2));

        CHECK(ptr1 != ptr2);

        ptr2 = ptr1;

        CHECK_FALSE(ptr1 != ptr2);
    }

    SECTION("make_not_null_ref")
    {
        phi::NotNullRefPtr<int> int_ptr = phi::make_not_null_ref<int>(3);

        CHECK(*int_ptr == 3);

        phi::NotNullRefPtr<phi::Vector2i32> vec2_ptr =
                phi::make_not_null_ref<phi::Vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }
}
