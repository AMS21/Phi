#include <phi/core/scope_ptr.hpp>

int main()
{
    phi::not_null_scope_ptr<int> ptr(new int(21));

    ptr.reset(nullptr);
}
