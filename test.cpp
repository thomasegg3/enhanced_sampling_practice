#include <iostream>
#include <cmath>
#include <iomanip>

int main() 
{
    double result = 1.0 / (2.0 - (std::pow(2.0, 1.0/3.0)));
    
    // Set output format to fixed-point with a specified number of decimal places
    std::cout << std::fixed << std::setprecision(10) << result << std::endl;
    
    return 0;
}
