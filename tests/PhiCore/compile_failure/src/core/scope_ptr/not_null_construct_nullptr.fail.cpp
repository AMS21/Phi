#include <phi/core/scope_ptr.hpp>

int main()
{
    phi::not_null_scope_ptr<int>(nullptr);
}
