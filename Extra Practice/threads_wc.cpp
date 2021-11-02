#include <iostream>
#include <algorithm>
#include <mutex>
#include <vector>
#include <thread>
#include <string>

void handleError(std::string str)
{
    std::cout << str << "\n";
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::string temp = "Incorrect number of arguments";
        handleError(temp);
    }

    int process_number = atoi(argv[2]);
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL)
        handleError("Main thread file open error!");

    if (fseek(fp, 0, SEEK_END) == -1)
        handleError("Main thread seek error!");

    long file_length = ftell(fp);

    long file_length_per_process = file_length / process_number;

    int starting_position[process_number];

    for (int i = 0; i <= process_number - 1; i++)
    {
        starting_position[i] = i * file_length_per_process;
    }

    fclose(fp);

    return 0;
}