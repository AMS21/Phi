#include "SetupRuntimeFailure.hpp"
#include <phi/container/string_view.hpp>

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    phi::string_view view(ptr);
}
