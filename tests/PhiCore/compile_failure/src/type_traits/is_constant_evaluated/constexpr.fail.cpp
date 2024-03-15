#include <phi/compiler_support/constexpr.hpp>
#include <phi/type_traits/is_constant_evaluated.hpp>

int main()
{
    PHI_CONSTEXPR bool b = phi::is_constant_evaluated();
    static_assert(!b, "is_constant_evaluated failure");
}
