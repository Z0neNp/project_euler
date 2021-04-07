// id_03_largest_prime_factor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <cmath>

bool areCoprime(long, long);
bool fermatPrimalityTest(std::list<int>&, long long);
long long getLargestMultiplier(long long);
void populateSeedNumbers(std::list<int>&);

int main()
{
    std::cout << "Welcome to the \"Largest prime factor\" problem!" << std::endl;
    long long target = 600851475143;
    std::list<int> seed_numbers;
    int result = -1;
    populateSeedNumbers(seed_numbers);
    long largest_multiplier = getLargestMultiplier(target);
    while (largest_multiplier > 1)
    {
        if (fermatPrimalityTest(seed_numbers, largest_multiplier))
        {
            if (target % largest_multiplier == 0)
            {
                result = largest_multiplier;
                break;
            }
        }
        largest_multiplier--;
    }
    if (result > 0)
        std::cout << "The largest prime factor is " << result << std::endl;
    else
        std::cout << "There is no largest prime factor" << std::endl;
}

bool fermatPrimalityTest(std::list<int>& seed_numbers, long long test_number)
{
    bool is_prime = true;
    for (auto itr = seed_numbers.begin(); itr != seed_numbers.end() && is_prime; ++itr)
    {
        int seed_number = *itr;
        if (test_number % seed_number == 0)
            is_prime = false;
    }
    return is_prime;
}

long long getLargestMultiplier(long long target)
{
    long double sqrt_val = sqrt(target);
    long long result = floor(sqrt_val);
    return result;
}

void populateSeedNumbers(std::list<int>& seed_numbers)
{
    seed_numbers.push_back(2);
    seed_numbers.push_back(3);
    int counter = 4;
    while (counter < 1000)
    {
        bool is_prime = true;
        for (auto itr = seed_numbers.begin(); itr != seed_numbers.end() && is_prime; ++itr)
        {
            int prime = *itr;
            if (counter % prime == 0)
                is_prime = false;
        }
        if (is_prime)
            seed_numbers.push_back(counter);
        counter++;
    }
}
