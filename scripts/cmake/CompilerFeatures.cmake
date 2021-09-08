phi_include_guard()

include(CheckCXXSourceCompiles)

# Intrinsics
check_cxx_source_compiles("int main() { int i = 5; __builtin_addressof(i);}"
                          PHI_HAS_INTRINSIC_BUILTIN_ADDRESS_OF)

# Extensions
check_cxx_source_compiles("#define M(...) 1
int main() { return M(); }" PHI_HAS_EXTENSION_VARIADIC_MACRO_ZERO_ARGS)

# configure file
configure_file("scripts/cmake/Features.hpp.in"
               "generated_files/include/Phi/CompilerSupport/Features.hpp")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated_files/include)
