#include <phi/core/observer_ptr.hpp>

int main()
{
    int                             i = 16;
    phi::not_null_observer_ptr<int> ptr(&i);

    ptr = nullptr;
}
