// id_07_10001st_prime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

static int CHEAP_CALCULATION_COUNT = 1000;

bool isPrime(int, const std::vector<int>&);
void printNumbers(const std::vector<int>&);
void getCheapPrimeNumbers(std::vector<int>&);

int main()
{
    std::cout << "Welcome to the \"10001st prime\" problem!" << std::endl;
    std::vector<int> primes;
    getCheapPrimeNumbers(primes);
    int primes_found = CHEAP_CALCULATION_COUNT;
    int next_number = *primes.rbegin();
    while (primes_found < 10001)
    {
        if (isPrime(next_number, primes))
        {
            primes_found++;
            if (primes_found % 1000 == 0)
                std::cout << "Past " << primes_found << " prime numbers" << std::endl;
            if (primes_found == 10001)
                break;
        }
        next_number++;
    }
    std::cout << "The 10001st prime number is " << next_number << std::endl;
    std::cout << std::endl;
    exit(0);
}

bool isPrime(int number, const std::vector<int>& primes)
{
    for (auto itr = primes.begin(); itr < primes.end(); itr++)
    {
        int prime = *itr;
        if (number % prime == 0)
            return false;
    }
    return true;
}

void printNumbers(const std::vector<int>& numbers)
{
    std::cout << "[ ";
    bool is_first = true;
    for (int number : numbers)
    {
        if (is_first)
        {
            std::cout << number;
            is_first = false;
        }
        else
            std::cout << ", " << number;
    }
    std::cout << " ]" << std::endl;
}

void getCheapPrimeNumbers(std::vector<int>& primes)
{
    std::cout << "Calculating the first " << CHEAP_CALCULATION_COUNT << " prime numbers" << std::endl;
    primes.push_back(2);
    int left_to_calculate = CHEAP_CALCULATION_COUNT - 1;
    int next_number = 3;
    while (left_to_calculate > 0)
    {
        if (isPrime(next_number, primes))
        {
            primes.push_back(next_number);
            left_to_calculate--;
        }
        next_number++;
    }
    std::cout << "The first " << CHEAP_CALCULATION_COUNT << " prime numbers are" << std::endl;
    printNumbers(primes);
}