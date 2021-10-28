#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void f(std::vector<int> &v, std::mutex &m)
{
    std::lock_guard g{m};

    // m.lock();
    for (int i = 0; i < 5; i++)
    {
        // m.lock()
        v.push_back(i);
        std::cout << v[i] << "\n";
        // m.unlock()
    }
    // m.unlock();
}

int main()
{
    std::vector<int> v{};

    std::mutex m;

    /* Multithreaded approach with arrays */
    std::vector<std::thread> t_vec{};
    for (int i{}; i < 5; i++)
    {
        t_vec.push_back(std::thread{f, std::ref(v), std::ref(m)});
    }

    for (auto &i : t_vec)
    {
        i.join();
    }

    for (const auto &i : v)
    {
        std::cout << i << "\n";
    }

    return 0;
}

/*
    mutex
    lock_guard
    scope of mutex (main thread and 2 parallel thread)
    To avoid scope of mutex, we use it in class, global variables (avoid generally), main thread (avoid generally).
    passing mutex in thread when declared in main
    Multiple threads array
*/