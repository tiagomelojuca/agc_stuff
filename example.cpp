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
    // print_matrix(res);

    agc::matrix<int> m1(3, 3);
    m1.fill_with(10);
    agc::matrix<int> m2(3, 3);
    m2.fill_with(7);
    agc::matrix<int> m3(0, 0);
    m3 = ((m1 + m2) * 10) / 2;
    // print_matrix(m3);

    agc::vector<double> v1(5);
    v1.fill_with(15);
    agc::vector<double> v2(5);
    v2.fill_with(5);
    agc::vector<double> v3(0);
    v3 = (3.0 * (v1 + v2)) / 2.5;
    // print_vector(v3);

    agc::vector<double> vconv1 = agc::linker<double>::mtx_to_vec(res);
    agc::vector<double> vconv2 = agc::linker<double>::mtx_to_vec(res.transpose());
    // std::cout << print_boolean(vconv1 == vconv2) << std::endl;

    agc::vector<int> vfrom(5, { 6, 5, 4, 3, 2 });
    agc::matrix<int> mconv1 = agc::linker<int>::vec_to_mtx_col(vfrom);
    agc::matrix<int> mconv2 = agc::linker<int>::vec_to_mtx_rol(vfrom);
    // std::cout << print_boolean(mconv1 == mconv2.transpose()) << std::endl;
    // std::cout << print_boolean(mconv2 == mconv1.transpose()) << std::endl;

    return 0;
}
