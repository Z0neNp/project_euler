#include <omp.h>
#include <iostream>
#include <vector>

bool isEvenlyDivisible(int, const std::vector<int>&);
bool isPrime(int);

static int THREAD_RANGE = 10000000;

int main()
{
    std::cout << "Welcome to the \"Smallest multiple\" problem!" << std::endl;
    std::vector<int> divisers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    int possible_multiple = 1 * 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 20;
    std::cout << "The lowest possible multiple is " << possible_multiple << std::endl;
    int first_res = 0, second_res = 0 , third_res = 0, fourth_res = 0;
    #pragma omp parallel num_threads(4) shared(first_res, second_res, third_res, fourth_res)
    {
        int tid = omp_get_thread_num();
        int start_point = possible_multiple + THREAD_RANGE * tid;
        for (int counter = start_point; counter < start_point + THREAD_RANGE; counter++)
        {
           if (isEvenlyDivisible(counter, divisers))
            {
                switch (tid)
                {
                case 0:
                    first_res = counter;
                    break;
                case 1:
                    second_res = counter;
                    break;
                case 2:
                    third_res = counter;
                    break;
                case 3:
                    fourth_res = counter;
                    break;
                }
                break;
            }
        }
    }
    if (first_res != 0)
        std::cout << "The lowest multiple is " << first_res << std::endl;
    else if (second_res != 0)
        std::cout << "The lowest multiple is " << second_res << std::endl;
    else if (third_res != 0)
        std::cout << "The lowest multiple is " << third_res << std::endl;
    else if (fourth_res != 0)
        std::cout << "The lowest multiple is " << fourth_res << std::endl;
    std::cin;
    exit(0);
}

bool isEvenlyDivisible(int number, const std::vector<int>& divisers)
{
    for (auto it = divisers.rbegin(); it < divisers.rend(); it++)
    {
        int diviser = *it;
        if (number % diviser != 0)
            return false;
    }
    return true;
}

bool isPrime(int number)
{
    if (number == 1 || number == 2)
        return true;
    for (int counter = 2; counter < number; counter++)
    {
        if (number % counter == 0)
            return false;
    }
    return true;
}