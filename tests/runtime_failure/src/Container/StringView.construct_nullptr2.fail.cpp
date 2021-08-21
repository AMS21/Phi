#include "SetupRuntimeFailure.hpp"
#include <Phi/Container/StringView.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    phi::StringView view(ptr, 1u);
}
