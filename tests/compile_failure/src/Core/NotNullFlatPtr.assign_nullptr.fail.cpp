#include <Phi/Core/FlatPtr.hpp>

int main()
{
    int                 i = 16;
    phi::NotNullFlatPtr ptr(&i);

    ptr = nullptr;
}
