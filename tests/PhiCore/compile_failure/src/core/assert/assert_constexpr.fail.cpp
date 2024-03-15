#include <phi/compiler_support/constexpr.hpp>
#include <phi/core/assert.hpp>

PHI_CONSTEXPR int f(int value)
{
    PHI_ASSERT(value != 0, "No division by zero");

    return value / 2;
}

int main()
{
    static PHI_CONSTEXPR int res = f(0);
    return res;
}
