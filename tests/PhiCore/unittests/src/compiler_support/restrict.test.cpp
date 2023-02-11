#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/restrict.hpp>
#include <phi/compiler_support/unused.hpp>

inline void f(int* PHI_RESTRICT arg)
{
    PHI_UNUSED_PARAMETER(arg);
}
