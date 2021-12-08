#include <phi/type_traits/is_constant_evaluated.hpp>

int main()
{
    static_assert(!phi::is_constant_evaluated(), "is_constant_evaluated failed");
}
