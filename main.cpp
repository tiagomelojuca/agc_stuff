#include <iostream>

#include "agc.hpp"
#include "agcdbg.h"

int main()
{
    auto v = agc::solver::solve({
        { 1,  1, 1,  9 },
        { 2, -3, 4, 13 },
        { 3,  4, 5, 40 }
    }); print_vector(v);

    return 0;
}
