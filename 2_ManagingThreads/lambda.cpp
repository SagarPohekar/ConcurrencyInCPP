#include <iostream>
#include <thread>

using namespace std;

int main()
{
    std::thread my_thread{ 
        []()
        {
            std::cout << __func__ << '\n';
        }
    };
    my_thread.join();
    return 0;
}