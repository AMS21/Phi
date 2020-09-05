#include <cstdlib>
#include <iostream>

constexpr int RETURN_SUCCESS{1};
constexpr int RETURN_FAILURE{0};

int main(int argc, char* argv[])
{
    // Requires atleast one commandline argument
    if (argc < 2)
    {
        std::cout << "[RuntimeFailureRunner] requires at least 1 command line argument!\n";
        return RETURN_FAILURE;
    }

    // Check if the host enviroment has a command processor
    const int has_cmd_processor = std::system(nullptr);
    if (has_cmd_processor == 0)
    {
        std::cout << "[RuntimeFailureRunner] Host enviroment seems to be missing a command "
                     "processor!\n";
        return RETURN_FAILURE;
    }

    // Create thread to run our program
    std::cout << std::flush;
    int return_value = std::system(argv[1]);

    // Interpret the value
    if (return_value != 0)
    {
        return RETURN_SUCCESS;
    }

    return RETURN_FAILURE;
}
