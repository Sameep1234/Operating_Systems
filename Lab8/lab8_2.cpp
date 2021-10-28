#include<iostream>
#include<mutex>
#include<thread>
#include<vector>

void f(std::vector<int> &v)
{
    std::mutex m;
    // std::lock_guard g{m};

    m.lock();
    for(int i = 0;i<200;i++)
    {
        // m.lock()
        v.push_back(i);
        std::cout<<v[i]<<"\n";
        // m.unlock()
    }
    m.unlock();
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
*/