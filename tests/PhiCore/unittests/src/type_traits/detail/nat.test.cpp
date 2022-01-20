#include <phi/test/test_macros.hpp>

#include <phi/type_traits/detail/nat.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_complete.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <phi/type_traits/is_copy_constructible.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_destructible.hpp>
#include <phi/type_traits/is_empty.hpp>
#include <phi/type_traits/is_final.hpp>
#include <phi/type_traits/is_move_assignable.hpp>
#include <phi/type_traits/is_move_constructible.hpp>

TEST_CASE("nat")
{
    STATIC_REQUIRE_FALSE(phi::is_copy_assignable<phi::nat>::value);
    STATIC_REQUIRE_FALSE(phi::is_copy_constructible<phi::nat>::value);
#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_default_constructible<phi::nat>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_destructible<phi::nat>::value);
    STATIC_REQUIRE_FALSE(phi::is_move_assignable<phi::nat>::value);
    STATIC_REQUIRE_FALSE(phi::is_move_constructible<phi::nat>::value);

#if PHI_HAS_WORKING_IS_EMPTY()
    STATIC_REQUIRE(phi::is_empty<phi::nat>::value);
#endif
#if PHI_HAS_WORKING_IS_FINAL()
    STATIC_REQUIRE(phi::is_final<phi::nat>::value);
#endif
    STATIC_REQUIRE(phi::is_complete<phi::nat>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class<phi::nat>::value);
#endif
}
