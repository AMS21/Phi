#include <phi/core/address_of.hpp>

int main()
{
    const int* p = phi::address_of<const int>(0);
}
