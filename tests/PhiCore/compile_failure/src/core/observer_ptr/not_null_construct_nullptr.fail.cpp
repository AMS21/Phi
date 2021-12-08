#include <phi/core/observer_ptr.hpp>

int main()
{
    phi::not_null_observer_ptr<int> ptr(nullptr);
}
