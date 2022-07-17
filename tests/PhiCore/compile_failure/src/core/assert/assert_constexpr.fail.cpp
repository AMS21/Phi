#include <phi/core/assert.hpp>

constexpr int f(int value)
{
    PHI_ASSERT(value != 0, "No division by zero");

    return value / 2;
}

int main()
{
    static constexpr int res = f(0);
    return res;
}
