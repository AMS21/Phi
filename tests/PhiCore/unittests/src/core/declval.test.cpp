#include <phi/test/test_macros.hpp>

#include <phi/core/declval.hpp>
#include <phi/type_traits/is_same.hpp>

struct A
{
    A(const A&);
    A(A&&) noexcept;
    ~A();
    A& operator=(const A&);
    A& operator=(A&&) noexcept;
};

TEST_CASE("declval")
{
    CHECK_SAME_TYPE(decltype(phi::declval<int>()), int&&);
    CHECK_SAME_TYPE(decltype(phi::declval<A>()), A&&);
    CHECK_SAME_TYPE(decltype(phi::declval<void>()), void);
    CHECK_NOEXCEPT(phi::declval<int>());
    CHECK_NOEXCEPT(phi::declval<A>());
    CHECK_NOEXCEPT(phi::declval<void>());
}
