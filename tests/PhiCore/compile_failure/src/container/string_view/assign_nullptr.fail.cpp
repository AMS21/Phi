#include <phi/container/string_view.hpp>

int main()
{
    const phi::not_null_string_view view = "string";

    view = nullptr;
}
