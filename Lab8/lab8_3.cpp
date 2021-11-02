#include<iostream>
#include<mutex>
#include<thread>
#include<vector>

void f(std::vector<int> &v)
{
    std::mutex m;
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

    std::thread t{f, std::ref(v)};
    std::thread u{f, std::ref(v)};

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