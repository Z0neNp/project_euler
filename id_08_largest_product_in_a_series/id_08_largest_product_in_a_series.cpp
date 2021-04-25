#include <iostream>
#include <vector>
#include <string>
#include <fstream>

long long getProduct(const std::vector<int>&, const std::vector<int>&);
void incrementIndexes(std::vector<int>&);
bool lastIndexNotPassed(const std::vector<int>&, const std::vector<int>&);
std::string multiplicationToString(long long, const std::vector<int>&, const std::vector<int>&);
std::string numbersToString(const std::vector<int>&);
void textFileToIntCollection(const std::string&, std::vector<int>&);


int main()
{
    std::cout << "Welcome to the \"Largest product in a series\" problem!" << std::endl;
    
    std::vector<int> numbers;
    std::string file_with_numbers = "sequence.txt";
    std::cout << "Mapping text file with digits to the collection of integers" << std::endl;
    textFileToIntCollection(file_with_numbers, numbers);
    std::cout << "The collection of integers is" << std::endl << numbersToString(numbers) << std::endl;
    std::vector<int> adjacent_digit_indexes({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 });
    std::vector<int> adjacent_digit_indexes_for_greatest_product;
    long long greatest_product = 1;
    while (lastIndexNotPassed(adjacent_digit_indexes, numbers))
    {
        long long product = getProduct(adjacent_digit_indexes, numbers);
        if (product > greatest_product)
        {
            greatest_product = product;
            std::cout << "The new greatest product is "
                << multiplicationToString(greatest_product, adjacent_digit_indexes, numbers) << std::endl;
            adjacent_digit_indexes_for_greatest_product = std::vector<int>(adjacent_digit_indexes);
        }
        incrementIndexes(adjacent_digit_indexes);
    }
    std::cout << std::endl <<  "The greatest product is " << multiplicationToString(
        greatest_product, adjacent_digit_indexes_for_greatest_product, numbers
    ) << std::endl;
    
    std::cout << std::endl;
    exit(0);
}

long long getProduct(const std::vector<int>& indexes, const std::vector<int>& numbers)
{
    long long result = 1;
    for (int index : indexes)
        result = result * numbers[index];
    return result;
}

void incrementIndexes(std::vector<int>& indexes)
{
    for (int i = 0; i < indexes.size(); i++)
        indexes[i] = indexes[i] + 1;
}

bool lastIndexNotPassed(const std::vector<int>& indexes, const std::vector<int>& numbers)
{
    return indexes[indexes.size() - 1] < numbers.size();
}

std::string multiplicationToString(long long product, const std::vector<int>& indexes, const std::vector<int>& numbers)
{
    std::string result;
    bool is_first = true;
    for (int index : indexes)
    {
        if (is_first)
        {
            result.append(std::to_string(numbers[index]));
            is_first = false;
        }
        else
        {
            result.append(" * ");
            result.append(std::to_string(numbers[index]));
        }
    }
    result.append(" = ");
    result.append(std::to_string(product));
    return result;
}

std::string numbersToString(const std::vector<int>& numbers)
{
    std::string result;
    result.append("[ ");
    bool is_first = true;
    for (int number : numbers)
    {
        if (is_first)
        {
            
            result.append(std::to_string(number));
            is_first = false;
        }
        else
        {
            result.append(", ");
            result.append(std::to_string(number));

        }
    }
    result.append(" ]");
    return result;
}

void textFileToIntCollection(const std::string& filename, std::vector<int>& numbers)
{
    
    std::ifstream read_file(filename);
    std::string next_line;
    while (std::getline(read_file, next_line))
    {
        for (char c : next_line)
        {
            if ('0' <= c && c <= '9')
                numbers.push_back(c - '0');
        }
    }
}