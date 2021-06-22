#include <Phi/Window/Window.hpp>
#include <chrono>
#include <thread>

int main()
{
    phi::Window window{"Test"};

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
