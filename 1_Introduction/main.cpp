#include <iostream>
#include <thread>

using namespace std;

void hello_world()
{
    std::cout << "Hello, Concurrent World" << '\n';
    return;
}

int main()
{
    std::thread t{ hello_world };
    t.join();
    return 0;
}