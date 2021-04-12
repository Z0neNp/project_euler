#include <iostream>
#include <vector>
#include <set>

void generatePalindromes(const std::vector<int>&, std::set<int>& , int, int);
int vectorToNumber(const std::vector<int>&);
void pivots(int&, int&, int);
int isResultOfTwoThreeDigitsNumbers(int);

int main()
{
    std::cout << "Welcome to the \"Largest palindrome product\" problem!\n";

    std::vector<int> palindrome_digits = { 9, 9, 9, 9, 9, 9 };
    std::set<int> possible_palindromes = std::set<int>();
    int i = -1, j = -1;
    int result = -1;
    while (!palindrome_digits.empty())
    {
        pivots(i, j, palindrome_digits.size() - 1);
        generatePalindromes(palindrome_digits, possible_palindromes, i, j);
        palindrome_digits.pop_back();
    }
    for (auto ritr = possible_palindromes.rbegin(); ritr != possible_palindromes.rend() && result == -1; ritr++)
    {
        int palindrome = *ritr;
        if (isResultOfTwoThreeDigitsNumbers(palindrome))
            result = palindrome;
    }
    if (result == -1)
        std::cout << "There is no suitable palindrome in the range [0, " << vectorToNumber(palindrome_digits) << "]";
    else
        std::cout << "The palindrome is " << result;
    std::cout << std::endl;
}

void generatePalindromes(const std::vector<int>& palindrome_digits, std::set<int>& result, int index, int complimentary_index)
{
    if (index < 0 || complimentary_index > palindrome_digits.size() - 1)
        return;
    std::vector<int> copy_palindrome_digits = std::vector<int>(palindrome_digits);
    if (index == complimentary_index)
    {
        while (copy_palindrome_digits[0] > 0 && copy_palindrome_digits[index] > -1)
        {
            generatePalindromes(copy_palindrome_digits, result, index - 1, complimentary_index + 1);
            int palindrome = vectorToNumber(copy_palindrome_digits);
            copy_palindrome_digits[index]--;
            result.insert(palindrome);
        }
    }
    else {
        while (copy_palindrome_digits[0] > 0 && copy_palindrome_digits[index] > -1 && copy_palindrome_digits[complimentary_index] > -1)
        {
            generatePalindromes(copy_palindrome_digits, result, index - 1, complimentary_index + 1);
            int palindrome = vectorToNumber(copy_palindrome_digits);
            result.insert(palindrome);
            copy_palindrome_digits[index]--;
            copy_palindrome_digits[complimentary_index]--;
        }
    }
}

int vectorToNumber(const std::vector<int>& number_digits)
{
    int result = 0;
    int multiplier = std::pow(10, (number_digits.size() - 1));
    for (int digit : number_digits)
    {
        result += digit * multiplier;
        multiplier = multiplier / 10;
    }
    return result;
}

void pivots(int& left, int& right, int count)
{
    if (count <= 0)
        return;
    if (count % 2 == 0)
    {
        left = count / 2;
        right = left;
    }
    else
    {
        left = (count - 1) / 2;
        right = (count + 1) / 2;
    }
}

int isResultOfTwoThreeDigitsNumbers(int dividend)
{
    for (int divisor = 100; divisor < 1000; divisor++)
    {
        if (dividend % divisor == 0)
        {
            int quotient = dividend / divisor;
            if (quotient > 99 && quotient < 1000)
                return true;
        }
    }
    return false;
}