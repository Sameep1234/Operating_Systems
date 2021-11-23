#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

void f(std::vector<int> &v, std::mutex &sameep)
{
    std::lock_guard kavya{sameep};
    // sameep.lock();
    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
    }

    for (auto &i : v)
    {
        std::cout << i << "\n";
    }
    // sameep.unlock();
}

int main()
{
    std::vector<int> v;
    std::mutex m;

    // Array of thread
    std::vector<std::thread> t;

    for (int i = 0; i < 5; i++)
    {
        t.push_back(std::thread{f, std::ref(v), std::ref(m)});
    }

    for (auto &i : t)
    {
        if(i.joinable())
            i.join();
    }

    return 0;
}