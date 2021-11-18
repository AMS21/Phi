#include <Phi/Test/TestMacros.hpp>

#include <Phi/Config/Inline.hpp>

PHI_ALWAYS_INLINE void f()
{}

PHI_NEVER_INLINE void g()
{}

TEST_CASE("Inline")
{
    f();
    g();
}
