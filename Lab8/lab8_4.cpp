#include<iostream>
#include<mutex>
#include<thread>
#include<vector>

/* CODE WITH MUTEX AS ARGUMENT */


/*
    As discussed earlier, the mutext variable must have some global/parent scope so that it becomes a shared resource 
    and mutex is achieved.
    Here, we are following the second approach of declaring the mutex in main thread and passing it as an argument in 
    function "f" and initializing lock guard in it.
    Thus, now there is a parent authority (main thread) which will take care of mutex.
*/

void f(std::vector<int> &v, std::mutex &m)
{
    std::lock_guard g{m};

    // m.lock();
    for(int i = 0;i<200;i++)
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

    std::thread t{f, std::ref(v), std::ref(m)};
    std::thread u{f, std::ref(v), std::ref(m)};

    if(t.joinable())
    {
        t.join();
    }
    if(u.joinable())
    {
        u.join();
    }
    return 0;
}

/* 
    mutex
    lock_guard
    scope of mutex (main thread and 2 parallel thread)
    To avoid scope of mutex, we use it in class, global variables (avoid generally), main thread (avoid generally).
    passing mutex in thread when declared in main
*/