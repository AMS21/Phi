#include "phi/forward/ref_ptr.hpp"
#include <phi/core/ref_ptr.hpp>

int main()
{
    phi::not_null_ref_ptr<int> ptr(nullptr);
}
