#include <phi/type_traits/static_clamp.hpp>

int main()
{
    static_assert(phi::static_clamp<0, 1, 0>::value == 1, "");
}
