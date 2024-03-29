#include <phi/test/test_macros.hpp>

#include <phi/core/boolean.hpp>
#include <phi/core/flat_ptr.hpp>
#include <phi/core/move.hpp>
#include <phi/core/observer_ptr.hpp>
#include <phi/core/ref_ptr.hpp>
#include <phi/math/vector2.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <phi/type_traits/is_copy_constructible.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_move_assignable.hpp>
#include <phi/type_traits/is_move_constructible.hpp>

struct A
{
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    PHI_NODISCARD bool f() const
    {
        return true;
    }
};

struct Base
{};

struct Derived : public Base
{};

TEST_CASE("ref_ptr")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::ref_ptr<int>) == sizeof(int*) * 2);

#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
        STATIC_REQUIRE(phi::is_default_constructible<phi::ref_ptr<int>>::value);
#endif
        STATIC_REQUIRE(phi::is_copy_constructible<phi::ref_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_move_constructible<phi::ref_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_copy_assignable<phi::ref_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_move_assignable<phi::ref_ptr<int>>::value);
    }

    SECTION("Type aliases")
    {
        CHECK_SAME_TYPE(phi::ref_ptr<int>::this_type, phi::ref_ptr<int>);
        CHECK_SAME_TYPE(phi::ref_ptr<int>::value_type, int);
        CHECK_SAME_TYPE(phi::ref_ptr<int>::reference, int&);
        CHECK_SAME_TYPE(phi::ref_ptr<int>::const_reference, const int&);
        CHECK_SAME_TYPE(phi::ref_ptr<int>::pointer, int*);
        CHECK_SAME_TYPE(phi::ref_ptr<int>::const_pointer, const int*);
    }

    SECTION("ref_ptr()")
    {
        phi::ref_ptr<int> ptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());

        phi::ref_ptr<int> ptr2{};

        CHECK_FALSE(ptr2);
        CHECK(ptr2.get() == nullptr);
        CHECK(ptr2.use_count() == 0u);
        CHECK_FALSE(ptr2.has_control_block());

        phi::ref_ptr<int> ptr3 = {};

        CHECK_FALSE(ptr3);
        CHECK(ptr3.get() == nullptr);
        CHECK(ptr3.use_count() == 0u);
        CHECK_FALSE(ptr3.has_control_block());
    }

    SECTION("ref_ptr(nullptr_t)")
    {
        phi::ref_ptr<int> ptr(nullptr);

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());

        phi::ref_ptr<int> ptr2{nullptr};

        CHECK_FALSE(ptr2);
        CHECK(ptr2.get() == nullptr);
        CHECK(ptr2.use_count() == 0u);
        CHECK_FALSE(ptr2.has_control_block());

        phi::ref_ptr<int> ptr3 = nullptr;

        CHECK_FALSE(ptr3);
        CHECK(ptr3.get() == nullptr);
        CHECK(ptr3.use_count() == 0u);
        CHECK_FALSE(ptr3.has_control_block());
    }

    SECTION("ref_ptr(TypeT*)")
    {
        int*              raw_ptr = new int(22);
        phi::ref_ptr<int> ptr(raw_ptr);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        int*              raw_ptr2 = nullptr;
        phi::ref_ptr<int> ptr2(raw_ptr2);

        CHECK_FALSE(ptr2);
        CHECK(ptr2.get() == nullptr);
        CHECK(ptr2.use_count() == 1u);
        CHECK(ptr2.has_control_block());
    }

    SECTION("ref_ptr(OtherT*)")
    {
        Derived*           raw_ptr = new Derived();
        phi::ref_ptr<Base> ptr{raw_ptr};

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        Derived*           raw_ptr2 = nullptr;
        phi::ref_ptr<Base> ptr2{raw_ptr2};

        CHECK_FALSE(ptr2);
        CHECK(ptr2.get() == nullptr);
        CHECK(ptr2.use_count() == 1u);
        CHECK(ptr2.has_control_block());
    }

    SECTION("ref_ptr(const ref_ptr&)")
    {
        int*              raw_ptr = new int(33);
        phi::ref_ptr<int> ptr(raw_ptr);
        phi::ref_ptr<int> copy(ptr);

        REQUIRE(ptr);
        REQUIRE(copy);
        CHECK(copy.get() == raw_ptr);
        CHECK(ptr == copy);
        CHECK(ptr.use_count() == 2u);
        CHECK(copy.use_count() == 2u);
        CHECK(ptr.has_control_block());
        CHECK(copy.has_control_block());

        phi::ref_ptr<int> empty;
        phi::ref_ptr<int> empty_copy(empty);

        CHECK_FALSE(empty);
        CHECK_FALSE(empty_copy);
        CHECK(empty.get() == empty_copy.get());
        CHECK(empty == empty_copy);
        CHECK(empty.use_count() == 0u);
        CHECK(empty_copy.use_count() == 0u);
        CHECK_FALSE(empty.has_control_block());
        CHECK_FALSE(empty_copy.has_control_block());
    }

    SECTION("ref_ptr(ref_ptr&&)")
    {
        int*              raw_ptr = new int(12);
        phi::ref_ptr<int> base(raw_ptr);
        phi::ref_ptr<int> copy(phi::move(base));

        CHECK(copy);
        CHECK(copy.get() == raw_ptr);
        CHECK(copy.use_count() == 1u);
        CHECK(copy.has_control_block());
        CHECK(base.get() == nullptr);
        CHECK(base.use_count() == 0u);
        CHECK_FALSE(base.has_control_block());
    }

    SECTION("ref_ptr(const not_null_ref_ptr&)")
    {
        int*                       raw_ptr = new int(21);
        phi::not_null_ref_ptr<int> not_null(raw_ptr);
        phi::ref_ptr<int>          ptr(not_null);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.get() == not_null.get());
        CHECK(ptr.use_count() == 2u);
        CHECK(not_null.use_count() == 2u);
        CHECK(ptr.has_control_block());
    }

    SECTION("ref_ptr(not_null_ref_ptr&&)")
    {
        int*                       raw_ptr = new int(21);
        phi::not_null_ref_ptr<int> not_null(raw_ptr);
        phi::ref_ptr<int>          ptr(phi::move(not_null));

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());
    }

    SECTION("operator=(nullptr_t)")
    {
        phi::ref_ptr<int> ptr(new int(21));

        CHECK(ptr);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());
    }

    SECTION("operator=(TypeT*)")
    {
        phi::ref_ptr<int> ptr(new int(21));
        int*              raw_ptr = new int(33);
        int*              null    = nullptr;

        ptr = raw_ptr;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        ptr = null;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());

        int* raw_ptr2 = new int(44);
        ptr           = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());
    }

    SECTION("operator=(const ref_ptr&)")
    {
        int*              raw_ptr  = new int(21);
        int*              raw_ptr2 = new int(22);
        phi::ref_ptr<int> ptr(raw_ptr);
        phi::ref_ptr<int> ptr2(raw_ptr2);

        ptr = ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 2u);
        CHECK(ptr2.use_count() == 2u);
        CHECK(ptr.has_control_block());
        CHECK(ptr2.has_control_block());

        ptr = phi::ref_ptr<int>();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK(ptr2.use_count() == 1u);
        CHECK_FALSE(ptr.has_control_block());
        CHECK(ptr2.has_control_block());

        int* raw_ptr3 = new int(44);
        ptr           = raw_ptr3;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr3);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 1u);
        CHECK(ptr.has_control_block());
        CHECK(ptr2.has_control_block());
    }

    SECTION("operator=(ref_ptr&&)")
    {
        int*              raw_ptr  = new int(21);
        int*              raw_ptr2 = new int(22);
        phi::ref_ptr<int> ptr(raw_ptr);
        phi::ref_ptr<int> ptr2(raw_ptr2);

        ptr = phi::move(ptr2);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 0u);
        CHECK(ptr.has_control_block());
        CHECK_FALSE(ptr2.has_control_block());

        int* raw_ptr3 = new int(23);
        ptr           = phi::ref_ptr<int>(raw_ptr3);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr3);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 0u);
        CHECK(ptr.has_control_block());
        CHECK_FALSE(ptr2.has_control_block());

        ptr = phi::ref_ptr<int>();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK(ptr2.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());
        CHECK_FALSE(ptr2.has_control_block());

        int* raw_ptr4 = new int(24);

        ptr = phi::ref_ptr<int>(raw_ptr4);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr4);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 0u);
        CHECK(ptr.has_control_block());
        CHECK_FALSE(ptr2.has_control_block());
    }

    SECTION("operator=(const not_null_ref_ptr&)")
    {
        int*                       raw_ptr  = new int(21);
        int*                       raw_ptr2 = new int(22);
        phi::ref_ptr<int>          ptr(raw_ptr);
        phi::not_null_ref_ptr<int> not_null(raw_ptr2);

        ptr = not_null;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 2u);
        CHECK(not_null.use_count() == 2u);
        CHECK(ptr.has_control_block());

        int* raw_ptr3 = new int(44);
        ptr           = phi::not_null_ref_ptr<int>(raw_ptr3);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr3);
        CHECK(ptr.use_count() == 1u);
        CHECK(not_null.use_count() == 1u);
        CHECK(ptr.has_control_block());
    }

    SECTION("operator=(not_null_ref_ptr&&)")
    {
        int*                       raw_ptr  = new int(21);
        int*                       raw_ptr2 = new int(22);
        phi::ref_ptr<int>          ptr(raw_ptr);
        phi::not_null_ref_ptr<int> not_null(raw_ptr2);

        ptr = phi::move(not_null);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        int*                       raw_ptr3 = new int(23);
        phi::not_null_ref_ptr<int> not_null2(raw_ptr3);
        ptr = phi::move(not_null2);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr3);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        ptr.clear();

        int*                       raw_ptr4 = new int(24);
        phi::not_null_ref_ptr<int> not_null3(raw_ptr4);
        ptr = phi::move(not_null3);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr4);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());
    }

    SECTION("clear")
    {
        phi::ref_ptr<int> ptr;

        ptr.clear();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());

        ptr = new int(23);
        ptr.clear();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());
    }

    SECTION("reset")
    {
        phi::ref_ptr<int> ptr;

        int* raw_ptr = new int(21);
        ptr.reset(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        int* raw_ptr2 = new int(22);
        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr.has_control_block());

        ptr.reset(nullptr);

        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());

        ptr.reset(new int(23));
        int* int_nullptr = nullptr;
        ptr.reset(int_nullptr);

        CHECK(ptr.get() == nullptr);
        CHECK(ptr.use_count() == 0u);
        CHECK_FALSE(ptr.has_control_block());
    }

    SECTION("swap")
    {
        int*              raw_ptr  = new int(21);
        int*              raw_ptr2 = new int(22);
        phi::ref_ptr<int> ptr(raw_ptr);
        phi::ref_ptr<int> ptr2(raw_ptr2);

        ptr.swap(ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 1u);
        CHECK(ptr.has_control_block());
        CHECK(ptr2.has_control_block());

        phi::swap(ptr, ptr2);

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr2.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 1u);
        CHECK(ptr.has_control_block());
        CHECK(ptr2.has_control_block());
    }

    SECTION("use_count")
    {
        phi::ref_ptr<int> ptr(new int(22));

        REQUIRE(ptr);
        CHECK(ptr.use_count() == 1u);

        {
            // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
            phi::ref_ptr<int> shared_ptr_1(ptr);

            CHECK(ptr.use_count() == 2u);

            {
                // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
                phi::ref_ptr<int> shared_ptr_2(ptr);

                CHECK(ptr.use_count() == 3u);
                {
                    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
                    phi::ref_ptr<int> shared_ptr_3(ptr);

                    CHECK(ptr.use_count() == 4u);
                }

                CHECK(ptr.use_count() == 3u);

                // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
                phi::ref_ptr<int> shared_ptr_4(ptr);

                CHECK(ptr.use_count() == 4u);
            }

            CHECK(ptr.use_count() == 2u);
        }

        CHECK(ptr.use_count() == 1u);

        ptr.clear();
        CHECK(ptr.use_count() == 0u);

        phi::ref_ptr<int> null;

        CHECK(null.use_count() == 0u);
    }

    SECTION("operator bool")
    {
        phi::ref_ptr<int> ptr;

        CHECK_FALSE(bool(ptr));

        ptr = new int(21);

        CHECK(bool(ptr));
    }

    SECTION("operator boolean")
    {
        phi::ref_ptr<int> ptr;

        CHECK_FALSE(phi::boolean(ptr));

        ptr = new int(21);

        CHECK(phi::boolean(ptr));
    }

    SECTION("operator TypeT*")
    {
        int*              raw_ptr = new int(12);
        phi::ref_ptr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);
        CHECK(new_ptr == raw_ptr);

        const phi::ref_ptr<int> const_ptr(ptr);
        const int*              new_const_ptr = static_cast<int*>(ptr);

        CHECK(new_const_ptr == raw_ptr);

        Derived*              raw_derived = new Derived();
        phi::ref_ptr<Derived> derived_ptr(raw_derived);
        Base*                 new_base = static_cast<Base*>(derived_ptr);

        CHECK(new_base == raw_derived);

        phi::ref_ptr<Derived> const_derived_ptr(derived_ptr);
        const Base*           new_const_base = static_cast<Base*>(derived_ptr);

        CHECK(new_const_base == raw_derived);
    }

    SECTION("operator->")
    {
        phi::ref_ptr<A> ptr(new A);
        CHECK(ptr->f());

        const phi::ref_ptr<A> const_ptr{new A};
        CHECK(const_ptr->f());
    }

    SECTION("operator*")
    {
        int*              raw_ptr = new int(0);
        phi::ref_ptr<int> ptr(raw_ptr);

        CHECK(*ptr == 0);

        *raw_ptr = 12;

        CHECK(*ptr == 12);

        *ptr = 9;

        CHECK(*ptr == 9);
        CHECK(*raw_ptr == 9);

        const phi::ref_ptr<A> const_ptr{new A};
        const A&              raw_a = *const_ptr;
        CHECK(raw_a.f());
    }

    SECTION("operator==")
    {
        phi::ref_ptr<int> ptr1(new int(1));
        phi::ref_ptr<int> ptr2(new int(2));
        phi::ref_ptr<int> null;

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

    SECTION("operator== with plain pointer")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::ref_ptr<int> null;
        phi::ref_ptr<int> ptr1(raw_ptr1);
        phi::ref_ptr<int> ptr2(raw_ptr2);

        CHECK_FALSE(null == raw_ptr1);
        CHECK_FALSE(null == raw_ptr2);

        CHECK(ptr1 == raw_ptr1);
        CHECK_FALSE(ptr1 == raw_ptr2);

        CHECK_FALSE(ptr2 == raw_ptr1);
        CHECK(ptr2 == raw_ptr2);

        CHECK_FALSE(raw_ptr1 == null);
        CHECK_FALSE(raw_ptr2 == null);

        CHECK(raw_ptr1 == ptr1);
        CHECK_FALSE(raw_ptr2 == ptr1);

        CHECK_FALSE(raw_ptr1 == ptr2);
        CHECK(raw_ptr2 == ptr2);
    }

    SECTION("operator!=")
    {
        phi::ref_ptr<int> ptr1(new int(1));
        phi::ref_ptr<int> ptr2(new int(2));
        phi::ref_ptr<int> null;

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

    SECTION("operator!= with plain pointer")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::ref_ptr<int> null;
        phi::ref_ptr<int> ptr1(raw_ptr1);
        phi::ref_ptr<int> ptr2(raw_ptr2);

        CHECK(null != raw_ptr1);
        CHECK(null != raw_ptr2);

        CHECK_FALSE(ptr1 != raw_ptr1);
        CHECK(ptr1 != raw_ptr2);

        CHECK(ptr2 != raw_ptr1);
        CHECK_FALSE(ptr2 != raw_ptr2);

        CHECK(raw_ptr1 != null);
        CHECK(raw_ptr2 != null);

        CHECK_FALSE(raw_ptr1 != ptr1);
        CHECK(raw_ptr2 != ptr1);

        CHECK(raw_ptr1 != ptr2);
        CHECK_FALSE(raw_ptr2 != ptr2);
    }

    SECTION("make_ref")
    {
        phi::ref_ptr<int> int_ptr  = phi::make_ref<int>();
        phi::ref_ptr<int> int_ptr2 = phi::make_ref<int>(3);

        CHECK(*int_ptr2 == 3);

        phi::ref_ptr<phi::vector2i32> vec2_ptr = phi::make_ref<phi::vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }
}

