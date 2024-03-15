#include <phi/compiler_support/constexpr.hpp>
#include <phi/core/assert.hpp>

PHI_CONSTEXPR int f(int value)
{
    if (value == 2)
    {
        return 3;
    }

    PHI_ASSERT_NOT_REACHED();

    return 0;
}

int main()
{
    static PHI_CONSTEXPR int val = f(0);
    return val;
}
