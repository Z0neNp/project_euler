#include <iostream>

bool isPythagoreanTriplet(int, int, int);
bool isValidRelation(int, int, int);


static int TRIPLET_SUM = 1000;

int main()
{
    std::cout << "Welcome to the \"Special Pythagorean triplet\" problem!\n";
    
    int a = 1;
    int b = 2;
    int c = TRIPLET_SUM - a - b;

    if (!isValidRelation(a, b, c))
    {
        std::cout << "There is no Pythagorean triple that meets the requirements" << std::endl;
        exit(0);
    }
    bool tripleNotFound = true;
    while (tripleNotFound && isValidRelation(a, b, c))
    {
        //std::cout << "Next Vertical iteration: " << a << ", " << b << ", " << c << std::endl;
        if (isPythagoreanTriplet(a, b, c))
            break;
        int temp_a = a;
        int temp_c = c;
        while (isValidRelation(temp_a + 1, b, temp_c - 1))
        {
            temp_a++;
            temp_c--;
            //std::cout << "\tNext Horizontal iteration: " << temp_a << ", " << b << ", " << temp_c << std::endl;
            if (isPythagoreanTriplet(temp_a, b, temp_c))
            {
                a = temp_a;
                c = temp_c;
                tripleNotFound = false;
                break;
            }
        }
        if (tripleNotFound)
        {
            b++;
            c--;
        }
    }
    std::cout << "The product is " << a << " * " << b << " * " << c << " = " << a * b * c << std::endl;

    std::cout << std::endl;
    exit(0);
}

bool isPythagoreanTriplet(int a, int b, int c)
{
    return std::pow(a, 2) + std::pow(b, 2) == std::pow(c, 2);
}

bool isValidRelation(int a, int b, int c)
{
    if (a < b)
        return b < c;
    return false;
}