#include <iostream>
#include <thread>
#include <vector>

/* CODE WITHOUT MUTEX */

/*
    Here, we created two threads viz t and u.
    Both these threads will run parallely and since we have not used any code for mutex,
    the output is bound to be unpredictable.
    It might run once or twice but there might be serious overlap between threads leading 
    to corrupted date being entered.
*/

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