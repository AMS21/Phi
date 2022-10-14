#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/core/flat_ptr.hpp>
#include <phi/core/observer_ptr.hpp>
#include <phi/core/ref_ptr.hpp>
#include <phi/core/scope_ptr.hpp>

struct Base
{};

struct Derived : public Base
{};

TEST_CASE("observer_ptr", "[Core][observer_ptr]")
{
    SECTION("Type aliases")
    {
        CHECK_SAME_TYPE(phi::observer_ptr<int>::this_type, phi::observer_ptr<int>);
        CHECK_SAME_TYPE(phi::observer_ptr<int>::not_null_type, phi::not_null_observer_ptr<int>);
        CHECK_SAME_TYPE(phi::observer_ptr<int>::value_type, int);
        CHECK_SAME_TYPE(phi::observer_ptr<int>::reference, int&);
        CHECK_SAME_TYPE(phi::observer_ptr<int>::const_reference, const int&);
        CHECK_SAME_TYPE(phi::observer_ptr<int>::pointer, int*);
        CHECK_SAME_TYPE(phi::observer_ptr<int>::const_pointer, const int*);
    }

    SECTION("observer_ptr()")
    {
        CONSTEXPR_RUNTIME phi::observer_ptr<int> ptr;

        STATIC_REQUIRE_FALSE(ptr);
        STATIC_REQUIRE(ptr.get() == nullptr);
    }

    SECTION("observer_ptr(nullptr_t)")
    {
        CONSTEXPR_RUNTIME phi::observer_ptr<int> ptr(nullptr);

        STATIC_REQUIRE_FALSE(ptr);
        STATIC_REQUIRE(ptr.get() == nullptr);
    }

    SECTION("observer_ptr(TypeT*)")
    {
        int                    integer = 22;
        phi::observer_ptr<int> ptr(&integer);

        CHECK(ptr);
        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 22);
    }

    SECTION("observer_ptr(OtherT*)")
    {
        Derived                 base;
        phi::observer_ptr<Base> ptr{&base};

        CHECK(ptr);
        CHECK(ptr.get() == &base);
    }

    SECTION("observer_ptr(const observer_ptr&)")
    {
        int                    integer = 21;
        phi::observer_ptr<int> ptr1(&integer);
        phi::observer_ptr<int> ptr2(ptr1);

        CHECK(ptr2);
        CHECK(ptr2.get() == &integer);
        CHECK(ptr2.get() == ptr1.get());
        CHECK(*ptr2 == 21);
    }

    SECTION("observer_ptr(observer_ptr&&)")
    {
        int                    integer = 19;
        phi::observer_ptr<int> ptr{phi::observer_ptr<int>(&integer)};

        CHECK(ptr);
        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 19);
    }

    SECTION("observer_ptr(const not_null_observer_ptr&)")
    {
        int                             integer = 66;
        phi::not_null_observer_ptr<int> not_null(&integer);

        phi::observer_ptr<int> ptr(not_null);

        CHECK(ptr);
        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 66);
    }

    SECTION("observer_ptr(not_null_observer_ptr&&)")
    {
        int                    integer = 25;
        phi::observer_ptr<int> ptr{phi::not_null_observer_ptr<int>(&integer)};

        CHECK(ptr);
        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 25);
    }

    SECTION("observer_ptr(scope_ptr&)")
    {
        phi::scope_ptr<int> scope = phi::make_scope<int>(23);

        CHECK(scope);

        phi::observer_ptr<int> ptr{scope};

        CHECK(scope);
        CHECK(ptr);
        CHECK(ptr.get() == scope.get());
    }

    SECTION("observer_ptr(not_null_scope_ptr&)")
    {
        phi::not_null_scope_ptr<int> scope = phi::make_not_null_scope<int>(23);
        phi::observer_ptr<int>       ptr{scope};

        CHECK(ptr);
        CHECK(ptr.get() == scope.get());
    }

    SECTION("observer_ptr(scope_ptr&)")
    {
        phi::ref_ptr<int> ref = phi::make_ref<int>(23);

        CHECK(ref);

        phi::observer_ptr<int> ptr{ref};

        CHECK(ref);
        CHECK(ptr);
        CHECK(ptr.get() == ref.get());
    }

    SECTION("observer_ptr(not_null_scope_ptr&)")
    {
        phi::not_null_ref_ptr<int> ref = phi::make_not_null_ref<int>(23);
        phi::observer_ptr<int>     ptr{ref};

        CHECK(ptr);
        CHECK(ptr.get() == ref.get());
    }

    SECTION("operator=(nullptr_t)")
    {
        int                    integer = 8;
        phi::observer_ptr<int> ptr(&integer);

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("operator=(TypeT*)")
    {
        int integer = 23;

        phi::observer_ptr<int> ptr;

        ptr = &integer;

        CHECK(ptr);
        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 23);
    }

    SECTION("operator=(OtherT*)")
    {
        Derived                 base;
        phi::observer_ptr<Base> ptr;

        ptr = &base;

        CHECK(ptr);
        CHECK(ptr.get() == &base);
    }

    SECTION("operator=(const observer_ptr&)")
    {
        int                    integer = 16;
        phi::observer_ptr<int> base(&integer);

        phi::observer_ptr<int> other = base;

        CHECK(other);
        CHECK(other.get() == &integer);
        CHECK(other.get() == base.get());
        CHECK(*other == 16);
    }

    SECTION("operator=(observer_ptr&&)")
    {
        int                    integer = 29;
        phi::observer_ptr<int> ptr;

        ptr = phi::observer_ptr<int>(&integer);

        CHECK(ptr);
        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 29);
    }

    SECTION("operator=(const not_null_observer_ptr&)")
    {
        int                             integer = 93;
        phi::not_null_observer_ptr<int> not_null(&integer);

        phi::observer_ptr<int> ptr = not_null;

        CHECK(ptr);
        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 93);
    }

    SECTION("operator=(not_null_observer_ptr&&)")
    {
        int                    integer = 92;
        phi::observer_ptr<int> ptr     = phi::not_null_observer_ptr<int>(&integer);

        CHECK(ptr);
        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 92);
    }

    SECTION("operator=(scope_ptr&)")
    {
        phi::scope_ptr<int>    scope = phi::make_scope<int>(42);
        phi::observer_ptr<int> ptr;

        ptr = scope;

        CHECK(ptr);
        CHECK(ptr.get() == scope.get());
    }

    SECTION("operator=(not_null_scope_ptr&)")
    {
        phi::not_null_scope_ptr<int> scope = phi::make_not_null_scope<int>(42);
        phi::observer_ptr<int>       ptr;

        ptr = scope;

        CHECK(ptr);
        CHECK(ptr.get() == scope.get());
    }

    SECTION("operator=(ref_ptr&)")
    {
        phi::ref_ptr<int>      ref = phi::make_ref<int>(42);
        phi::observer_ptr<int> ptr;

        ptr = ref;

        CHECK(ptr);
        CHECK(ptr.get() == ref.get());
    }

    SECTION("operator=(not_null_ref_ptr&)")
    {
        phi::not_null_ref_ptr<int> ref = phi::make_not_null_ref<int>(42);
        phi::observer_ptr<int>     ptr;

        ptr = ref;

        CHECK(ptr);
        CHECK(ptr.get() == ref.get());
    }

    SECTION("operator bool")
    {
        int                    integer = 99;
        phi::observer_ptr<int> true_ptr(&integer);
        phi::observer_ptr<int> false_ptr(nullptr);

        CHECK(true_ptr);
        CHECK_FALSE(false_ptr);
    }

    SECTION("operator boolean")
    {
        int                    integer = 77;
        phi::observer_ptr<int> true_ptr(&integer);
        phi::observer_ptr<int> false_ptr(nullptr);

        CHECK(static_cast<phi::boolean>(true_ptr));
        CHECK_FALSE(static_cast<phi::boolean>(false_ptr));
    }

    SECTION("operator TypeT*")
    {
        int                    integer = 55;
        phi::observer_ptr<int> ptr(&integer);

        CHECK(static_cast<int*>(ptr) == &integer);
    }

    SECTION("get")
    {
        int                    integer = 42;
        phi::observer_ptr<int> ptr;

        CHECK(ptr.get() == nullptr);

        ptr = &integer;

        CHECK(ptr.get() == &integer);
    }

    SECTION("release")
    {
        int                    integer = 25;
        phi::observer_ptr<int> ptr(&integer);

        int* i_ptr = ptr.release();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
        REQUIRE(i_ptr);
        CHECK(i_ptr == &integer);
    }

    SECTION("release_not_null")
    {
        int                    integer = 63;
        phi::observer_ptr<int> ptr(&integer);

        phi::not_null_observer_ptr<int> not_null = ptr.release_not_null();

        CHECK(not_null.get() == &integer);
        CHECK(*not_null == 63);
    }

    SECTION("reset")
    {
        int                    integer1 = 19;
        int                    integer2 = 666;
        phi::observer_ptr<int> ptr(&integer1);

        ptr.reset();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr.reset(&integer2);

        REQUIRE(ptr);
        CHECK(ptr.get() == &integer2);
        CHECK(*ptr == 666);
    }

    SECTION("swap")
    {
        int integer1 = 1;
        int integer2 = 2;

        phi::observer_ptr<int> pointer1 = &integer1;
        phi::observer_ptr<int> pointer2 = &integer2;

        pointer1.swap(pointer2);

        REQUIRE(pointer1);
        REQUIRE(pointer2);
        CHECK(pointer1.get() == &integer2);
        CHECK(pointer2.get() == &integer1);

        pointer1.swap(pointer2);

        REQUIRE(pointer1);
        REQUIRE(pointer2);
        CHECK(pointer1.get() == &integer1);
        CHECK(pointer2.get() == &integer2);

        pointer1.swap(pointer1);

        REQUIRE(pointer1);
        REQUIRE(pointer2);
        CHECK(pointer1.get() == &integer1);
        CHECK(pointer2.get() == &integer2);
    }

    SECTION("operator==")
    {
        int integer1 = 1;
        int integer2 = 2;
        int integer3 = 3;

        phi::observer_ptr<int> pointer1 = &integer1;
        phi::observer_ptr<int> pointer2 = &integer2;
        phi::observer_ptr<int> pointer3 = &integer3;

        CHECK(pointer1 == pointer1);
        CHECK(pointer2 == pointer2);
        CHECK(pointer3 == pointer3);

        CHECK_FALSE(pointer1 == nullptr);
        CHECK_FALSE(pointer2 == nullptr);
        CHECK_FALSE(pointer3 == nullptr);
        CHECK_FALSE(nullptr == pointer1);
        CHECK_FALSE(nullptr == pointer2);
        CHECK_FALSE(nullptr == pointer3);

        CHECK_FALSE(pointer1 == pointer2);
        CHECK_FALSE(pointer1 == pointer3);
        CHECK_FALSE(pointer2 == pointer3);

        pointer2 = &integer3;

        CHECK_FALSE(pointer1 == pointer2);
        CHECK_FALSE(pointer1 == pointer3);
        CHECK(pointer2 == pointer3);

        pointer1 = nullptr;

        CHECK(pointer1 == nullptr);
        CHECK(nullptr == pointer1);

        CHECK_FALSE(pointer1 == pointer2);
        CHECK_FALSE(pointer1 == pointer3);

        pointer3.reset();

        CHECK(pointer1 == pointer3);
    }

    SECTION("operator!=")
    {
        int integer1 = 1;
        int integer2 = 2;
        int integer3 = 3;

        phi::observer_ptr<int> pointer1 = &integer1;
        phi::observer_ptr<int> pointer2 = &integer2;
        phi::observer_ptr<int> pointer3 = &integer3;

        CHECK_FALSE(pointer1 != pointer1);
        CHECK_FALSE(pointer2 != pointer2);
        CHECK_FALSE(pointer3 != pointer3);

        CHECK(pointer1 != nullptr);
        CHECK(pointer2 != nullptr);
        CHECK(pointer3 != nullptr);
        CHECK(nullptr != pointer1);
        CHECK(nullptr != pointer2);
        CHECK(nullptr != pointer3);

        CHECK(pointer1 != pointer2);
        CHECK(pointer1 != pointer3);
        CHECK(pointer2 != pointer3);

        pointer2 = &integer3;

        CHECK(pointer1 != pointer2);
        CHECK(pointer1 != pointer3);
        CHECK_FALSE(pointer2 != pointer3);

        pointer1 = nullptr;

        CHECK_FALSE(pointer1 != nullptr);
        CHECK_FALSE(nullptr != pointer1);

        CHECK(pointer1 != pointer2);
        CHECK(pointer1 != pointer3);

        pointer3.reset();

        CHECK_FALSE(pointer1 != pointer3);
    }

    SECTION("operator== not_null_observer_ptr")
    {
        int integer1 = 5;
        int integer2 = 7;

        phi::observer_ptr<int>          null;
        phi::observer_ptr<int>          ptr(&integer1);
        phi::not_null_observer_ptr<int> not_null(&integer2);

        CHECK_FALSE(null == ptr);
        CHECK_FALSE(null == not_null);
        CHECK_FALSE(ptr == not_null);

        CHECK_FALSE(ptr == null);
        CHECK_FALSE(not_null == null);
        CHECK_FALSE(not_null == ptr);

        ptr = &integer2;

        CHECK(ptr == not_null);
        CHECK(not_null == ptr);
    }

    SECTION("operator!= not_null_observer_ptr")
    {
        int integer1 = 5;
        int integer2 = 7;

        phi::observer_ptr<int>          null;
        phi::observer_ptr<int>          ptr(&integer1);
        phi::not_null_observer_ptr<int> not_null(&integer2);

        CHECK(null != ptr);
        CHECK(null != not_null);
        CHECK(ptr != not_null);

        CHECK(ptr != null);
        CHECK(not_null != null);
        CHECK(not_null != ptr);

        ptr = &integer2;

        CHECK_FALSE(ptr != not_null);
        CHECK_FALSE(not_null != ptr);
    }

    SECTION("hash")
    {
        int         integer   = 62;
        phi::size_t null_hash = std::hash<phi::observer_ptr<int>>{}(nullptr);
        phi::size_t i_hash    = std::hash<phi::observer_ptr<int>>{}(&integer);

        CHECK(null_hash != i_hash);
        CHECK(null_hash == std::hash<int*>{}(nullptr));
        CHECK(i_hash == std::hash<int*>{}(&integer));
    }
}

