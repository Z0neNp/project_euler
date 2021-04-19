#include <iostream>
#include <vector>

void print(const std::vector<int>);
int squareOfTheSum(const std::vector<int>&);
int sumOfTheSquares(const std::vector<int>&);
void getNaturalNumbers(std::vector<int>&, int);

int main()
{
    std::cout << "Welcome to the \"Sum square difference\" problem!" << std::endl;
    std::vector<int> numbers = std::vector<int>();
    getNaturalNumbers(numbers, 100);
    int square_of_the_sum = squareOfTheSum(numbers);
    int sum_of_the_squares = sumOfTheSquares(numbers);
    int difference = square_of_the_sum - sum_of_the_squares;
    std::cout << "The difference between Square of the Sums and the Sum of the Squares is " << difference << std::endl;
    exit(0);
}

void print(const std::vector<int> numbers)
{
    std::cout << "[ ";
    bool first = true;
    for (auto itr = numbers.begin(); itr < numbers.end(); itr++)
    {
        if (first)
        {
            std::cout << *itr;
            first = false;
        }
        else
            std::cout << ", " << *itr;
    }
    std::cout << " ]";
}

int squareOfTheSum(const std::vector<int>& numbers)
{
    std::cout << "Calculating the square of the sum: ";
    print(numbers);
    std::cout << std::endl;
    int sum = 0;
    for (int number : numbers)
        sum += number;
    int result = std::pow(sum, 2);
    std::cout << "The square of the sum is " << result << std::endl;;
    return result;
}

int sumOfTheSquares(const std::vector<int>& numbers)
{
    std::cout << "Calculating the sum of the squares: ";
    print(numbers);
    std::cout << std::endl;
    int result = 0;
    for (int number : numbers)
        result += std::pow(number, 2);
    std::cout << "The sum of the squares is " << result << std::endl;
    return result;
}

void getNaturalNumbers(std::vector<int>& numbers, int count)
{
    std::cout << "Preparing " << count << " natural numbers" << std::endl;
    for (int i = 1; i <= count; i++)
        numbers.push_back(i);
    std::cout << count << " natural numbers have been prepared" << std::endl;
    print(numbers);
    std::cout << std::endl;
}