#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/container/singly_linked_list.hpp>
#include <phi/core/move.hpp>

using sll_i = phi::singly_linked_list<int>;
using sll_c = phi::singly_linked_list<char>;

TEST_CASE("container.singly_linked_list_node")
{
    using node_t = phi::singly_linked_list_node<int>;

    CHECK_SAME_TYPE(node_t::this_type, node_t);
    CHECK_SAME_TYPE(node_t::this_type, phi::singly_linked_list_node<int>);
    CHECK_SAME_TYPE(node_t::value_type, int);

    CHECK_NOEXCEPT(node_t{3});
    CHECK_NOEXCEPT(node_t{phi::move(3)});

    // Not noexcept for throwing types
    CHECK_NOT_NOEXCEPT(phi::singly_linked_list_node<ThrowDefaultClass>{ThrowDefaultClass{}});
    CHECK_NOT_NOEXCEPT(
            phi::singly_linked_list_node<ThrowDefaultClass>{phi::move(ThrowDefaultClass{})});

    node_t node{1};

    CHECK(node.value() == 1);
    CHECK_NOEXCEPT(node.value());

    CHECK(node.is_last());
    CHECK_NOEXCEPT(node.is_last());

    CHECK_FALSE(node.has_next());
    CHECK_NOEXCEPT(node.has_next());

    CHECK(node.next() == nullptr);
    CHECK_NOEXCEPT(node.next());
}

TEST_CASE("container.singly_linked_list_iterator")
{
    using it_t  = phi::singly_linked_list_iterator<phi::singly_linked_list<int>>;
    using cit_t = phi::singly_linked_list_const_iterator<phi::singly_linked_list<int>>;

    it_t null_it{};
    CHECK_FALSE(null_it.is_valid());
    CHECK_NOEXCEPT(null_it.is_valid());
    CHECK_FALSE(null_it.has_next());
    CHECK_NOEXCEPT(null_it.has_next());

    it_t null_it2{};

    CHECK(null_it == null_it);
    CHECK(null_it == null_it2);
    CHECK_NOEXCEPT(null_it == null_it);
    CHECK_FALSE(null_it != null_it);
    CHECK_FALSE(null_it != null_it2);
    CHECK_NOEXCEPT(null_it != null_it);

    cit_t null_it3;

    CHECK(null_it == null_it3);
    CHECK_FALSE(null_it != null_it3);
    CHECK_NOEXCEPT(null_it == null_it3);
}

TEST_CASE("container.singly_linked_list_const_iterator")
{
    using it_t  = phi::singly_linked_list_iterator<phi::singly_linked_list<int>>;
    using cit_t = phi::singly_linked_list_const_iterator<phi::singly_linked_list<int>>;

    cit_t null_it{};
    CHECK_FALSE(null_it.is_valid());
    CHECK_NOEXCEPT(null_it.is_valid());
    CHECK_FALSE(null_it.has_next());
    CHECK_NOEXCEPT(null_it.has_next());

    cit_t null_it2;

    CHECK(null_it == null_it);
    CHECK(null_it == null_it2);
    CHECK_NOEXCEPT(null_it == null_it2);
    CHECK_FALSE(null_it != null_it);
    CHECK_FALSE(null_it != null_it2);
    CHECK_NOEXCEPT(null_it != null_it2);

    it_t null_it3;

    CHECK(null_it == null_it3);
    CHECK_NOEXCEPT(null_it == null_it3);
    CHECK_FALSE(null_it != null_it3);
    CHECK_NOEXCEPT(null_it != null_it3);
}

TEST_CASE("container.singly_linked_list")
{
    SECTION("singly_linked_list()")
    {
        CHECK_NOEXCEPT(sll_i{});
        sll_i list;

        CHECK(list.length() == 0u);
        CHECK(list.is_empty());
    }

    SECTION("try_push_front")
    {
        sll_i list;

        /*
        REQUIRE(list.try_push_front(1));

        CHECK(list.length() == 1u);
        CHECK_FALSE(list.is_empty());
        CHECK(list.front() == 1);
        CHECK(list.back() == 1);

        int val = 3;
        REQUIRE(list.try_push_front(val));

        CHECK(list.length() == 2u);
        CHECK_FALSE(list.is_empty());
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);

        REQUIRE(list.try_push_front(5));

        CHECK(list.length() == 3u);
        CHECK_FALSE(list.is_empty());
        CHECK(list.front() == 1);
        CHECK(list.back() == 5);
        */
    }

    SECTION("push_front")
    {
        sll_i list;

        /*
        list.push_front(1);

        CHECK(list.length() == 1u);
        CHECK_FALSE(list.is_empty());
        CHECK(list.front() == 1);
        CHECK(list.back() == 1);

        int val = 3;
        list.push_front(val);

        CHECK(list.length() == 2u);
        CHECK_FALSE(list.is_empty());
        CHECK(list.front() == 1);
        CHECK(list.back() == 3);

        list.push_front(5);

        CHECK(list.length() == 3u);
        CHECK_FALSE(list.is_empty());
        CHECK(list.front() == 1);
        CHECK(list.back() == 5);
        */
    }
}
