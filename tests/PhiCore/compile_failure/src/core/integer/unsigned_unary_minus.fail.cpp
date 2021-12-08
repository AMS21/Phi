#include <phi/core/integer.hpp>

int main()
{
    phi::integer<unsigned> i{7u};

    auto val = -i;

    return val.get();
}
