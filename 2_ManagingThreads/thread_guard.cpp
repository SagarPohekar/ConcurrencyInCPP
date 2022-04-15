#include <iostream>
#include <thread>

using namespace std;

class thread_guard
{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_): t{ t_ } {}
    ~thread_guard()
    {
        if (t.joinable())
            t.join();
    }

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
};


struct func
{
    int& i;
    func(int& i_) : i{ i_ }{}
    void operator()()
    {
        for(unsigned j = 0; j < 1'000'00; ++j)
        {
            do_something(i);
        }
    }

    void do_something(int n)
    {
        std::cout << n << '\n';
    }
};

void thread_guard_test()
{
    int some_local_state = 0;
    func my_func{ some_local_state };
    std::thread t{ my_func };
    thread_guard g{ t };
    
    //do something in the current thread
    std::cout << std::this_thread::get_id() << '\n';
}

int main()
{
    thread_guard_test();
    return 0;
}