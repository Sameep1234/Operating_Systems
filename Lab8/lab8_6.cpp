#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <algorithm>

class Set
{
private:
    std::vector<int> data;
    std::mutex m;

public:
    Set() : data{{}} {}
    Set &operator=(const Set &) = delete;

    auto &get_data()
    {
        return data;
    }

    void insert(int val)
    {
        std::lock_guard g{m};
        if (std::find(data.begin(), data.end(), val) == data.end())
        {
            data.push_back(val);
        }
    }

    void erase(int val)
    {
        std::lock_guard g{m};
        std::remove(data.begin(), data.end(), val);
    }
};

void f(Set &s, int val)
{
    for (int i = 0; i < val; i++)
    {
        s.insert(val);
    }
}

int main()
{
    Set s;
    // s(); // Gives error because not callable

    std::vector<std::thread> t_vec;
    for (int i = 0; i < 5; i++)
    {
        t_vec.push_back(std::thread{f, std::ref(s), i});
    }

    for (auto &t : t_vec)
    {
        t.join();
    }

    for (const auto &i : s.get_data())
    {
        std::cout << i << '\n';
    }
    return 0;
}