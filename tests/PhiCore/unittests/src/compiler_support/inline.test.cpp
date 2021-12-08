#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/inline.hpp>

PHI_ALWAYS_INLINE void f()
{}

PHI_NEVER_INLINE void g()
{}

TEST_CASE("Inline")
{
    f();
    g();
}
