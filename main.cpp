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
    auto v = eqsys.solve();

    print_matrix(v);

    return 0;
}
