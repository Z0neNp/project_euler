#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ios>

bool areIndexesInRange(const std::vector<int>&, int, int);
int getProduct(const std::vector<int>&, const std::vector<int>&);
std::string gridToString(const std::vector<int>&, int, int);
std::string highlightedNumbersInGrid(const std::vector<int>&, const std::vector<int>&, int, int);
void incrementIndexes(std::vector<int>&);
void initRowIndexesDiagonallyDown(std::vector<int>&, int, int);
void initRowIndexesDiagonallyUp(std::vector<int>&, int, int);
void initRowIndexesHorizontally(std::vector<int>&, int, int);
void initRowIndexesVertically(std::vector<int>&, int, int);
bool isEndOfColumnReached(int, int, int);
bool isIndexLegal(int, int, int);
void populateGrid(std::vector<int>&, const std::string&);
int largestProductOfAdjacentNumbersDiagonallyDown(std::vector<int>&, const std::vector<int>&, int, int);
int largestProductOfAdjacentNumbersDiagonallyUp(std::vector<int>&, const std::vector<int>&, int, int);
int largestProductOfAdjacentNumbersHorizontally(std::vector<int>&, const std::vector<int>&, int, int);
int largestProductOfAdjacentNumbersVertically(std::vector<int>&, const std::vector<int>&, int, int);
std::string vectorToString(const std::vector<int>& numbers);


static int ROWS = 20;
static int COLS = 20;

int main()
{
    std::cout << "Welcome to the \"Largest product in a grid\" problem!\n";
    std::vector<int> grid;
    std::string filename("grid.txt");
    std::cout << "Reading " << ROWS << " x " << COLS << " grid from " << filename << " file..." << std::endl;
    populateGrid(grid, filename);
    std::cout << "\tThe grid was read" << std::endl << gridToString(grid, ROWS, COLS) << std::endl;
    std::cout << "Calculating the largest product of diagonally down adjacent numbers..." << std::endl;
    std::vector<int> diagonal_indexes_down({ -1, -1, -1, -1 });
    int largest_product_diagonally_down = largestProductOfAdjacentNumbersDiagonallyDown(diagonal_indexes_down, grid, ROWS, COLS);
    std::cout << "\tThe largest product diagonally down is " << largest_product_diagonally_down << std::endl
        << highlightedNumbersInGrid(diagonal_indexes_down, grid, ROWS, COLS) << std::endl;
    int result_product = largest_product_diagonally_down;
    std::vector<int>* p_result_indexes = &diagonal_indexes_down;
    std::cout << "Calculating the largest product of diagonally up adjacent numbers..." << std::endl;
    std::vector<int> diagonal_indexes_up({ -1, -1, -1, -1 });
    int largest_product_diagonally_up = largestProductOfAdjacentNumbersDiagonallyUp(diagonal_indexes_up, grid, ROWS, COLS);
    std::cout << "\tThe largest product diagonally up is " << largest_product_diagonally_up << std::endl
        << highlightedNumbersInGrid(diagonal_indexes_up, grid, ROWS, COLS) << std::endl;
    if (largest_product_diagonally_up > result_product)
    {
        result_product = largest_product_diagonally_up;
        p_result_indexes = &diagonal_indexes_up;
    }
    std::cout << "Calculating the largest product of horizontally adjacent numbers..." << std::endl;
    std::vector<int> horizontal_indexes({ -1, -1, -1, -1 });
    int largest_product_horizontally = largestProductOfAdjacentNumbersHorizontally(horizontal_indexes, grid, ROWS, COLS);
    std::cout << "\tThe largest product horizontally is " << largest_product_horizontally << std::endl
        << highlightedNumbersInGrid(horizontal_indexes, grid, ROWS, COLS) << std::endl;
    if (largest_product_horizontally > result_product)
    {
        result_product = largest_product_horizontally;
        p_result_indexes = &horizontal_indexes;
    }
    std::cout << "Calculating the largest product of vertically adjacent numbers..." << std::endl;
    std::vector<int> vertical_indexes({ -1, -1, -1, -1 });
    int largest_product_vertically = largestProductOfAdjacentNumbersVertically(vertical_indexes, grid, ROWS, COLS);
    std::cout << "\tThe largest product vertically is " << largest_product_vertically << std::endl
        << highlightedNumbersInGrid(vertical_indexes, grid, ROWS, COLS) << std::endl;
    if (largest_product_vertically > result_product)
    {
        result_product = largest_product_vertically;
        p_result_indexes = &vertical_indexes;
    }
    std::cout << "The largest product is " << result_product << std::endl;
    std::cout << "It's factors are " << std::endl << highlightedNumbersInGrid(*p_result_indexes, grid, ROWS, COLS);
    std::cout << std::endl;
    exit(0);
}

