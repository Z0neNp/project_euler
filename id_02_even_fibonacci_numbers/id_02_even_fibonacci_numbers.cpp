// id_02_even_fibonacci_numbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Welcome to the \"Even Fibonacci numbers\" problem!\n";
    int previous_num = 1;
    int num = 2;
    int limit = 4000000;
    int result = 0;
    while (num < limit)
    {
        if (num % 2 == 0)
            result += num;
        int temp = num;
        num += previous_num;
        previous_num = temp;
    }
    std::cout << "The result is " << result << std::endl;
}
