#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

void f(std::vector<int> &v, std::mutex &sameep)
{
    std::lock_guard kavya{sameep};
    // sameep.lock();
    for (int i = 0; i < 200; i++)
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

    std::thread t{f, std::ref(v), std::ref(m)};
    std::thread u{f, std::ref(v), std::ref(m)};

    if (t.joinable())
        t.join(); // Equivalent to wait(NULL) in process.

    if (u.joinable())
        u.join();

    return 0;
}