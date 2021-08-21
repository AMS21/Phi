#include "SetupRuntimeFailure.hpp"
#include <Phi/Container/StringView.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::StringView view("test");

    view.remove_suffix(6u);
}
