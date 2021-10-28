#include <iostream>
#include <thread>

void f(int &a, int &b)
{
    std::cout << "Hello World!\n";
}

int main()
{
    /*
        t = variable name for the thread
        f = function pointer which points to f
    */
    std::thread t{f, 1, 2}; // Create a thread in cpp
                      /*
                          This will result in an error because we are not defining what to do with the thread.
                          Thus, whenever we create a thread, we need to join the thread which is done below.
                          Functions are callable which means that anything that can be "called" using a paranthesis.
                          Thus, we always pass callable object in thread variable.
                      */
    if (t.joinable())
    {
        t.join(); // This is analogous to wait() in c. It will wait for all other threads to complete and then will execute.
    }
    /*
        This means that main thread will wait untill all other threads are completing.
        This code will now run and print hello world. Note that this hello world is getting printed in the new thread that we created.
    */
    return 0;
}