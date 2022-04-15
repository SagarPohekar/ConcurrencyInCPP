#include <iostream>
#include <thread>

using namespace std;

class background_task
{
    void do_something() const
    {
        std::cout << __func__ << '\n';
    }

    void do_something_else() const
    {
        std::cout << __func__ << '\n';
    }
public:
    void operator()() const
    {
        do_something();
        do_something_else();
    }
};

int main()
{
    background_task f{};
    std::thread t{ f };
    t.join();
    return 0;
}