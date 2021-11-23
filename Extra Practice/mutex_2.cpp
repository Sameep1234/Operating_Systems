#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex m;

void f(std::vector<int> &v)
{
    m.lock();
    for (int i = 0; i < 200; i++)
    {
        v.push_back(i);
    }

    for (auto &i : v)
    {
        std::cout << i << "\n";
    }
    m.unlock();
}

int main()
{
    std::vector<int> v;

    std::thread t{f, std::ref(v)};
    std::thread u{f, std::ref(v)};

    if (t.joinable())
        t.join(); // Equivalent to wait(NULL) in process.

    if (u.joinable())
        u.join();

    return 0;
}