#include <phi/type_traits/false_t.hpp>

template <typename TypeT>
void func()
{
    static_assert(phi::false_t<TypeT>::value, "TWO_PHASE_LOOKUP_FAILURE");
}

template <>
void func<int>()
{}

int main()
{
    func<float>();
}