TEST_CASE("not_null_ref_ptr", "[Core][ref_ptr][ref_ptr][not_null_ref_ptr]")
{
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::not_null_ref_ptr<int>) == sizeof(int*) * 2);

#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
        STATIC_REQUIRE_FALSE(phi::is_default_constructible<phi::not_null_ref_ptr<int>>::value);
#endif
        STATIC_REQUIRE(phi::is_copy_constructible<phi::not_null_ref_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_move_constructible<phi::not_null_ref_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_copy_assignable<phi::not_null_ref_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_move_assignable<phi::not_null_ref_ptr<int>>::value);
    }

    SECTION("Type aliases")
    {
        CHECK_SAME_TYPE(phi::not_null_ref_ptr<int>::this_type, phi::not_null_ref_ptr<int>);
        CHECK_SAME_TYPE(phi::not_null_ref_ptr<int>::value_type, int);
        CHECK_SAME_TYPE(phi::not_null_ref_ptr<int>::reference, int&);
        CHECK_SAME_TYPE(phi::not_null_ref_ptr<int>::const_reference, const int&);
        CHECK_SAME_TYPE(phi::not_null_ref_ptr<int>::pointer, int*);
        CHECK_SAME_TYPE(phi::not_null_ref_ptr<int>::const_pointer, const int*);
    }

    SECTION("not_null_ref_ptr(TypeT*)")
    {
        int*                       raw_ptr = new int(22);
        phi::not_null_ref_ptr<int> ptr(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
    }

    SECTION("not_null_ref_ptr(OtherT*)")
    {
        Derived*                    raw_ptr = new Derived();
        phi::not_null_ref_ptr<Base> ptr(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
    }

    SECTION("not_null_ref_ptr(const not_null_ref_ptr&)")
    {
        int*                       raw_ptr = new int(33);
        phi::not_null_ref_ptr<int> ptr(raw_ptr);
        phi::not_null_ref_ptr<int> copy(ptr);

        CHECK(copy.get() == raw_ptr);
        CHECK(ptr == copy);
        CHECK(ptr.use_count() == 2u);
        CHECK(copy.use_count() == 2u);
    }

    SECTION("not_null_ref_ptr(not_null_ref_ptr&&)")
    {
        int*                       raw_ptr = new int(12);
        phi::not_null_ref_ptr<int> base(raw_ptr);
        phi::not_null_ref_ptr<int> copy(phi::move(base));

        CHECK(copy.get() == raw_ptr);
        CHECK(copy.use_count() == 1u);
    }

    SECTION("operator=(TypeT*)")
    {
        phi::not_null_ref_ptr<int> ptr(new int(21));
        int*                       raw_ptr = new int(33);

        ptr = raw_ptr;

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);

        int* raw_ptr2 = new int(44);
        ptr           = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
    }

    SECTION("operator=(const not_null_ref_ptr&)")
    {
        int*                       raw_ptr  = new int(21);
        int*                       raw_ptr2 = new int(22);
        phi::not_null_ref_ptr<int> ptr(raw_ptr);
        phi::not_null_ref_ptr<int> ptr2(raw_ptr2);

        ptr = ptr2;

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 2u);
        CHECK(ptr2.use_count() == 2u);

        int* raw_ptr3 = new int(44);
        ptr           = raw_ptr3;

        CHECK(ptr.get() == raw_ptr3);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 1u);
    }

    SECTION("operator=(not_null_ref_ptr&&)")
    {
        int*                       raw_ptr  = new int(21);
        int*                       raw_ptr2 = new int(22);
        phi::not_null_ref_ptr<int> ptr(raw_ptr);
        phi::not_null_ref_ptr<int> ptr2(raw_ptr2);

        ptr = phi::move(ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);

        int* raw_ptr3 = new int(23);
        ptr           = phi::not_null_ref_ptr<int>(raw_ptr3);

        CHECK(ptr.get() == raw_ptr3);
        CHECK(ptr.use_count() == 1u);

        int* raw_ptr4 = new int(24);

        ptr = phi::not_null_ref_ptr<int>(raw_ptr4);

        CHECK(ptr.get() == raw_ptr4);
        CHECK(ptr.use_count() == 1u);
    }

    SECTION("reset")
    {
        phi::not_null_ref_ptr<int> ptr(new int(20));

        int* raw_ptr = new int(21);
        ptr.reset(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);

        int* raw_ptr2 = new int(22);
        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);

        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
    }

    SECTION("swap")
    {
        int*                       raw_ptr  = new int(21);
        int*                       raw_ptr2 = new int(22);
        phi::not_null_ref_ptr<int> ptr(raw_ptr);
        phi::not_null_ref_ptr<int> ptr2(raw_ptr2);

        ptr.swap(ptr2);

        CHECK(ptr.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 1u);

        phi::swap(ptr, ptr2);

        CHECK(ptr.get() == raw_ptr);
        CHECK(ptr2.get() == raw_ptr2);
        CHECK(ptr.use_count() == 1u);
        CHECK(ptr2.use_count() == 1u);
    }

    SECTION("use_count")
    {
        phi::not_null_ref_ptr<int> ptr(new int(22));

        CHECK(ptr.use_count() == 1u);

        {
            // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
            phi::not_null_ref_ptr<int> shared_ptr_1(ptr);

            CHECK(ptr.use_count() == 2u);

            {
                // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
                phi::not_null_ref_ptr<int> shared_ptr_2(ptr);

                CHECK(ptr.use_count() == 3u);
                {
                    // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
                    phi::not_null_ref_ptr<int> shared_ptr_3(ptr);

                    CHECK(ptr.use_count() == 4u);
                }

                CHECK(ptr.use_count() == 3u);

                // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
                phi::not_null_ref_ptr<int> shared_ptr_4(ptr);

                CHECK(ptr.use_count() == 4u);
            }

            CHECK(ptr.use_count() == 2u);
        }

        CHECK(ptr.use_count() == 1u);
    }

    SECTION("operator TypeT*")
    {
        int*                       raw_ptr = new int(12);
        phi::not_null_ref_ptr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);
        CHECK(new_ptr == raw_ptr);
        CHECK(ptr.use_count() == 1u);

        phi::not_null_ref_ptr<int> const_ptr(ptr);

        const int* new_const_ptr = static_cast<int*>(const_ptr);
        CHECK(new_const_ptr == raw_ptr);

        Derived*                       raw_derived = new Derived();
        phi::not_null_ref_ptr<Derived> derived_ptr(raw_derived);

        Base* new_base = static_cast<Base*>(derived_ptr);
        CHECK(new_base == raw_derived);

        const phi::not_null_ref_ptr<Derived> const_derived_ptr(derived_ptr);
        const Base*                          new_const_base = static_cast<Base*>(derived_ptr);

        CHECK(new_const_base == raw_derived);
    }

    SECTION("operator->")
    {
        phi::not_null_ref_ptr<A> ptr(new A);
        CHECK(ptr->f());

        const phi::not_null_ref_ptr<A> const_ptr(new A());
        CHECK(const_ptr->f());
    }

    SECTION("operator*")
    {
        int*                       raw_ptr = new int(0);
        phi::not_null_ref_ptr<int> ptr(raw_ptr);

        CHECK(*ptr == 0);

        *raw_ptr = 12;

        CHECK(*ptr == 12);

        *ptr = 9;

        CHECK(*ptr == 9);
        CHECK(*raw_ptr == 9);

        const phi::not_null_ref_ptr<A> const_ptr(new A());
        const A&                       raw_a = *const_ptr;
        CHECK(raw_a.f());
    }

    SECTION("operator==")
    {
        phi::not_null_ref_ptr<int> ptr1(new int(1));
        phi::not_null_ref_ptr<int> ptr2(new int(2));

        CHECK_FALSE(ptr1 == ptr2);

        ptr2 = ptr1;

        CHECK(ptr1 == ptr2);
    }

    SECTION("operator== with plain pointer")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::not_null_ref_ptr<int> ptr1(raw_ptr1);
        phi::not_null_ref_ptr<int> ptr2(raw_ptr2);

        CHECK(ptr1 == raw_ptr1);
        CHECK_FALSE(ptr1 == raw_ptr2);

        CHECK_FALSE(ptr2 == raw_ptr1);
        CHECK(ptr2 == raw_ptr2);

        CHECK(raw_ptr1 == ptr1);
        CHECK_FALSE(raw_ptr2 == ptr1);

        CHECK_FALSE(raw_ptr1 == ptr2);
        CHECK(raw_ptr2 == ptr2);
    }

    SECTION("operator!=")
    {
        phi::not_null_ref_ptr<int> ptr1(new int(1));
        phi::not_null_ref_ptr<int> ptr2(new int(2));

        CHECK(ptr1 != ptr2);

        ptr2 = ptr1;

        CHECK_FALSE(ptr1 != ptr2);
    }

    SECTION("operator!= with plain pointer")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::not_null_ref_ptr<int> ptr1(raw_ptr1);
        phi::not_null_ref_ptr<int> ptr2(raw_ptr2);

        CHECK_FALSE(ptr1 != raw_ptr1);
        CHECK(ptr1 != raw_ptr2);

        CHECK(ptr2 != raw_ptr1);
        CHECK_FALSE(ptr2 != raw_ptr2);

        CHECK_FALSE(raw_ptr1 != ptr1);
        CHECK(raw_ptr2 != ptr1);

        CHECK(raw_ptr1 != ptr2);
        CHECK_FALSE(raw_ptr2 != ptr2);
    }

    SECTION("make_not_null_ref")
    {
        phi::not_null_ref_ptr<int> int_ptr = phi::make_not_null_ref<int>(3);

        CHECK(*int_ptr == 3);

        phi::not_null_ref_ptr<phi::vector2i32> vec2_ptr =
                phi::make_not_null_ref<phi::vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }
}

