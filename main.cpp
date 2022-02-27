#include <iostream>

#include "agc.hpp"

void dbg_print_mtx(const agc::matrix<int>& matriz, const char* str)
{
    std::cout << str << std::endl;
    for (int i = 1; i <= matriz.size_rows(); i++) {
        for (int j = 1; j <= matriz.size_cols(); j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void dbg_print_mtx(const agc::matrix<double>& matriz, const char* str)
{
    std::cout << str << std::endl;
    for (int i = 1; i <= matriz.size_rows(); i++) {
        for (int j = 1; j <= matriz.size_cols(); j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::cout << "bool ? " << (true ? "true" : "false") << std::endl;
    std::cout << "return 0" << std::endl;
    return 0;
}
