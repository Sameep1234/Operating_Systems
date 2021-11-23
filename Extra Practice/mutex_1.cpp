#include <iostream>
#include <vector>
#include <thread>

/*
    STL - Standard template library
    iterator
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
    std::vector<int> v;

    std::thread t{f, std::ref(v)};

    if (t.joinable())
        t.join(); // Equivalent to wait(NULL) in process.


    std::cout<<"\n\n\n\n\n";

    for (auto &i : v)
    {
        std::cout << i << "\n";
    }
    return 0;
}