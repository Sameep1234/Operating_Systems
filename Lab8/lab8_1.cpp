#include <iostream>
#include <thread>
#include <vector>

/* CODE WITHOUT MUTEX */

void f(std::vector<int> &v)
{
    for (int i = 0; i < 200; i++)
    {
        v.push_back(i);
    }

    for (auto &i : v)
    {
        std::cout << i << "\n";
    }
}

int main()
{
    std::vector<int> v{};

    std::thread t{f, std::ref(v)};
    std::thread u{f, std::ref(v)};

    if (t.joinable())
    {
        t.join();
    }
    if (u.joinable())
    {
        u.join();
    }
    return 0;
}