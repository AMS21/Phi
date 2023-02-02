#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_ARCHITECTURE_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_ARCHITECTURE_HPP

#if defined(__AMDGPU__)
#    define PHI_ARCH_AMDGPU() 1
#else
#    define PHI_ARCH_AMDGPU() 0
#endif

#if defined(__NVPTX__)
#    define PHI_ARCH_NVPTX() 1
#else
#    define PHI_ARCH_NVPTX() 0
#endif

#if PHI_ARCH_AMDGPU() || PHI_ARCH_NVPTX()
#    define PHI_ARCH_GPU() 1
#else
#    define PHI_ARCH_GPU() 0
#endif

#if defined(__CLR_VER)
#    define PHI_ARCH_CLR() 1
#else
#    define PHI_ARCH_CLR() 0
#endif

#if defined(__pnacl__) || PHI_ARCH_CLR() || PHI_ARCH_GPU()
#    define PHI_ARCH_VM() 1
#else
#    define PHI_ARCH_VM() 0
#endif

#if (defined(_M_IX86) || defined(i386) || defined(__i386) || defined(__i386__)) && !PHI_ARCH_VM()
#    define PHI_ARCH_X86_32() 1
#else
#    define PHI_ARCH_X86_32() 0
#endif

#if (defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64) || defined(__x86_64__) ||           \
     defined(__amd64) || defined(__amd64__)) &&                                                    \
        !PHI_ARCH_VM()
#    define PHI_ARCH_X86_64() 1
#    define PHI_ARCH_AMD64()  1
#else
#    define PHI_ARCH_X86_64() 0
#    define PHI_ARCH_AMD64()  0
#endif

#if PHI_ARCH_X86_32() || PHI_ARCH_X86_64()
#    define PHI_ARCH_X86() 1
#else
#    define PHI_ARCH_X86() 0
#endif

#if (defined(__arm__) || defined(_M_ARM))
#    define PHI_ARCH_ARM32() 1
#else
#    define PHI_ARCH_ARM32() 0
#endif

#if defined(__aarch64__) || defined(__arm64__) || defined(_M_ARM64)
#    define PHI_ARCH_ARM64() 1
#else
#    define PHI_ARCH_ARM64() 0
#endif

#if PHI_ARCH_ARM32() || PHI_ARCH_ARM64()
#    define PHI_ARCH_ARM() 1
#else
#    define PHI_ARCH_ARM() 0
#endif

#define PHI_ARCH_IS(arch) (PHI_ARCH_##arch())

#define PHI_ARCH_IS_NOT(arch) (!PHI_ARCH_##arch())

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_ARCHITECTURE_HPP
