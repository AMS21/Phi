#include <phi/algorithm/string_length_unsafe.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/types.hpp>

#if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
#endif

extern "C" int LLVMFuzzerTestOneInput(const phi::uint8_t* data, phi::size_t size)
{
    if (size == 0)
    {
        return 0;
    }
    if (data[size - 1] != '\0')
    {
        return 0;
    }

    const char* string = reinterpret_cast<const char*>(data);

    phi::usize result = phi::string_length_unsafe(string);
    (void)result;

    return 0;
}
