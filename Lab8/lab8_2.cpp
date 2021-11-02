#include<iostream>
#include<mutex>
#include<thread>
#include<vector>

/* CODE WITH PRIMARY MUTEX */

/*
    Here we lock the resource vector (v) before writing
    The lock is put by the thread untill all the work regarding this vector is completed
    by the thread.
    Thus, we have achieved mutual exclusion.

    Now here the output will not be unpredictable like in the last case.
    Since the mutual exclusion is garunteed, the output will be regular.
    Also, note that we are not creating a new vector everytime "f" function is called.
    NOTE THAT VECTOR IS A SHARED RESOURCE. Thus, the threads will start the new value from where
    the old thread left and will not delete the old values.

    Also note that in function "f" there is another commented mutex locks.
    This pair will not garuntee mutex because it is only for writing. It is very well 
    possible that the second thread might lock the resource, push something and release which
    will interfere with the notmal pattern of the threads.
*/

void f(std::vector<int> &v)
{
    std::mutex m;
    // std::lock_guard g{m};

    m.lock();
    for(int i = 0;i<200;i++)
    {
        // m.lock()
        v.push_back(i);
        // m.unlock()
    }
    for (auto &i : v)
    {
        std::cout << i << "\n";
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