TEST_CASE("not_null_observer_ptr", "[Core][observer_ptr][NotNullnot_null_observer_ptr]")
{
    SECTION("Type aliases")
    {
        CHECK_SAME_TYPE(phi::not_null_observer_ptr<int>::this_type,
                        phi::not_null_observer_ptr<int>);
        CHECK_SAME_TYPE(phi::not_null_observer_ptr<int>::value_type, int);
        CHECK_SAME_TYPE(phi::not_null_observer_ptr<int>::reference, int&);
        CHECK_SAME_TYPE(phi::not_null_observer_ptr<int>::const_reference, const int&);
        CHECK_SAME_TYPE(phi::not_null_observer_ptr<int>::pointer, int*);
        CHECK_SAME_TYPE(phi::not_null_observer_ptr<int>::const_pointer, const int*);
    }

    SECTION("not_null_observer_ptr(TypeT*)")
    {
        int                             integer = 22;
        phi::not_null_observer_ptr<int> ptr(&integer);

        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 22);
    }

    SECTION("not_null_observer_ptr(OtherT*)")
    {
        Derived                          dervied;
        phi::not_null_observer_ptr<Base> ptr(&dervied);

        CHECK(ptr.get() == &dervied);
    }

    SECTION("not_null_observer_ptr(not_null_scope_ptr&)")
    {
        phi::not_null_scope_ptr<int>    scope = phi::make_not_null_scope<int>(42);
        phi::not_null_observer_ptr<int> ptr{scope};

        CHECK(ptr.get() == scope.get());
    }

    SECTION("not_null_observer_ptr(not_null_ref_ptr&)")
    {
        phi::not_null_ref_ptr<int>      ref = phi::make_not_null_ref<int>(42);
        phi::not_null_observer_ptr<int> ptr{ref};

        CHECK(ptr.get() == ref.get());
    }

    SECTION("not_null_observer_ptr(const not_null_observer_ptr&)")
    {
        int                             integer = 21;
        phi::not_null_observer_ptr<int> ptr1(&integer);
        phi::not_null_observer_ptr<int> ptr2(ptr1);

        CHECK(ptr2.get() == &integer);
        CHECK(ptr2.get() == ptr1.get());
        CHECK(*ptr2 == 21);
    }

    SECTION("not_null_observer_ptr(not_null_observer_ptr&&)")
    {
        int                             integer = 19;
        phi::not_null_observer_ptr<int> ptr{phi::not_null_observer_ptr<int>(&integer)};

        CHECK(ptr.get() == &integer);
        CHECK(*ptr == 19);
    }

    SECTION("operator=(TypeT*)")
    {
        int integer1 = 11;
        int integer2 = 23;

        phi::not_null_observer_ptr<int> ptr(&integer1);

        ptr = &integer2;

        CHECK(ptr.get() == &integer2);
        CHECK(*ptr == 23);
    }

    SECTION("operator=(const not_null_observer_ptr&)")
    {
        int                             integer = 16;
        phi::not_null_observer_ptr<int> base(&integer);

        phi::not_null_observer_ptr<int> other = base;

        CHECK(other.get() == &integer);
        CHECK(other.get() == base.get());
        CHECK(*other == 16);
    }

    SECTION("operator=(not_null_observer_ptr&&)")
    {
        int                             integer1 = 29;
        int                             integer2 = 17;
        phi::not_null_observer_ptr<int> ptr(&integer1);

        ptr = phi::not_null_observer_ptr<int>(&integer2);

        CHECK(ptr.get() == &integer2);
        CHECK(*ptr == 17);
    }

    SECTION("operator=(not_null_scope_ptr&)")
    {
        int                             dummy = 42;
        phi::not_null_scope_ptr<int>    scope = phi::make_not_null_scope<int>(42);
        phi::not_null_observer_ptr<int> ptr{&dummy};

        ptr = scope;

        CHECK(ptr.get() == scope.get());
    }

    SECTION("operator=(not_null_ref_ptr&)")
    {
        int                             dummy = 21;
        phi::not_null_ref_ptr<int>      ref   = phi::make_not_null_ref<int>(42);
        phi::not_null_observer_ptr<int> ptr{&dummy};

        ptr = ref;

        CHECK(ptr.get() == ref.get());
    }

    SECTION("operator TypeT*")
    {
        int                             integer = 55;
        phi::not_null_observer_ptr<int> ptr(&integer);

        CHECK(static_cast<int*>(ptr) == &integer);
    }

    SECTION("get")
    {
        int                             integer = 42;
        phi::not_null_observer_ptr<int> ptr(&integer);

        CHECK(ptr.get() == &integer);
    }

    SECTION("reset")
    {
        int                             integer1 = 19;
        int                             integer2 = 666;
        phi::not_null_observer_ptr<int> ptr(&integer1);

        ptr.reset(&integer2);

        CHECK(ptr.get() == &integer2);
        CHECK(*ptr == 666);
    }

    SECTION("swap")
    {
        int integer1 = 1;
        int integer2 = 2;

        phi::not_null_observer_ptr<int> pointer1 = &integer1;
        phi::not_null_observer_ptr<int> pointer2 = &integer2;

        pointer1.swap(pointer2);

        CHECK(pointer1.get() == &integer2);
        CHECK(pointer2.get() == &integer1);

        pointer1.swap(pointer2);

        CHECK(pointer1.get() == &integer1);
        CHECK(pointer2.get() == &integer2);

        pointer1.swap(pointer1);

        CHECK(pointer1.get() == &integer1);
        CHECK(pointer2.get() == &integer2);
    }

    SECTION("operator==")
    {
        int integer1 = 1;
        int integer2 = 2;
        int integer3 = 3;

        phi::not_null_observer_ptr<int> pointer1 = &integer1;
        phi::not_null_observer_ptr<int> pointer2 = &integer2;
        phi::not_null_observer_ptr<int> pointer3 = &integer3;

        CHECK(pointer1 == pointer1);
        CHECK(pointer2 == pointer2);
        CHECK(pointer3 == pointer3);

        CHECK_FALSE(pointer1 == pointer2);
        CHECK_FALSE(pointer1 == pointer3);
        CHECK_FALSE(pointer2 == pointer3);

        pointer2 = &integer3;

        CHECK_FALSE(pointer1 == pointer2);
        CHECK_FALSE(pointer1 == pointer3);
        CHECK(pointer2 == pointer3);
    }

    SECTION("operator!=")
    {
        int integer1 = 1;
        int integer2 = 2;
        int integer3 = 3;

        phi::not_null_observer_ptr<int> pointer1 = &integer1;
        phi::not_null_observer_ptr<int> pointer2 = &integer2;
        phi::not_null_observer_ptr<int> pointer3 = &integer3;

        CHECK_FALSE(pointer1 != pointer1);
        CHECK_FALSE(pointer2 != pointer2);
        CHECK_FALSE(pointer3 != pointer3);

        CHECK(pointer1 != pointer2);
        CHECK(pointer1 != pointer3);
        CHECK(pointer2 != pointer3);

        pointer2 = &integer3;

        CHECK(pointer1 != pointer2);
        CHECK(pointer1 != pointer3);
        CHECK_FALSE(pointer2 != pointer3);
    }

    SECTION("hash")
    {
        int         integer1    = 62;
        int         integer2    = 14;
        phi::size_t first_hash  = std::hash<phi::not_null_observer_ptr<int>>{}(&integer1);
        phi::size_t second_hash = std::hash<phi::not_null_observer_ptr<int>>{}(&integer2);

        CHECK(first_hash != second_hash);
        CHECK(first_hash == std::hash<int*>{}(&integer1));
        CHECK(second_hash == std::hash<int*>{}(&integer2));
    }
}

TEST_CASE("make_observer")
{
    int integer = 23;

    auto ptr = phi::make_observer(&integer);

    CHECK(ptr);
    CHECK(ptr.get() == &integer);
}

TEST_CASE("make_not_null_observer")
{
    int integer = 23;

    auto ptr = phi::make_not_null_observer(&integer);

    CHECK(ptr.get() == &integer);
}

TEST_CASE("observer_ptr - flat")
{
    int                    i = 21;
    phi::observer_ptr<int> ptr{&i};

    phi::flat_ptr flat = ptr.flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == &i);
}

TEST_CASE("observer_ptr - not_null_flat")
{
    int                    i = 21;
    phi::observer_ptr<int> ptr{&i};

    phi::not_null_flat_ptr flat = ptr.not_null_flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == &i);
}

TEST_CASE("not_null_observer_ptr - flat")
{
    int                             i = 21;
    phi::not_null_observer_ptr<int> ptr{&i};

    phi::not_null_flat_ptr flat = ptr.not_null_flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == &i);
}
