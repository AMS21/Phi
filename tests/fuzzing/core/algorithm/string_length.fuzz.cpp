#include <phi/algorithm/string_length.hpp>
#include <phi/core/types.hpp>

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

    phi::usize result = phi::string_length(string);
    result            = phi::safe_string_length(string);

    (void)result;

    return 0;
}
