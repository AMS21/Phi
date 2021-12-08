#include <phi/core/flat_ptr.hpp>

int main()
{
    int                    i = 16;
    phi::not_null_flat_ptr ptr(&i);

    ptr = nullptr;
}
