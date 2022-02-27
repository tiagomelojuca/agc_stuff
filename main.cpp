#include <iostream>

#include "agc.hpp"
#include "agcdbg.h"

int main()
{
    agc::solver<double> eqsys(3, 4, {
        { 1,  1, 1,  9 },
        { 2, -3, 4, 13 },
        { 3,  4, 5, 40 }
    });
    auto res = eqsys.solve();
    print_matrix(res);

    agc::matrix<int> m1(3, 3);
    m1.fill_with(10);
    agc::matrix<int> m2(3, 3);
    m2.fill_with(7);
    agc::matrix<int> m3(0, 0);
    m3 = ((m1 + m2) * 10) / 2;
    print_matrix(m3);

    agc::vector<double> v1(5);
    v1.fill_with(15);
    agc::vector<double> v2(5);
    v2.fill_with(5);
    v1 = v1.times(v2);
    print_vector(v1);

    return 0;
}
