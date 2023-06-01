#include <phi/test/test_macros.hpp>

#include <phi/core/assert.hpp>
#include <phi/core/observer_ptr.hpp>
#include <phi/core/pointer_traits.hpp>
#include <phi/core/ptrdiff_t.hpp>
#include <phi/core/ref_ptr.hpp>
#include <phi/core/scope_ptr.hpp>

TEST_CASE("core.pointer_traits.this_type")
{
    CHECK_SAME_TYPE(phi::pointer_traits<void*>::this_type, phi::pointer_traits<void*>);
    CHECK_SAME_TYPE(phi::pointer_traits<int*>::this_type, phi::pointer_traits<int*>);

    CHECK_SAME_TYPE(phi::pointer_traits<phi::observer_ptr<int>>::this_type,
                    phi::pointer_traits<phi::observer_ptr<int>>);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::ref_ptr<int>>::this_type,
                    phi::pointer_traits<phi::ref_ptr<int>>);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::scope_ptr<int>>::this_type,
                    phi::pointer_traits<phi::scope_ptr<int>>);
}

TEST_CASE("core.pointer_traits.pointer")
{
    CHECK_SAME_TYPE(phi::pointer_traits<void*>::pointer, void*);
    CHECK_SAME_TYPE(phi::pointer_traits<int*>::pointer, int*);

    CHECK_SAME_TYPE(phi::pointer_traits<phi::observer_ptr<int>>::pointer, phi::observer_ptr<int>);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::ref_ptr<int>>::pointer, phi::ref_ptr<int>);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::scope_ptr<int>>::pointer, phi::scope_ptr<int>);
}

struct A
{
    using element_type    = char;
    using difference_type = float;
};

TEST_CASE("core.pointer_traits.difference_type")
{
    CHECK_SAME_TYPE(phi::pointer_traits<void*>::difference_type, phi::ptrdiff_t);
    CHECK_SAME_TYPE(phi::pointer_traits<int*>::difference_type, phi::ptrdiff_t);

    CHECK_SAME_TYPE(phi::pointer_traits<phi::observer_ptr<int>>::difference_type, phi::ptrdiff_t);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::ref_ptr<int>>::difference_type, phi::ptrdiff_t);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::scope_ptr<int>>::difference_type, phi::ptrdiff_t);

    CHECK_SAME_TYPE(phi::pointer_traits<A>::difference_type, float);
}

TEST_CASE("core.pointer_traits.element_type")
{
    CHECK_SAME_TYPE(phi::pointer_traits<void*>::element_type, void);
    CHECK_SAME_TYPE(phi::pointer_traits<int*>::element_type, int);

    CHECK_SAME_TYPE(phi::pointer_traits<phi::observer_ptr<int>>::element_type, int);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::ref_ptr<int>>::element_type, int);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::scope_ptr<int>>::element_type, int);

    CHECK_SAME_TYPE(phi::pointer_traits<A>::element_type, char);
}

TEST_CASE("core.pointer_traits.rebind")
{
    CHECK_SAME_TYPE(phi::pointer_traits<void*>::rebind<int>, int*);
    CHECK_SAME_TYPE(phi::pointer_traits<int*>::rebind<void>, void*);

    CHECK_SAME_TYPE(phi::pointer_traits<phi::observer_ptr<int>>::rebind<double>,
                    phi::observer_ptr<double>);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::ref_ptr<int>>::rebind<double>, phi::ref_ptr<double>);
    CHECK_SAME_TYPE(phi::pointer_traits<phi::scope_ptr<int>>::rebind<double>,
                    phi::scope_ptr<double>);
}

constexpr bool test_pointer_to()
{
    {
        int i = 0;
        CHECK_SAME_TYPE(decltype(std::pointer_traits<int*>::pointer_to(i)), int*);
        PHI_RELEASE_ASSERT(phi::pointer_traits<int*>::pointer_to(i) == &i);
    }
    {
        int i = 0;
        CHECK_SAME_TYPE(decltype(std::pointer_traits<const int*>::pointer_to(i)), const int*);
        PHI_RELEASE_ASSERT(phi::pointer_traits<const int*>::pointer_to(i) == &i);
    }
    return true;
}

TEST_CASE("core.pointer_traits.pointer_to")
{
    test_pointer_to();
    STATIC_REQUIRE(test_pointer_to());

    {
        // Check that pointer_traits<void*> is still well-formed, even though it has no pointer_to.
        CHECK_SAME_TYPE(phi::pointer_traits<void*>::element_type, void);
        CHECK_SAME_TYPE(phi::pointer_traits<const void*>::element_type, const void);
        CHECK_SAME_TYPE(phi::pointer_traits<volatile void*>::element_type, volatile void);
    }
}
