#include <phi/test/test_macros.hpp>

#include <phi/forward/std/allocator.hpp>

TEST_CASE("forward.std.allocator.forward")
{
    std::allocator<int>* pointer = nullptr;

    CHECK(pointer == nullptr);

#if PHI_CPP_STANDARD() <= PHI_CPLUSPLUS_17()
    std::allocator<void>* pointer2 = nullptr;
    CHECK(pointer2 == nullptr);
#endif
}

#include <memory>

TEST_CASE("forward.std.allocator")
{
    std::allocator<int> alloc;

    (void)alloc;

#if PHI_CPP_STANDARD() <= PHI_CPLUSPLUS_17()
    std::allocator<void> alloc2;
    (void)alloc2;
#endif
}