bool areIndexesInRange(const std::vector<int>& indexes, int rows, int cols)
{
    for (int index : indexes)
    {
        if (!isIndexLegal(index, rows, cols))
            return false;
    }
    for (std::size_t i = 0, j = 1; i < indexes.size() - 1 && j < indexes.size(); i++, j++)
    {
        if (std::abs(indexes[i] - indexes[j]) > 1)
        {
            int difference = std::abs(indexes[i] - indexes[j]);
            if (difference != cols + 1 && difference != cols - 1 && difference != cols)
                return false;
        }
    }
    return true;
}

int getProduct(const std::vector<int>& indexes, const std::vector<int>& numbers)
{
    int result = 1;
    for (int index : indexes)
        result *= numbers[index];
    return result;
}

std::string gridToString(const std::vector<int>& grid, int rows, int cols)
{
    std::string result = "";
    for (int i = 0; i < rows; i++)
    {
        std::vector<int> row(grid.begin() + i * cols, grid.begin() + i * cols + cols);
        result.append("\t");
        result.append(vectorToString(row));
        if (i < rows - 1)
            result.append("\n");
    }
    return result;
}

std::string highlightedNumbersInGrid(const std::vector<int>& indexes, const std::vector<int>& grid, int rows, int cols)
{
    std::string result = "\t";
    for (int i = 0; i < rows; i++)
    {
        int isFirst = true;
        for (int j = 0; j < cols; j++)
        {
            int index = i * cols + j;
            if (std::count(indexes.begin(), indexes.end(), index) > 0)
            {
                int number = grid[index];
                if (isFirst)
                {
                    result.append(std::to_string(number));
                    isFirst = false;
                }
                else
                {
                    result.append(", ");
                    result.append(std::to_string(number));
                }
                if (number < 10)
                    result.append(" ");
            }
            else
            {
                if (isFirst)
                {
                    result.append("__");
                    isFirst = false;
                }
                else
                    result.append(", __");
            }
        }
        result.append("\n\t");
    }
    return result;
}

void incrementIndexes(std::vector<int>& indexes)
{
    for (std::size_t i = 0; i < indexes.size(); i++)
        indexes[i] = indexes[i] + 1;
}

void initRowIndexesDiagonallyDown(std::vector<int>& indexes, int row_id, int cols)
{
    int offset = 0;
    for (std::size_t i = 0; i < indexes.size(); i++)
    {
        indexes[i] = (row_id + offset) * cols + offset;
        offset++;
    }
}

void initRowIndexesDiagonallyUp(std::vector<int>& indexes, int row_id, int cols)
{
    int offset = 0;
    for (std::size_t i = 0; i < indexes.size(); i++)
    {
        indexes[i] = (row_id - offset) * cols + offset;
        offset++;
    }
}

void initRowIndexesHorizontally(std::vector<int>& indexes, int row_id, int cols)
{
    int offset = 0;
    for (std::size_t i = 0; i < indexes.size(); i++)
    {
        indexes[i] = row_id * cols + offset;
        offset++;
    }
}

void initRowIndexesVertically(std::vector<int>& indexes, int row_id, int cols)
{
    int offset = 0;
    for (std::size_t i = 0; i < indexes.size(); i++)
    {
        indexes[i] = row_id + cols * offset;
        offset++;
    }
}

bool isIndexLegal(int index, int rows, int cols)
{
    return 0 <= index && index < (rows * cols);
}

bool isEndOfColumnReached(int index, int rows, int cols)
{
    for (int i = cols - 1; i < rows * cols; i += cols)
    {
        if (index == i)
            return true;
    }
    return false;
}

int largestProductOfAdjacentNumbersDiagonallyDown(std::vector<int>& indexes, const std::vector<int>& grid, int rows, int cols)
{
    std::vector<int> result_indexes;
    int result_product = -1;
    int rows_covered = 0;
    initRowIndexesDiagonallyDown(indexes, rows_covered, cols);
    while (areIndexesInRange(indexes, rows, cols))
    {
        int product = getProduct(indexes, grid);
        //std::cout << "\t\tAnalyzing numbers at " << vectorToString(indexes) << ". Product is " << product << std::endl;
        //std::cout << highlightedNumbersInGrid(indexes, grid, rows, cols);
        if (product > result_product)
        {
            result_product = product;
            result_indexes = std::vector<int>(indexes);
        }
        if (isEndOfColumnReached(indexes[indexes.size() - 1], rows, cols))
        {
            rows_covered++;
            initRowIndexesDiagonallyDown(indexes, rows_covered, cols);
        }
        else
        {
            incrementIndexes(indexes);
            if (!areIndexesInRange(indexes, rows, cols))
            {
                rows_covered++;
                initRowIndexesDiagonallyDown(indexes, rows_covered, cols);
            }
        }
    }
    indexes = std::vector<int>(result_indexes);
    return result_product;
}

