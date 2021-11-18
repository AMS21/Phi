#include <Phi/Core/ScopePtr.hpp>

int main()
{
    phi::NotNullScopePtr<int> ptr(new int(21));

    ptr.reset(nullptr);
}
