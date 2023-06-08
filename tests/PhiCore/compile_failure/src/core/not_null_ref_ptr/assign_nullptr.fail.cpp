#include <phi/core/ref_ptr.hpp>

int main()
{
    phi::not_null_ref_ptr<int> ptr(new int(21));

    ptr = nullptr;
}
