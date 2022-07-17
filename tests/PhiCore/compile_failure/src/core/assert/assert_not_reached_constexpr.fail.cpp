#include <phi/core/assert.hpp>

constexpr int f(int value)
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
    static constexpr int val = f(0);
    return val;
}
