#include <phi/core/NonCopyable.hpp>

class A : phi::NonCopyable
{};

int main()
{
    A a;

    A b(a);
}
