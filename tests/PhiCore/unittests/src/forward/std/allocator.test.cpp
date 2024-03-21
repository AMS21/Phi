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

// Required for MSVC to not complain about 'std::allocator<void>'
#if PHI_COMPILER_IS(MSVC)
#    define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING
#endif

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
