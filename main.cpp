#include <iostream>
#include "agc.hpp"

int main()
{
    agc::solver<double> eqsys(3, 4, {
        { 1,  1, 1,  9 },
        { 2, -3, 4, 13 },
        { 3,  4, 5, 40 }
    });
    auto v = eqsys.solve();

    std::cout << "V = [X, Y, Z]" << std::endl;
    for (int i = 1; i <= v.size_rows(); i++)
    {
        for (int j = 1; j <= v.size_cols(); j++)
        {
            std::cout << "        " << v[i][j] << std::endl;
        }
    }

    return 0;
}
