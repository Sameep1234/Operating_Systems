#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/* CREATING MULTIPLE THREADS */

/*
    It is very well possible that we are required to create multiple threads for each component of job we need to perform.
    Thus, it is almost impossible to write thread creation statement about 100 times with different variable names.
    Thus, we use for loop and create array of thread.

    Note that printing statements are written after join statement because we need to wait for all the threads to complete
    their execution and then main thread will be able to print the values contained in vector v without interference from
    ny other threads.
*/

void f(std::vector<int> &v, std::mutex &m)
{
    std::lock_guard g{m};

    // m.lock();
    for (int i = 0; i < 5; i++)
    {
        // m.lock()
        v.push_back(i);
        // m.unlock()
    }
    for (auto &i : v)
    {
        std::cout << i << "\n";
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