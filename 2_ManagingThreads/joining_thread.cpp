#include <iostream>
#include <thread>
#include <vector>

using namespace std;

class joining_thread
{
    std::thread t;

public:
    joining_thread() noexcept = default;

    template<typename Callable, typename ... Args>
    explicit joining_thread(Callable&& func, Args&&... args):
        t{ std::forward<Callable>(func), std::forward<Args>(args)... }
        {

        }
    
    explicit joining_thread(std::thread t_) noexcept: t{ std::move(t_)} {}

    joining_thread(joining_thread&& other) noexcept: t{ std::move(other.t)}{}

    joining_thread& operator=(joining_thread&& other) noexcept
    {
        if (t.joinable())
            t.join();

        t = std::move(other.t);
        return *this;
    }

    ~joining_thread() noexcept
    {
        if (t.joinable())
            t.join();
    }

    void swap(joining_thread& other) noexcept { t.swap(other.t); }

    std::thread::id get_id() const noexcept{
        return t.get_id();
    }

    bool joinable() const noexcept { return t.joinable(); }

    void join() { t.join(); }

    void detach() { t.detach(); }

    std::thread& as_thread() noexcept { return t; }

    const std::thread& as_thread() const noexcept { return t; }
};

int main()
{
    using thread_t = joining_thread;//std::thread;
    std::vector<thread_t> threads{};

    auto do_work = [](size_t num){
        std::cout << num << ' ' << std::this_thread::get_id() << '\n';
        std::this_thread::sleep_for(100ms);
    };

    for (size_t i = 0; i < 5; i++)
    {
        threads.emplace_back(do_work, i);
    }
    
    for (auto& entry : threads)
        entry.join();

    auto nThreads = std::thread::hardware_concurrency();
    return 0;
}