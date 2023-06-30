#include "phi/forward/span.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include <phi/test/test_macros.hpp>

#include <phi/container/span.hpp>

TEST_CASE("span - typedefs")
{
    // this_type
    CHECK_SAME_TYPE(phi::span<int>::this_type, phi::span<int>);
    CHECK_SAME_TYPE(phi::span<const int>::this_type, phi::span<const int>);
    CHECK_SAME_TYPE(phi::span<int, 0>::this_type, phi::span<int, 0>);
    CHECK_SAME_TYPE(phi::span<const int, 0>::this_type, phi::span<const int, 0>);
    CHECK_SAME_TYPE(phi::span<int, 1>::this_type, phi::span<int, 1>);
    CHECK_SAME_TYPE(phi::span<const int, 1>::this_type, phi::span<const int, 1>);

    // element_type
    CHECK_SAME_TYPE(phi::span<int>::element_type, int);
    CHECK_SAME_TYPE(phi::span<const int>::element_type, const int);
    CHECK_SAME_TYPE(phi::span<int, 0>::element_type, int);
    CHECK_SAME_TYPE(phi::span<const int, 0>::element_type, const int);
    CHECK_SAME_TYPE(phi::span<int, 1>::element_type, int);
    CHECK_SAME_TYPE(phi::span<const int, 1>::element_type, const int);

    // value_type
    CHECK_SAME_TYPE(phi::span<int>::value_type, int);
    CHECK_SAME_TYPE(phi::span<const int>::value_type, int);
    CHECK_SAME_TYPE(phi::span<int, 0>::value_type, int);
    CHECK_SAME_TYPE(phi::span<const int, 0>::value_type, int);
    CHECK_SAME_TYPE(phi::span<int, 1>::value_type, int);
    CHECK_SAME_TYPE(phi::span<const int, 1>::value_type, int);

    // size_type
    CHECK_SAME_TYPE(phi::span<int>::size_type, phi::usize);
    CHECK_SAME_TYPE(phi::span<int, 0>::size_type, phi::usize);
    CHECK_SAME_TYPE(phi::span<int, 1>::size_type, phi::usize);

    // difference_type
    CHECK_SAME_TYPE(phi::span<int>::difference_type, phi::ptrdiff);
    CHECK_SAME_TYPE(phi::span<int, 0>::difference_type, phi::ptrdiff);
    CHECK_SAME_TYPE(phi::span<int, 1>::difference_type, phi::ptrdiff);

    // pointer
    CHECK_SAME_TYPE(phi::span<int>::pointer, int*);
    CHECK_SAME_TYPE(phi::span<const int>::pointer, const int*);
    CHECK_SAME_TYPE(phi::span<int, 0>::pointer, int*);
    CHECK_SAME_TYPE(phi::span<const int, 0>::pointer, const int*);
    CHECK_SAME_TYPE(phi::span<int, 1>::pointer, int*);
    CHECK_SAME_TYPE(phi::span<const int, 1>::pointer, const int*);

    // const_pointer
    CHECK_SAME_TYPE(phi::span<int>::const_pointer, const int*);
    CHECK_SAME_TYPE(phi::span<const int>::const_pointer, const int*);
    CHECK_SAME_TYPE(phi::span<int, 0>::const_pointer, const int*);
    CHECK_SAME_TYPE(phi::span<const int, 0>::const_pointer, const int*);
    CHECK_SAME_TYPE(phi::span<int, 1>::const_pointer, const int*);
    CHECK_SAME_TYPE(phi::span<const int, 1>::const_pointer, const int*);

    // reference
    CHECK_SAME_TYPE(phi::span<int>::reference, int&);
    CHECK_SAME_TYPE(phi::span<const int>::reference, const int&);
    CHECK_SAME_TYPE(phi::span<int, 0>::reference, int&);
    CHECK_SAME_TYPE(phi::span<const int, 0>::reference, const int&);
    CHECK_SAME_TYPE(phi::span<int, 1>::reference, int&);
    CHECK_SAME_TYPE(phi::span<const int, 1>::reference, const int&);

    // const_reference
    CHECK_SAME_TYPE(phi::span<int>::const_reference, const int&);
    CHECK_SAME_TYPE(phi::span<const int>::const_reference, const int&);
    CHECK_SAME_TYPE(phi::span<int, 0>::const_reference, const int&);
    CHECK_SAME_TYPE(phi::span<const int, 0>::const_reference, const int&);
    CHECK_SAME_TYPE(phi::span<int, 1>::const_reference, const int&);
    CHECK_SAME_TYPE(phi::span<const int, 1>::const_reference, const int&);

    // iterator
    CHECK_SAME_TYPE(phi::span<int>::iterator, int*);
    CHECK_SAME_TYPE(phi::span<const int>::iterator, const int*);
    CHECK_SAME_TYPE(phi::span<int, 0>::iterator, int*);
    CHECK_SAME_TYPE(phi::span<const int, 0>::iterator, const int*);
    CHECK_SAME_TYPE(phi::span<int, 1>::iterator, int*);
    CHECK_SAME_TYPE(phi::span<const int, 1>::iterator, const int*);

    // const_iterator
    CHECK_SAME_TYPE(phi::span<int>::const_iterator, const int*);
    CHECK_SAME_TYPE(phi::span<const int>::const_iterator, const int*);
    CHECK_SAME_TYPE(phi::span<int, 0>::const_iterator, const int*);
    CHECK_SAME_TYPE(phi::span<const int, 0>::const_iterator, const int*);
    CHECK_SAME_TYPE(phi::span<int, 1>::const_iterator, const int*);
    CHECK_SAME_TYPE(phi::span<const int, 1>::const_iterator, const int*);

    // reverse_iterator
    CHECK_SAME_TYPE(phi::span<int>::reverse_iterator, phi::reverse_iterator<int*>);
    CHECK_SAME_TYPE(phi::span<const int>::reverse_iterator, phi::reverse_iterator<const int*>);
    CHECK_SAME_TYPE(phi::span<int, 0>::reverse_iterator, phi::reverse_iterator<int*>);
    CHECK_SAME_TYPE(phi::span<const int, 0>::reverse_iterator, phi::reverse_iterator<const int*>);
    CHECK_SAME_TYPE(phi::span<int, 1>::reverse_iterator, phi::reverse_iterator<int*>);
    CHECK_SAME_TYPE(phi::span<const int, 1>::reverse_iterator, phi::reverse_iterator<const int*>);

    // const_reverse_iterator
    CHECK_SAME_TYPE(phi::span<int>::const_reverse_iterator, phi::reverse_iterator<const int*>);
    CHECK_SAME_TYPE(phi::span<const int>::const_reverse_iterator,
                    phi::reverse_iterator<const int*>);
    CHECK_SAME_TYPE(phi::span<int, 0>::const_reverse_iterator, phi::reverse_iterator<const int*>);
    CHECK_SAME_TYPE(phi::span<const int, 0>::const_reverse_iterator,
                    phi::reverse_iterator<const int*>);
    CHECK_SAME_TYPE(phi::span<int, 1>::const_reverse_iterator, phi::reverse_iterator<const int*>);
    CHECK_SAME_TYPE(phi::span<const int, 1>::const_reverse_iterator,
                    phi::reverse_iterator<const int*>);
}

TEST_CASE("span - extent")
{
    STATIC_REQUIRE(phi::span<int, 0>::extent == 0);
    STATIC_REQUIRE(phi::span<int, 1>::extent == 1);
    STATIC_REQUIRE(phi::span<int, 2>::extent == 2);
    STATIC_REQUIRE(phi::span<int, 3>::extent == 3);
    STATIC_REQUIRE(phi::span<int, 4>::extent == 4);
    STATIC_REQUIRE(phi::span<int, 5>::extent == 5);

    STATIC_REQUIRE(phi::span<int>::extent == phi::dynamic_extent);
    STATIC_REQUIRE(phi::span<int, phi::dynamic_extent>::extent == phi::dynamic_extent);
}
