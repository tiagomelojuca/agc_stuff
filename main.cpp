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
    // agc::matrix<int> m1(3, 8, {{}, {4, 8, 6, 7, 8, 9, 10, 11, 12}});
    // agc::matrix<int> m2(3, 8, {{}, {4, 8, 6}});
    // agc::matrix<int> m3 = m2 / 2;

    // dbg_print_mtx(m3, "m3");
    // dbg_print_mtx(m2 / 2, "m2 / 5");
    // // dbg_print_mtx(m1, "m1");
    // dbg_print_mtx(m2, "m2");

    // agc::matrix<double> a(1, 4, { {4, 3, 2, 5} });
    // agc::matrix<double> b(4, 2, { {6, 1}, {4, 2}, {5, 7}, {3, 4} });
    // b = b.transpose();
    // auto c = a * b;

    // agc::matrix<double> d=b;

    // dbg_print_mtx(a, "a");
    // dbg_print_mtx(b, "b");
    // dbg_print_mtx(c, "c");
    // dbg_print_mtx(d, "d");

    // agc::matrix<int> a(2, 2, { {1, 2}, {4, 3} });
    // a = a.times(a.transpose());
    // dbg_print_mtx(a, "a");

    std::cout << "return 0" << std::endl;
    return 0;
}
