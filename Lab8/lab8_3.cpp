#include<iostream>
#include<mutex>
#include<thread>
#include<vector>

/* CODE WITH AUTO MUTEX */

/*
    Below code used lock guard which takes in mutex as the argument and performs auto locking mechanism.
    The resources are locked as soon as a thread starts to use it and releases it once its usage completes.

    However, all the codes seen till now does pose a problem of not solving mutual exclusion and below is the reason.
    Whenever threads are created, there is a seperate copy of thread used variables and resources along with 
    memory pointers to the shared resource. Here, as evident from the code, the threads created will have separate copy 
    of mutex variable because it is declared and initialized in function "f".
    Thus, if there is a thread created under that thread, only then it will be possible to achieve mutual exclusion
    between those threads.

    We, thus, need to take care of the "scope" of mutex varible. There are three methods by which the scope of mutex
    variable can be defined such that mutex is acieved.
    First, declare mutex variable as a global variable and thus it becomes a shared resources and solves the difficulty.
    Second, declare mutex variable in the main thread so that whenever its threads are created, they will have access to 
    the same mutex variable elimination the said problem.
    Lastly, create a class and declare the variable as well the function in it so as to achieve mutex. 
*/

void f(std::vector<int> &v)
{
    std::mutex m;
    std::lock_guard g{m};

    // m.lock();
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
    // m.unlock();
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
    scope of mutex (main thread and 2 parallel thread)
    To avoid scope of mutex, we use it in class, global variables (avoid generally), main thread (avoid generally).
    passing mutex in thread when declared in main
*/