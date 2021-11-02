#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <algorithm>

/* CODE TO CREATE A "SET" DATA STRUCTURE */

/*
    Here, to acheive mutex, we are using class to provide a parent authority.
    Created a private vector data and since it is a private variable, we need to create a getter method.

*/

class Set
{
private:
    std::vector<int> data;
    std::mutex m;

public:
    Set() : data{{}} {} // Initialize data to null as soon as Set() is called.
    Set &operator=(const Set &) = delete; // Operator overloading (DOUBT)

    auto &get_data() // Getter method for accessing data
    {
        return data;
    }

    void insert(int val) // Insert method
    {
        std::lock_guard g{m}; // Achieve mutex
        if (std::find(data.begin(), data.end(), val) == data.end()) // Order must be maintained because it is a set
        { // Hence used "find" function from the std library
            data.push_back(val); // Pushed the availble value 
        }
    }

    void erase(int val) // Delete function
    {
        std::lock_guard g{m}; // Achieve auto mutex
        std::remove(data.begin(), data.end(), val); // Simply delete the data
    }
};

void f(Set &s, int val) // Primary function on which threads are created
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
    for (int i = 0; i < 5; i++) // Create threads
    {
        t_vec.push_back(std::thread{f, std::ref(s), i});
    }

    for (auto &t : t_vec) // Join them
    {
        t.join();
    }

    for (const auto &i : s.get_data()) // Print the final data in class created above.
    {
        std::cout << i << '\n';
    }
    return 0;
}