TEST_CASE("ref_ptr - flat")
{
    int*              raw_ptr = new int(21);
    phi::ref_ptr<int> ptr{raw_ptr};

    phi::flat_ptr flat = ptr.flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("ref_ptr - not_null_flat")
{
    int*              raw_ptr = new int(21);
    phi::ref_ptr<int> ptr{raw_ptr};

    phi::not_null_flat_ptr flat = ptr.not_null_flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("not_null_ref_ptr - flat")
{
    int*                       raw_ptr = new int(21);
    phi::not_null_ref_ptr<int> ptr{raw_ptr};

    phi::not_null_flat_ptr flat = ptr.not_null_flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("ref_ptr - observer")
{
    int*              raw_ptr = new int(21);
    phi::ref_ptr<int> ptr{raw_ptr};

    phi::observer_ptr<int> observer = ptr.observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("ref_ptr - not_null_observer")
{
    int*              raw_ptr = new int(21);
    phi::ref_ptr<int> ptr{raw_ptr};

    phi::not_null_observer_ptr<int> observer = ptr.not_null_observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("not_null_ref_ptr - observer")
{
    int*                       raw_ptr = new int(21);
    phi::not_null_ref_ptr<int> ptr{raw_ptr};

    phi::not_null_observer_ptr<int> observer = ptr.not_null_observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("ref_ptr - hash")
{
    phi::ref_ptr<int> ptr          = new int(21);
    phi::size_t       ptr_hash     = std::hash<phi::ref_ptr<int>>{}(ptr);
    phi::size_t       raw_ptr_hash = std::hash<int*>{}(ptr.get());

    CHECK(ptr_hash == raw_ptr_hash);
}

TEST_CASE("not_null_ref_ptr - hash")
{
    phi::not_null_ref_ptr<int> ptr          = new int(21);
    phi::size_t                ptr_hash     = std::hash<phi::not_null_ref_ptr<int>>{}(ptr);
    phi::size_t                raw_ptr_hash = std::hash<int*>{}(ptr.get());

    CHECK(ptr_hash == raw_ptr_hash);
}
