#include<iostream>
#include<thread>
#include<vector>

void f(std::vector<int> &v)
{
    for(int i = 0;i<200;i++)
    {
        v.push_back(i);
        std::cout<<v[i]<<"\n";
    }
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