#include <Phi/Core/ScopePtr.hpp>

int main()
{
    phi::NotNullScopePtr ptr(new int(22));

    ptr = nullptr;
}
