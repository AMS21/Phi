#include <Phi/Meta/AlwaysFalse.hpp>

template <typename TypeT>
void func()
{
    static_assert(phi::always_false<TypeT>, "TWO_PHASE_LOOKUP_FAILURE");
}

template <>
void func<int>()
{}

int main()
{
    func<float>();
}