int largestProductOfAdjacentNumbersDiagonallyUp(std::vector<int>& indexes, const std::vector<int>& grid, int rows, int cols)
{
    std::vector<int> result_indexes;
    int result_product = -1;
    int rows_to_cover = 19;
    initRowIndexesDiagonallyUp(indexes, rows_to_cover, cols);
    while (areIndexesInRange(indexes, rows, cols))
    {
        int product = getProduct(indexes, grid);
        //std::cout << "\t\tAnalyzing numbers at " << vectorToString(indexes) << ". Product is " << product << std::endl;
        //std::cout << highlightedNumbersInGrid(indexes, grid, rows, cols);
        if (product > result_product)
        {
            result_product = product;
            result_indexes = std::vector<int>(indexes);
        }
        if (isEndOfColumnReached(indexes[indexes.size() - 1], rows, cols))
        {
            rows_to_cover--;
            initRowIndexesDiagonallyUp(indexes, rows_to_cover, cols);
        }
        else
        {
            incrementIndexes(indexes);
            if (!areIndexesInRange(indexes, rows, cols))
            {
                rows_to_cover--;
                initRowIndexesDiagonallyUp(indexes, rows_to_cover, cols);
            }
        }
    }
    indexes = std::vector<int>(result_indexes);
    return result_product;
}

int largestProductOfAdjacentNumbersHorizontally(std::vector<int>& indexes, const std::vector<int>& grid, int rows, int cols)
{
    std::vector<int> result_indexes;
    int result_product = -1;
    int covered_rows = 0;
    initRowIndexesHorizontally(indexes, covered_rows, cols);
    while (areIndexesInRange(indexes, rows, cols))
    {
        int product = getProduct(indexes, grid);
        //std::cout << "\t\tAnalyzing numbers at " << vectorToString(indexes) << ". Product is " << product << std::endl;
        //std::cout << highlightedNumbersInGrid(indexes, grid, rows, cols);
        if (product > result_product)
        {
            result_product = product;
            result_indexes = std::vector<int>(indexes);
        }
        if (isEndOfColumnReached(indexes[indexes.size() - 1], rows, cols))
        {
            covered_rows++;
            initRowIndexesHorizontally(indexes, covered_rows, cols);
        }
        else
        {
            incrementIndexes(indexes);
            if (!areIndexesInRange(indexes, rows, cols))
            {
                covered_rows++;
                initRowIndexesHorizontally(indexes, covered_rows, cols);
            }
        }
    }
    indexes = std::vector<int>(result_indexes);
    return result_product;
}

int largestProductOfAdjacentNumbersVertically(std::vector<int>& indexes, const std::vector<int>& grid, int rows, int cols)
{
    std::vector<int> result_indexes;
    int result_product = -1;
    int covered_rows = 0;
    initRowIndexesVertically(indexes, covered_rows, cols);
    while (areIndexesInRange(indexes, rows, cols))
    {
        int product = getProduct(indexes, grid);
        //std::cout << "\t\tAnalyzing numbers at " << vectorToString(indexes) << ". Product is " << product << std::endl;
        //std::cout << highlightedNumbersInGrid(indexes, grid, rows, cols);
        if (product > result_product)
        {
            result_product = product;
            result_indexes = std::vector<int>(indexes);
        }
        if (isEndOfColumnReached(indexes[indexes.size() - 1], rows, cols))
        {
            covered_rows += cols;
            initRowIndexesVertically(indexes, covered_rows, cols);
        }
        else
        {
            incrementIndexes(indexes);
            if (!areIndexesInRange(indexes, rows, cols))
            {
                covered_rows += cols;
                initRowIndexesVertically(indexes, covered_rows, cols);
            }
        }
    }
    indexes = std::vector<int>(result_indexes);
    return result_product;
}

void populateGrid(std::vector<int>& result, const std::string& filename)
{
    std::ifstream read_file(filename);
    std::string line;
    while (std::getline(read_file, line))
    {
        bool parsing_number = true;
        int number = 0;
        for (char c : line)
        {
            if ('0' <= c && c <= '9')
            {
                if (!parsing_number)
                {
                    number = 0;
                    parsing_number = true;
                }
                number *= 10;
                number += c - '0';
            }
            else
            {
                parsing_number = false;
                result.push_back(number);
            }
        }
        if (parsing_number)
            result.push_back(number);
    }
}

std::string vectorToString(const std::vector<int>& numbers)
{
    std::string result = "[";
    bool isFirst = true;
    for (int number : numbers)
    {
        if (isFirst)
        {
            result.append(std::to_string(number));
            isFirst = false;
        }
        else
        {
            result.append(", ");
            result.append(std::to_string(number));
        }
        if (number < 10)
            result.append(" ");
    }
    result.append(" ]");
    return result;
}