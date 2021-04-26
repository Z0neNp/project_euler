#include <vector>
#include <iostream>
#include <numeric>

static int LIMIT = 2000000;
static int FAST_PRIMES = 1000;

bool isPrime(const std::vector<int>&, int);
void populateFastPrimes(std::vector<int>&, int);
long long sumOfPrimes(const std::vector<int>&, int);

int main()
{
    std::cout << "Welcome to the \"Summation of primes\" problem!\n";
    std::vector<int> fast_primes;
    std::cout << "Calculating the fast primes..." << std::endl;
    populateFastPrimes(fast_primes, FAST_PRIMES);
    std::cout << "\t" << fast_primes.size() << " fast primes have been calculated" << std::endl;
    std::cout << "Calculating the sum of the prime numbers less than " << LIMIT << "..." << std::endl;
    long long sum_of_the_fast_primes = std::accumulate(fast_primes.begin(), fast_primes.end(), 0);
    std::cout << "\tThe sum of the fast primes is " << sum_of_the_fast_primes << std::endl;
    long long sum = sum_of_the_fast_primes + sumOfPrimes(fast_primes, LIMIT);
    std::cout << "The sum of the prime numbers less than " << LIMIT << " is " << sum << std::endl;
    std::cout << std::endl;
    exit(0);
}

bool isPrime(const std::vector<int>& primes, int number)
{
    for (int prime : primes)
    {
        if (number % prime == 0)
            return false;
    }
    return true;
}

void populateFastPrimes(std::vector<int>& result, int count)
{
    result.push_back(2);
    count--;
    int potential_prime = 3;
    while (count > 0)
    {
        if (isPrime(result, potential_prime))
        {
            result.push_back(potential_prime);
            count--;
        }
        potential_prime++;
    }
}

long long sumOfPrimes(const std::vector<int>&samples, int limit)
{
    int potential_prime = *samples.rbegin() + 1;
    long long result = 0;
    while (potential_prime < limit)
    {
        if (isPrime(samples, potential_prime))
            result += potential_prime;
        potential_prime++;
        if (potential_prime % 100000 == 0)
            std::cout << "\t\tDEBUG -- past " << potential_prime << std::endl;
    }
    return result;
}