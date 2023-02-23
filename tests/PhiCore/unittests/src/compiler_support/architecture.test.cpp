#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/architecture.hpp>

TEST_CASE("Architecture")
{
#if PHI_ARCH_IS(AMDGPU)
    STATIC_REQUIRE(PHI_ARCH_IS(AMDGPU));
    STATIC_REQUIRE(PHI_ARCH_AMDGPU());
    STATIC_REQUIRE(PHI_ARCH_GPU());
    STATIC_REQUIRE(PHI_ARCH_VM());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(AMDGPU));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(AMDGPU));
    STATIC_REQUIRE_FALSE(PHI_ARCH_AMDGPU());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(AMDGPU));
#endif

#if PHI_ARCH_IS(NVPTX)
    STATIC_REQUIRE(PHI_ARCH_IS(NVPTX));
    STATIC_REQUIRE(PHI_ARCH_NVPTX());
    STATIC_REQUIRE(PHI_ARCH_GPU());
    STATIC_REQUIRE(PHI_ARCH_VM());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(NVPTX));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(NVPTX));
    STATIC_REQUIRE_FALSE(PHI_ARCH_NVPTX());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(NVPTX));
#endif

#if PHI_ARCH_IS(GPU)
    STATIC_REQUIRE(PHI_ARCH_IS(GPU));
    STATIC_REQUIRE(PHI_ARCH_AMDGPU() || PHI_ARCH_NVPTX());
    STATIC_REQUIRE(PHI_ARCH_GPU());
    STATIC_REQUIRE(PHI_ARCH_VM());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(GPU));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(GPU));
    STATIC_REQUIRE_FALSE(PHI_ARCH_GPU());
    STATIC_REQUIRE_FALSE(PHI_ARCH_AMDGPU());
    STATIC_REQUIRE_FALSE(PHI_ARCH_NVPTX());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(GPU));
#endif

#if PHI_ARCH_IS(CLR)
    STATIC_REQUIRE(PHI_ARCH_IS(CLR));
    STATIC_REQUIRE(PHI_ARCH_CLR());
    STATIC_REQUIRE(PHI_ARCH_VM());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(CLR));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(CLR));
    STATIC_REQUIRE_FALSE(PHI_ARCH_CLR());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(CLR));
#endif

#if PHI_ARCH_IS(VM)
    STATIC_REQUIRE(PHI_ARCH_IS(VM));
    STATIC_REQUIRE(PHI_ARCH_VM());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(VM));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(VM));
    STATIC_REQUIRE_FALSE(PHI_ARCH_VM());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(VM));
#endif

#if PHI_ARCH_IS(X86_32)
    STATIC_REQUIRE(PHI_ARCH_IS(X86_32));
    STATIC_REQUIRE(PHI_ARCH_X86_32());
    STATIC_REQUIRE(PHI_ARCH_X86());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(x86_32));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(X86_32));
    STATIC_REQUIRE_FALSE(PHI_ARCH_X86_32());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(X86_32));
#endif

#if PHI_ARCH_IS(X86_64)
    STATIC_REQUIRE(PHI_ARCH_IS(X86_64));
    STATIC_REQUIRE(PHI_ARCH_X86_64());
    STATIC_REQUIRE(PHI_ARCH_X86());
    STATIC_REQUIRE(PHI_ARCH_AMD64());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(X86_64));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(X86_64));
    STATIC_REQUIRE_FALSE(PHI_ARCH_X86_64());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(X86_64));
#endif

#if PHI_ARCH_IS(AMD64)
    STATIC_REQUIRE(PHI_ARCH_IS(AMD64));
    STATIC_REQUIRE(PHI_ARCH_X86_64());
    STATIC_REQUIRE(PHI_ARCH_X86());
    STATIC_REQUIRE(PHI_ARCH_AMD64());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(AMD64));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(AMD64));
    STATIC_REQUIRE_FALSE(PHI_ARCH_AMD64());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(AMD64));
#endif

#if PHI_ARCH_IS(X86)
    STATIC_REQUIRE(PHI_ARCH_IS(X86));
    STATIC_REQUIRE(PHI_ARCH_X86());
    STATIC_REQUIRE(PHI_ARCH_X86_32() || PHI_ARCH_X86_64());
    STATIC_REQUIRE(PHI_ARCH_X86_32() || PHI_ARCH_AMD64());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(X86));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(X86));
    STATIC_REQUIRE_FALSE(PHI_ARCH_X86());
    STATIC_REQUIRE_FALSE(PHI_ARCH_X86_32());
    STATIC_REQUIRE_FALSE(PHI_ARCH_X86_32());
    STATIC_REQUIRE_FALSE(PHI_ARCH_AMD64());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(X86));
#endif

#if PHI_ARCH_IS(ARM32)
    STATIC_REQUIRE(PHI_ARCH_IS(ARM32));
    STATIC_REQUIRE(PHI_ARCH_ARM32());
    STATIC_REQUIRE(PHI_ARCH_ARM());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(ARM32));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(ARM32));
    STATIC_REQUIRE_FALSE(PHI_ARCH_ARM32());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(ARM32));
#endif

#if PHI_ARCH_IS(ARM64)
    STATIC_REQUIRE(PHI_ARCH_IS(ARM64));
    STATIC_REQUIRE(PHI_ARCH_ARM64());
    STATIC_REQUIRE(PHI_ARCH_ARM());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(ARM64));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(ARM64));
    STATIC_REQUIRE_FALSE(PHI_ARCH_ARM64());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(ARM64));
#endif

#if PHI_ARCH_IS(ARM)
    STATIC_REQUIRE(PHI_ARCH_IS(ARM));
    STATIC_REQUIRE(PHI_ARCH_ARM());
    STATIC_REQUIRE(PHI_ARCH_ARM32() || PHI_ARCH_ARM64());
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS_NOT(ARM));
#else
    STATIC_REQUIRE_FALSE(PHI_ARCH_IS(ARM));
    STATIC_REQUIRE_FALSE(PHI_ARCH_ARM());
    STATIC_REQUIRE_FALSE(PHI_ARCH_ARM32());
    STATIC_REQUIRE_FALSE(PHI_ARCH_ARM64());
    STATIC_REQUIRE(PHI_ARCH_IS_NOT(ARM));
#endif
}