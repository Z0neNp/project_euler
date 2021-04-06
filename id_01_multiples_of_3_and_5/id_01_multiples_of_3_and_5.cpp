// id_01_multiples_of_3_and_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Welcome to the \"Multiples of 3 and 5\" problem!\n";
    int limit = 1000;
    int counter = 0;
    int result = 0;
    while (counter < limit)
    {
        if (counter % 3 == 0 || counter % 5 == 0)
            result += counter;
        counter++;
    }
    std::cout << "The result is " << result;
}
