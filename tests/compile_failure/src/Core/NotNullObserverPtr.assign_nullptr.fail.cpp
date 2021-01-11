#include <Phi/Core/ObserverPtr.hpp>

int main()
{
    int                          i = 16;
    phi::NotNullObserverPtr<int> ptr(&i);

    ptr = nullptr;
}
