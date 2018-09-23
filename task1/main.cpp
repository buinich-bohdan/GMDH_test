#include <iostream>

/*
 * #define SQR(x) x*x
 * if input will be SQR(1+1) result must be 4, but we have 3 because SQR(1+1) translates to 1+1*1+1
 * we must use
 * #define SQR(x) ((x)*(x))
 * then we have result ((1+1)*(1+1)) = 4
*/

// in C++11 add constexpr
template <typename T>
constexpr T SQR(T x){
    return x * x;
}

int main() {
    std::cout << SQR(1+1) << std::endl;
    std::cout << SQR(2) << std::endl;
    std::cout << SQR(2.2) << std::endl;
    return 0;
}