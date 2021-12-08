#include <phi/type_traits/is_constant_evaluated.hpp>

int main()
{
    constexpr bool b = phi::is_constant_evaluated();
    static_assert(!b, "is_constant_evaluated failure");
}
