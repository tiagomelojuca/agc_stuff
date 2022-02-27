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

    agc::vector<double> v1(5);
    v1.fill_with(15);
    agc::vector<double> v2(5);
    v2.fill_with(5);
    v1 = v1.times(v2);
    print_vector(v1);

    return 0;
}
