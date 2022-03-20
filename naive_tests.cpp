#include <iostream>
#include <stdint.h>
#include <string>

#include "aecc.h"
#include "agc.hpp"
#include "agcdbg.h"

// ---------------------------------------------------------------------------------

int num_runs = 0;
int num_pass = 0;
void print_test_output(const char*, bool);
void print_tests_output();

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_construct()
{
    const std::string e_msg = "matrix size cannot be negative";

    agc::matrix<int8_t> m1(3, 3);
    const bool ok1 = m1[1][1] == 0 && m1[1][2] == 0 && m1[1][3] == 0 &&
                     m1[2][1] == 0 && m1[2][2] == 0 && m1[2][3] == 0 &&
                     m1[3][1] == 0 && m1[3][2] == 0 && m1[3][3] == 0;

    agc::matrix<int8_t> m2(3, 3, { {11, 12, 13},
                                   {21, 22, 23},
                                   {31, 32, 33} });
    const bool ok2 = m2[1][1] == 11 && m2[1][2] == 12 && m2[1][3] == 13 &&
                     m2[2][1] == 21 && m2[2][2] == 22 && m2[2][3] == 23 &&
                     m2[3][1] == 31 && m2[3][2] == 32 && m2[3][3] == 33;

    agc::matrix<int8_t> m3(m2);
    const bool ok3 = m3[1][1] == 11 && m3[1][2] == 12 && m3[1][3] == 13 &&
                     m3[2][1] == 21 && m3[2][2] == 22 && m3[2][3] == 23 &&
                     m3[3][1] == 31 && m3[3][2] == 32 && m3[3][3] == 33;

    agc::matrix<int8_t> m4(std::move(m3));
    const bool ok4 = m4[1][1] == 11 && m4[1][2] == 12 && m4[1][3] == 13 &&
                     m4[2][1] == 21 && m4[2][2] == 22 && m4[2][3] == 23 &&
                     m4[3][1] == 31 && m4[3][2] == 32 && m4[3][3] == 33 &&
                     m4.size_rows() == 3 && m4.size_cols() == 3 &&
                     m3.size_rows() == 0 && m3.size_cols() == 0;

    bool ok5 = false;
    try { agc::matrix<int8_t>(-1, 0); }
    catch (const std::invalid_argument& e) { ok5 = std::string(e.what()) == e_msg; }

    bool ok6 = false;
    try { agc::matrix<int8_t>(0, -1); }
    catch (const std::invalid_argument& e) { ok6 = std::string(e.what()) == e_msg; }

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6;
    print_test_output("RunTest_Matrix_should_be_able_to_construct", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_get_size()
{
    agc::matrix<int8_t> m(3, 7);
    const bool ok1 = m.size_rows() == 3;
    const bool ok2 = m.size_cols() == 7;

    const bool ok = ok1 && ok2;
    print_test_output("RunTest_Matrix_should_be_able_to_get_size", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_compare_sizes()
{
    agc::matrix<int8_t> m1(3, 7);
    agc::matrix<int8_t> m2(3, 7);
    agc::matrix<int8_t> m3(7, 3);

    const bool ok1 = m1.is_same_size(m2);
    const bool ok2 = !m1.is_same_size(m3);

    const bool ok = ok1 && ok2;
    print_test_output("RunTest_Matrix_should_be_able_to_compare_sizes", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_empty()
{
    agc::matrix<int8_t> m1(0, 0);
    agc::matrix<int8_t> m2(0, 1);
    agc::matrix<int8_t> m3(1, 0);
    agc::matrix<int8_t> m4(1, 1);

    const bool ok1 = m1.is_empty();
    const bool ok2 = m2.is_empty();
    const bool ok3 = m3.is_empty();
    const bool ok4 = !m4.is_empty();

    const bool ok = ok1 && ok2 && ok3 && ok4;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_empty", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_a_square_matrix()
{
    agc::matrix<int8_t> m1(0, 0);
    agc::matrix<int8_t> m2(0, 1);
    agc::matrix<int8_t> m3(1, 0);
    agc::matrix<int8_t> m4(1, 1);
    agc::matrix<int8_t> m5(2, 2);
    agc::matrix<int8_t> m6(1, 2);
    agc::matrix<int8_t> m7(2, 1);

    const bool ok1 = !m1.is_square_matrix();
    const bool ok2 = !m2.is_square_matrix();
    const bool ok3 = !m3.is_square_matrix();
    const bool ok4 = m4.is_square_matrix();
    const bool ok5 = m5.is_square_matrix();
    const bool ok6 = !m6.is_square_matrix();
    const bool ok7 = !m7.is_square_matrix();

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_a_square_matrix", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_a_rect_matrix()
{
    agc::matrix<int8_t> m1(0, 0);
    agc::matrix<int8_t> m2(0, 1);
    agc::matrix<int8_t> m3(1, 0);
    agc::matrix<int8_t> m4(1, 1);
    agc::matrix<int8_t> m5(2, 2);
    agc::matrix<int8_t> m6(1, 2);
    agc::matrix<int8_t> m7(2, 1);

    const bool ok1 = !m1.is_rectangular_matrix();
    const bool ok2 = !m2.is_rectangular_matrix();
    const bool ok3 = !m3.is_rectangular_matrix();
    const bool ok4 = !m4.is_rectangular_matrix();
    const bool ok5 = !m5.is_rectangular_matrix();
    const bool ok6 = m6.is_rectangular_matrix();
    const bool ok7 = m7.is_rectangular_matrix();

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_a_rect_matrix", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_a_row_matrix()
{
    agc::matrix<int8_t> m1(0, 0);
    agc::matrix<int8_t> m2(0, 1);
    agc::matrix<int8_t> m3(1, 0);
    agc::matrix<int8_t> m4(1, 1);
    agc::matrix<int8_t> m5(2, 2);
    agc::matrix<int8_t> m6(1, 2);
    agc::matrix<int8_t> m7(2, 1);

    const bool ok1 = !m1.is_row_matrix();
    const bool ok2 = !m2.is_row_matrix();
    const bool ok3 = !m3.is_row_matrix();
    const bool ok4 = m4.is_row_matrix();
    const bool ok5 = !m5.is_row_matrix();
    const bool ok6 = m6.is_row_matrix();
    const bool ok7 = !m7.is_row_matrix();

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_a_row_matrix", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_a_col_matrix()
{
    agc::matrix<int8_t> m1(0, 0);
    agc::matrix<int8_t> m2(0, 1);
    agc::matrix<int8_t> m3(1, 0);
    agc::matrix<int8_t> m4(1, 1);
    agc::matrix<int8_t> m5(2, 2);
    agc::matrix<int8_t> m6(1, 2);
    agc::matrix<int8_t> m7(2, 1);

    const bool ok1 = !m1.is_column_matrix();
    const bool ok2 = !m2.is_column_matrix();
    const bool ok3 = !m3.is_column_matrix();
    const bool ok4 = m4.is_column_matrix();
    const bool ok5 = !m5.is_column_matrix();
    const bool ok6 = !m6.is_column_matrix();
    const bool ok7 = m7.is_column_matrix();

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_a_col_matrix", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_null_matrix()
{
    agc::matrix<int8_t> m1(3, 3);
    agc::matrix<int8_t> m2(5, 5);
    agc::matrix<int8_t> m3(5, 5);
    m3[4][5] = 1;

    bool m1_has_only_zeros = true;
    for (int i = 1; i <= m1.size_rows(); i++)
    {
        for (int j = 1; j <= m1.size_cols(); j++)
        { if (m1[i][j] != 0) { m1_has_only_zeros = false; } }
    }
    const bool ok1 = m1_has_only_zeros;

    bool m2_has_only_zeros = true;
    for (int i = 1; i <= m2.size_rows(); i++)
    {
        for (int j = 1; j <= m2.size_cols(); j++)
        { if (m2[i][j] != 0) { m2_has_only_zeros = false; } }
    }
    const bool ok2 = m2_has_only_zeros;

    bool m3_has_only_zeros = true;
    for (int i = 1; i <= m3.size_rows(); i++)
    {
        for (int j = 1; j <= m3.size_cols(); j++)
        { if (m3[i][j] != 0) { m3_has_only_zeros = false; } }
    }
    const bool ok3 = !m3_has_only_zeros;

    const bool ok = ok1 && ok2 && ok3;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_null_matrix", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_triangular_upper()
{
    agc::matrix<int8_t> m01(3, 3, { {0, 0, 0} ,
                                    {0, 0, 0} ,
                                    {0, 0, 0} });

    agc::matrix<int8_t> m02(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m03(3, 3, { {1, 2, 3} ,
                                    {0, 5, 6} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m04(3, 3, { {1, 0, 3} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m05(3, 3, { {1, 0, 0} ,
                                    {0, 5, 6} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m06(3, 3, { {1, 2, 0} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m07(3, 3, { {1, 0, 0} ,
                                    {4, 5, 0} ,
                                    {7, 8, 9} });

    agc::matrix<int8_t> m08(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {7, 0, 9} });

    agc::matrix<int8_t> m09(3, 3, { {1, 0, 0} ,
                                    {4, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m10(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {0, 8, 9} });

    agc::matrix<int8_t> m11(3, 3, { {1, 2, 3} ,
                                    {4, 5, 6} ,
                                    {7, 8, 9} });

    agc::matrix<int8_t> m12(1, 1, { {1} });

    agc::matrix<int8_t> m13(1, 2);

    const bool ok01 = m01.is_triangular_upper_matrix();
    const bool ok02 = m02.is_triangular_upper_matrix();
    const bool ok03 = m03.is_triangular_upper_matrix();
    const bool ok04 = m04.is_triangular_upper_matrix();
    const bool ok05 = m05.is_triangular_upper_matrix();
    const bool ok06 = m06.is_triangular_upper_matrix();
    const bool ok07 = !m07.is_triangular_upper_matrix();
    const bool ok08 = !m08.is_triangular_upper_matrix();
    const bool ok09 = !m09.is_triangular_upper_matrix();
    const bool ok10 = !m10.is_triangular_upper_matrix();
    const bool ok11 = !m11.is_triangular_upper_matrix();
    const bool ok12 = m12.is_triangular_upper_matrix();
    const bool ok13 = !m13.is_triangular_upper_matrix();

    const bool ok = ok01 && ok02 && ok03 && ok04 && ok05 &&
                    ok06 && ok07 && ok08 && ok09 && ok10 &&
                    ok11 && ok12 && ok13;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_triangular_upper", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_triangular_lower()
{
    agc::matrix<int8_t> m01(3, 3, { {0, 0, 0} ,
                                    {0, 0, 0} ,
                                    {0, 0, 0} });

    agc::matrix<int8_t> m02(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m03(3, 3, { {1, 2, 3} ,
                                    {0, 5, 6} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m04(3, 3, { {1, 0, 3} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m05(3, 3, { {1, 0, 0} ,
                                    {0, 5, 6} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m06(3, 3, { {1, 2, 0} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m07(3, 3, { {1, 0, 0} ,
                                    {4, 5, 0} ,
                                    {7, 8, 9} });

    agc::matrix<int8_t> m08(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {7, 0, 9} });

    agc::matrix<int8_t> m09(3, 3, { {1, 0, 0} ,
                                    {4, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m10(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {0, 8, 9} });

    agc::matrix<int8_t> m11(3, 3, { {1, 2, 3} ,
                                    {4, 5, 6} ,
                                    {7, 8, 9} });

    agc::matrix<int8_t> m12(1, 1, { {1} });

    agc::matrix<int8_t> m13(1, 2);

    const bool ok01 = m01.is_triangular_lower_matrix();
    const bool ok02 = m02.is_triangular_lower_matrix();
    const bool ok03 = !m03.is_triangular_lower_matrix();
    const bool ok04 = !m04.is_triangular_lower_matrix();
    const bool ok05 = !m05.is_triangular_lower_matrix();
    const bool ok06 = !m06.is_triangular_lower_matrix();
    const bool ok07 = m07.is_triangular_lower_matrix();
    const bool ok08 = m08.is_triangular_lower_matrix();
    const bool ok09 = m09.is_triangular_lower_matrix();
    const bool ok10 = m10.is_triangular_lower_matrix();
    const bool ok11 = !m11.is_triangular_lower_matrix();
    const bool ok12 = m12.is_triangular_lower_matrix();
    const bool ok13 = !m13.is_triangular_lower_matrix();

    const bool ok = ok01 && ok02 && ok03 && ok04 && ok05 &&
                    ok06 && ok07 && ok08 && ok09 && ok10 &&
                    ok11 && ok12 && ok13;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_triangular_lower", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_triangular()
{
    agc::matrix<int8_t> m01(3, 3, { {0, 0, 0} ,
                                    {0, 0, 0} ,
                                    {0, 0, 0} });

    agc::matrix<int8_t> m02(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m03(3, 3, { {1, 2, 3} ,
                                    {0, 5, 6} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m04(3, 3, { {1, 0, 3} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m05(3, 3, { {1, 0, 0} ,
                                    {0, 5, 6} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m06(3, 3, { {1, 2, 0} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m07(3, 3, { {1, 0, 0} ,
                                    {4, 5, 0} ,
                                    {7, 8, 9} });

    agc::matrix<int8_t> m08(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {7, 0, 9} });

    agc::matrix<int8_t> m09(3, 3, { {1, 0, 0} ,
                                    {4, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m10(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {0, 8, 9} });

    agc::matrix<int8_t> m11(3, 3, { {1, 2, 3} ,
                                    {4, 5, 6} ,
                                    {7, 8, 9} });

    agc::matrix<int8_t> m12(1, 1, { {1} });

    agc::matrix<int8_t> m13(1, 2);

    const bool ok01 = m01.is_triangular_matrix();
    const bool ok02 = m02.is_triangular_matrix();
    const bool ok03 = m03.is_triangular_matrix();
    const bool ok04 = m04.is_triangular_matrix();
    const bool ok05 = m05.is_triangular_matrix();
    const bool ok06 = m06.is_triangular_matrix();
    const bool ok07 = m07.is_triangular_matrix();
    const bool ok08 = m08.is_triangular_matrix();
    const bool ok09 = m09.is_triangular_matrix();
    const bool ok10 = m10.is_triangular_matrix();
    const bool ok11 = !m11.is_triangular_matrix();
    const bool ok12 = m12.is_triangular_matrix();
    const bool ok13 = !m13.is_triangular_matrix();

    const bool ok = ok01 && ok02 && ok03 && ok04 && ok05 &&
                    ok06 && ok07 && ok08 && ok09 && ok10 &&
                    ok11 && ok12 && ok13;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_triangular", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_diagonal()
{
    agc::matrix<int8_t> m01(3, 3, { {0, 0, 0} ,
                                    {0, 0, 0} ,
                                    {0, 0, 0} });

    agc::matrix<int8_t> m02(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m03(3, 3, { {1, 2, 3} ,
                                    {0, 5, 6} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m04(3, 3, { {1, 0, 3} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m05(3, 3, { {1, 0, 0} ,
                                    {0, 5, 6} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m06(3, 3, { {1, 2, 0} ,
                                    {0, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m07(3, 3, { {1, 0, 0} ,
                                    {4, 5, 0} ,
                                    {7, 8, 9} });

    agc::matrix<int8_t> m08(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {7, 0, 9} });

    agc::matrix<int8_t> m09(3, 3, { {1, 0, 0} ,
                                    {4, 5, 0} ,
                                    {0, 0, 9} });

    agc::matrix<int8_t> m10(3, 3, { {1, 0, 0} ,
                                    {0, 5, 0} ,
                                    {0, 8, 9} });

    agc::matrix<int8_t> m11(3, 3, { {1, 2, 3} ,
                                    {4, 5, 6} ,
                                    {7, 8, 9} });

    agc::matrix<int8_t> m12(1, 1, { {1} });

    agc::matrix<int8_t> m13(1, 2);

    const bool ok01 = m01.is_diagonal_matrix();
    const bool ok02 = m02.is_diagonal_matrix();
    const bool ok03 = !m03.is_diagonal_matrix();
    const bool ok04 = !m04.is_diagonal_matrix();
    const bool ok05 = !m05.is_diagonal_matrix();
    const bool ok06 = !m06.is_diagonal_matrix();
    const bool ok07 = !m07.is_diagonal_matrix();
    const bool ok08 = !m08.is_diagonal_matrix();
    const bool ok09 = !m09.is_diagonal_matrix();
    const bool ok10 = !m10.is_diagonal_matrix();
    const bool ok11 = !m11.is_diagonal_matrix();
    const bool ok12 = m12.is_diagonal_matrix();
    const bool ok13 = !m13.is_diagonal_matrix();

    const bool ok = ok01 && ok02 && ok03 && ok04 && ok05 &&
                    ok06 && ok07 && ok08 && ok09 && ok10 &&
                    ok11 && ok12 && ok13;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_diagonal", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_scalar()
{
    agc::matrix<int8_t> m1(3, 3, { {0, 0, 0} ,
                                   {0, 0, 0} ,
                                   {0, 0, 0} });

    agc::matrix<int8_t> m2(3, 3, { {1, 0, 0} ,
                                   {0, 1, 0} ,
                                   {0, 0, 1} });

    agc::matrix<int8_t> m3(3, 3, { {3, 0, 0} ,
                                   {0, 3, 0} ,
                                   {0, 0, 3} });

    agc::matrix<int8_t> m4(3, 3, { {3, 0, 0} ,
                                   {0, 3, 0} ,
                                   {3, 0, 3} });

    agc::matrix<int8_t> m5(3, 3, { {3, 0, 3} ,
                                   {0, 3, 0} ,
                                   {0, 0, 3} });

    agc::matrix<int8_t> m6(1, 1, { {1} });

    agc::matrix<int8_t> m7(1, 2);

    const bool ok1 = m1.is_scalar_matrix();
    const bool ok2 = m2.is_scalar_matrix();
    const bool ok3 = m3.is_scalar_matrix();
    const bool ok4 = !m4.is_scalar_matrix();
    const bool ok5 = !m5.is_scalar_matrix();
    const bool ok6 = m6.is_scalar_matrix();
    const bool ok7 = !m7.is_scalar_matrix();

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_scalar", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_identity()
{
    agc::matrix<int8_t> m1(3, 3, { {0, 0, 0} ,
                                   {0, 0, 0} ,
                                   {0, 0, 0} });

    agc::matrix<int8_t> m2(3, 3, { {1, 0, 0} ,
                                   {0, 1, 0} ,
                                   {0, 0, 1} });

    agc::matrix<int8_t> m3(3, 3, { {3, 0, 0} ,
                                   {0, 3, 0} ,
                                   {0, 0, 3} });

    agc::matrix<int8_t> m4(3, 3, { {3, 0, 0} ,
                                   {0, 3, 0} ,
                                   {3, 0, 3} });

    agc::matrix<int8_t> m5(3, 3, { {3, 0, 3} ,
                                   {0, 3, 0} ,
                                   {0, 0, 3} });

    agc::matrix<int8_t> m6(1, 1, { {1} });

    agc::matrix<int8_t> m7(1, 2);

    const bool ok1 = !m1.is_identity_matrix();
    const bool ok2 = m2.is_identity_matrix();
    const bool ok3 = !m3.is_identity_matrix();
    const bool ok4 = !m4.is_identity_matrix();
    const bool ok5 = !m5.is_identity_matrix();
    const bool ok6 = m6.is_identity_matrix();
    const bool ok7 = !m7.is_identity_matrix();

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_identity", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_transform_its_elements()
{
    agc::matrix<int8_t> m1(3, 3, { {3, 0, 0} ,
                                   {0, 3, 0} ,
                                   {0, 0, 3} });
    agc::matrix<int8_t> m2(3, 3, { {1, 2, 3} ,
                                   {4, 5, 6} ,
                                   {3, 2, 1} });

    m1.transform(2, 3, 2, 3, [](int8_t p) { return p + 1; });
    const bool ok1 = m1[1][1] == 3 && m1[1][2] == 0 && m1[1][3] == 0 &&
                     m1[2][1] == 0 && m1[2][2] == 4 && m1[2][3] == 1 &&
                     m1[3][1] == 0 && m1[3][2] == 1 && m1[3][3] == 4;

    m1.transform(2, 3, 2, 3, m2, [](int8_t p1, int8_t p2) { return p1 + p2; });
    const bool ok2 = m1[1][1] == 3 && m1[1][2] == 0 && m1[1][3] == 0 &&
                     m1[2][1] == 0 && m1[2][2] == 9 && m1[2][3] == 7 &&
                     m1[3][1] == 0 && m1[3][2] == 3 && m1[3][3] == 5;

    m1.transform([](int8_t p) { return p + 2; });
    const bool ok3 = m1[1][1] == 5 && m1[1][2] ==  2 && m1[1][3] == 2 &&
                     m1[2][1] == 2 && m1[2][2] == 11 && m1[2][3] == 9 &&
                     m1[3][1] == 2 && m1[3][2] ==  5 && m1[3][3] == 7;

    m1.transform(m2, [](int8_t p1, int8_t p2) { return p1 - p2; });
    const bool ok4 = m1[1][1] ==  4 && m1[1][2] == 0 && m1[1][3] == -1 &&
                     m1[2][1] == -2 && m1[2][2] == 6 && m1[2][3] ==  3 &&
                     m1[3][1] == -1 && m1[3][2] == 3 && m1[3][3] ==  6;

    m1.fill_with(7);
    const bool ok5 = m1[1][1] == 7 && m1[1][2] == 7 && m1[1][3] == 7 &&
                     m1[2][1] == 7 && m1[2][2] == 7 && m1[2][3] == 7 &&
                     m1[3][1] == 7 && m1[3][2] == 7 && m1[3][3] == 7;

    bool ok6 = false;
    try
    {
        m1.transform(1, 3, 1, 3, agc::matrix<int8_t>(1, 1), [](int8_t p1, int8_t p2) { return 0; });
    }
    catch (const std::domain_error& e)
    {
        ok6 = std::string(e.what()) == "matrix transform must have same size";
    }

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6;
    print_test_output("RunTest_Matrix_should_be_able_to_transform_its_elements", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_access_elements_safely()
{
    agc::matrix<int8_t> m1(3, 3);

    const std::string e_msg_row = "matrix row access out of boundary";
    const std::string e_msg_col = "matrix column access out of boundary";
    auto is_throwing_for_row = [&e_msg_row, &m1](int i, int j) -> bool
    {
        bool current_ok = false;
        try { int8_t value_out_of_range = m1[i][j]; }
        catch (const std::out_of_range& e) { current_ok = std::string(e.what()) == e_msg_row; }
        return current_ok;
    };
    auto is_throwing_for_col = [&e_msg_col, &m1](int i, int j) -> bool
    {
        bool current_ok = false;
        try { int8_t value_out_of_range = m1[i][j]; }
        catch (const std::out_of_range& e) { current_ok = std::string(e.what()) == e_msg_col; }
        return current_ok;
    };

    const bool ok01 = !is_throwing_for_row(1, 1);
    const bool ok02 = !is_throwing_for_row(2, 2);
    const bool ok03 = !is_throwing_for_row(3, 3);
    const bool ok04 = is_throwing_for_row(0, 1);
    const bool ok05 = !is_throwing_for_row(1, 0);
    const bool ok06 = is_throwing_for_row(0, 0);
    const bool ok07 = is_throwing_for_row(4, 1);
    const bool ok08 = !is_throwing_for_row(1, 4);
    const bool ok09 = is_throwing_for_row(4, 4);
    const bool ok10 = is_throwing_for_row(-1, 1);
    const bool ok11 = !is_throwing_for_row(1, -1);
    const bool ok12 = is_throwing_for_row(-1, -1);
    const bool ok13 = !is_throwing_for_col(1, 1);
    const bool ok14 = !is_throwing_for_col(1, 1);
    const bool ok15 = !is_throwing_for_col(1, 1);
    const bool ok16 = !is_throwing_for_col(0, 1);
    const bool ok17 = is_throwing_for_col(1, 0);
    const bool ok18 = !is_throwing_for_col(4, 1);
    const bool ok19 = is_throwing_for_col(1, 4);
    const bool ok20 = !is_throwing_for_col(-1, 1);
    const bool ok21 = is_throwing_for_col(1, -1);

    const bool ok = ok01 && ok02 && ok03 && ok04 && ok05 && ok06 &&
                    ok07 && ok08 && ok09 && ok10 && ok11 && ok12 &&
                    ok13 && ok14 && ok15 && ok16 && ok17 && ok18 &&
                    ok19 && ok20 && ok21;
    print_test_output("RunTest_Matrix_should_be_able_to_access_elements_safely", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_assign_copy()
{
    agc::matrix<int8_t> m1(2, 3, { {11, 12, 13},
                                   {21, 22, 23} });
    auto m2 = m1;

    const bool ok1 = m1.size_rows() == 2 && m1.size_cols() == 3;
    const bool ok2 = m2.size_rows() == m1.size_rows() && m2.size_cols() == m1.size_cols();
    const bool ok3 = m1[1][1] == 11 && m1[1][2] == 12 && m1[1][3] == 13 &&
                     m1[2][1] == 21 && m1[2][2] == 22 && m1[2][3] == 23;
    const bool ok4 = m2[1][1] == 11 && m2[1][2] == 12 && m2[1][3] == 13 &&
                     m2[2][1] == 21 && m2[2][2] == 22 && m2[2][3] == 23;

    const bool ok = ok1 && ok2 && ok3 && ok4;
    print_test_output("RunTest_Matrix_should_be_able_to_assign_copy", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_assign_move()
{
    agc::matrix<int8_t> m_tmp(2, 3, { {11, 12, 13},
                                      {21, 22, 23} });
    auto m1 = std::move(m_tmp);

    const bool ok1 = m1[1][1] == 11 && m1[1][2] == 12 && m1[1][3] == 13 &&
                     m1[2][1] == 21 && m1[2][2] == 22 && m1[2][3] == 23;
    const bool ok2 = m1.size_rows() == 2 && m1.size_cols() == 3;
    const bool ok3 = m_tmp.size_rows() == 0 && m_tmp.size_cols() == 0;

    auto m2 = agc::matrix<int8_t>(2, 3, { {11, 12, 13},
                                          {21, 22, 23} });
    const bool ok4 = m2[1][1] == 11 && m2[1][2] == 12 && m2[1][3] == 13 &&
                     m2[2][1] == 21 && m2[2][2] == 22 && m2[2][3] == 23;

    const bool ok = ok1 && ok2 && ok3 && ok4;
    print_test_output("RunTest_Matrix_should_be_able_to_assign_move", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_compare()
{
    const agc::matrix<int8_t> m01(3, 3, { {1, 2, 3} ,
                                          {4, 5, 6} ,
                                          {7, 8, 9} });

    const agc::matrix<int8_t> m02(3, 3, { {0, 2, 3} ,
                                          {4, 5, 6} ,
                                          {7, 8, 9} });

    const agc::matrix<int8_t> m03(3, 3, { {1, 0, 3} ,
                                          {4, 5, 6} ,
                                          {7, 8, 9} });

    const agc::matrix<int8_t> m04(3, 3, { {1, 2, 0} ,
                                          {4, 5, 6} ,
                                          {7, 8, 9} });

    const agc::matrix<int8_t> m05(3, 3, { {1, 2, 3} ,
                                          {0, 5, 6} ,
                                          {7, 8, 9} });

    const agc::matrix<int8_t> m06(3, 3, { {1, 2, 3} ,
                                          {4, 0, 6} ,
                                          {7, 8, 9} });

    const agc::matrix<int8_t> m07(3, 3, { {1, 2, 3} ,
                                          {4, 5, 0} ,
                                          {7, 8, 9} });

    const agc::matrix<int8_t> m08(3, 3, { {1, 2, 3} ,
                                          {4, 5, 6} ,
                                          {0, 8, 9} });

    const agc::matrix<int8_t> m09(3, 3, { {1, 2, 3} ,
                                          {4, 5, 6} ,
                                          {7, 0, 9} });

    const agc::matrix<int8_t> m10(3, 3, { {1, 2, 3} ,
                                          {4, 5, 6} ,
                                          {7, 8, 0} });

    const agc::matrix<int8_t> m11(3, 3, { {1, 2, 3} ,
                                          {4, 5, 6} ,
                                          {7, 8, 9} });

    const agc::matrix<int8_t> m12(3, 2, { {1, 2} ,
                                          {4, 5} ,
                                          {7, 8} });

    const agc::matrix<int8_t> m13(2, 3, { {1, 2, 3} ,
                                          {4, 5, 6} });

    const agc::matrix<int8_t> m14(2, 2, { {1, 2} ,
                                          {4, 5} });

    const bool ok01 = !(m01 == m02);
    const bool ok02 = !(m01 == m03);
    const bool ok03 = !(m01 == m04);
    const bool ok04 = !(m01 == m05);
    const bool ok05 = !(m01 == m06);
    const bool ok06 = !(m01 == m07);
    const bool ok07 = !(m01 == m08);
    const bool ok08 = !(m01 == m09);
    const bool ok09 = !(m01 == m10);
    const bool ok10 = m01 == m11;
    const bool ok11 = !(m01 == m12);
    const bool ok12 = !(m01 == m13);
    const bool ok13 = !(m01 == m14);

    const bool ok14 = m01 != m02;
    const bool ok15 = m01 != m03;
    const bool ok16 = m01 != m04;
    const bool ok17 = m01 != m05;
    const bool ok18 = m01 != m06;
    const bool ok19 = m01 != m07;
    const bool ok20 = m01 != m08;
    const bool ok21 = m01 != m09;
    const bool ok22 = m01 != m10;
    const bool ok23 = !(m01 != m11);
    const bool ok24 = m01 != m12;
    const bool ok25 = m01 != m13;
    const bool ok26 = m01 != m14;

    const bool ok = ok01 && ok02 && ok03 && ok04 && ok05 && ok06 &&
                    ok07 && ok08 && ok09 && ok10 && ok11 && ok12 &&
                    ok13 && ok14 && ok15 && ok16 && ok17 && ok18 &&
                    ok19 && ok20 && ok21 && ok22 && ok23 && ok24 &&
                    ok25 && ok26;
    print_test_output("RunTest_Matrix_should_be_able_to_compare", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_increment()
{
    agc::matrix<int8_t> m(3, 3, { {5, 5, 5} ,
                                  {5, 5, 5} ,
                                  {5, 5, 5} });
    m++;
    ++m;

    const bool ok = m[1][1] == 7 && m[1][2] == 7 && m[1][3] == 7 &&
                    m[2][1] == 7 && m[2][2] == 7 && m[2][3] == 7 &&
                    m[3][1] == 7 && m[3][2] == 7 && m[3][3] == 7;
    print_test_output("RunTest_Matrix_should_be_able_to_increment", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_decrement()
{
    agc::matrix<int8_t> m(3, 3, { {5, 5, 5} ,
                                  {5, 5, 5} ,
                                  {5, 5, 5} });
    m--;
    --m;

    const bool ok = m[1][1] == 3 && m[1][2] == 3 && m[1][3] == 3 &&
                    m[2][1] == 3 && m[2][2] == 3 && m[2][3] == 3 &&
                    m[3][1] == 3 && m[3][2] == 3 && m[3][3] == 3;
    print_test_output("RunTest_Matrix_should_be_able_to_decrement", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_addition_assign()
{
    const std::string e_msg = "matrix addition must have same size";

    agc::matrix<int8_t> m1(3, 3, { {3, 0, 0} ,
                                   {0, 3, 0} ,
                                   {0, 0, 3} });
    agc::matrix<int8_t> m2(3, 3, { {1, 2, 3} ,
                                   {4, 5, 6} ,
                                   {3, 2, 1} });
    m1 += m2;

    const bool ok1 = m1[1][1] == 4 && m1[1][2] == 2 && m1[1][3] == 3 &&
                     m1[2][1] == 4 && m1[2][2] == 8 && m1[2][3] == 6 &&
                     m1[3][1] == 3 && m1[3][2] == 2 && m1[3][3] == 4;

    bool ok2 = false;
    try { m1 += agc::matrix<int8_t>(2, 2); }
    catch (const std::domain_error& e) { ok2 = std::string(e.what()) == e_msg; }

    const bool ok = ok1 && ok2;
    print_test_output("RunTest_Matrix_should_be_able_to_addition_assign", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_subtraction_assign()
{
    const std::string e_msg = "matrix subtraction must have same size";

    agc::matrix<int8_t> m1(3, 3, { {1, 2, 3} ,
                                   {4, 5, 6} ,
                                   {3, 2, 1} });
    agc::matrix<int8_t> m2(3, 3, { {3, 0, 0} ,
                                   {0, 3, 0} ,
                                   {0, 0, 3} });
    m1 -= m2;

    const bool ok1 = m1[1][1] == -2 && m1[1][2] == 2 && m1[1][3] ==  3 &&
                     m1[2][1] ==  4 && m1[2][2] == 2 && m1[2][3] ==  6 &&
                     m1[3][1] ==  3 && m1[3][2] == 2 && m1[3][3] == -2;

    bool ok2 = false;
    try { m1 -= agc::matrix<int8_t>(2, 2); }
    catch (const std::domain_error& e) { ok2 = std::string(e.what()) == e_msg; }

    const bool ok = ok1 && ok2;
    print_test_output("RunTest_Matrix_should_be_able_to_subtraction_assign", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_multiplication_assign()
{
    const std::string e_msg = "matrix multiplication requires numColumns(A) == numRows(B)";

    agc::matrix<int8_t> m1(3, 3, { {1, 2, 3} ,
                                   {4, 5, 6} ,
                                   {3, 2, 1} });
    m1 *= 2;

    const bool ok01 = m1[1][1] == 2 && m1[1][2] ==  4 && m1[1][3] ==  6 &&
                      m1[2][1] == 8 && m1[2][2] == 10 && m1[2][3] == 12 &&
                      m1[3][1] == 6 && m1[3][2] ==  4 && m1[3][3] ==  2;

    agc::matrix<int8_t> m2(3, 2, { {2, 3} ,
                                   {1, 0} ,
                                   {4, 5} });

    agc::matrix<int8_t> m3(2, 2, { {3, 1} ,
                                   {2, 4} });

    agc::matrix<int8_t> m4 = m2 * m3;
    const bool ok02 = m4.size_rows() == 3;
    const bool ok03 = m4.size_cols() == 2;
    const bool ok04 = m4[1][1] == 12 && m4[1][2] == 14 &&
                      m4[2][1] ==  3 && m4[2][2] ==  1 &&
                      m4[3][1] == 22 && m4[3][2] == 24;

    agc::matrix<int8_t> m5(3, 3);
    agc::matrix<int8_t> m6(2, 3);
    agc::matrix<int8_t> m7(3, 2);
    agc::matrix<int8_t> m8(2, 2);

    bool ok05 = false;
    try { auto m9 = m5 * m5; ok05 = true; }
    catch (const std::domain_error& e) {}

    bool ok06 = false;
    try { auto m9 = m5 * m6; }
    catch (const std::domain_error& e) { ok06 = std::string(e.what()) == e_msg; }

    bool ok07 = false;
    try { auto m9 = m5 * m7; ok07 = true; }
    catch (const std::domain_error& e) {}

    bool ok08 = false;
    try { auto m9 = m5 * m8; }
    catch (const std::domain_error& e) { ok08 = std::string(e.what()) == e_msg; }

    bool ok09 = false;
    try { auto m9 = m6 * m5; ok09 = true; }
    catch (const std::domain_error& e) {}

    bool ok10 = false;
    try { auto m9 = m6 * m6; }
    catch (const std::domain_error& e) { ok10 = std::string(e.what()) == e_msg; }

    bool ok11 = false;
    try { auto m9 = m6 * m7; ok11 = true; }
    catch (const std::domain_error& e) {}
    
    bool ok12 = false;
    try { auto m9 = m6 * m8; }
    catch (const std::domain_error& e) { ok12 = std::string(e.what()) == e_msg; }

    bool ok13 = false;
    try { auto m9 = m7 * m5; }
    catch (const std::domain_error& e) { ok13 = std::string(e.what()) == e_msg; }

    bool ok14 = false;
    try { auto m9 = m7 * m6; ok14 = true; }
    catch (const std::domain_error& e) {}

    bool ok15 = false;
    try { auto m9 = m7 * m7; }
    catch (const std::domain_error& e) { ok15 = std::string(e.what()) == e_msg; }

    bool ok16 = false;
    try { auto m9 = m7 * m8; ok16 = true; }
    catch (const std::domain_error& e) {}

    bool ok17 = false;
    try { auto m9 = m8 * m5; }
    catch (const std::domain_error& e) { ok17 = std::string(e.what()) == e_msg; }

    bool ok18 = false;
    try { auto m9 = m8 * m6; ok18 = true; }
    catch (const std::domain_error& e) {}

    bool ok19 = false;
    try { auto m9 = m8 * m7; }
    catch (const std::domain_error& e) { ok19 = std::string(e.what()) == e_msg; }

    bool ok20 = false;
    try { auto m9 = m8 * m8; ok20 = true; }
    catch (const std::domain_error& e) {}

    const bool ok = ok01 && ok02 && ok03 && ok04 && ok05 && ok06 && ok07 && ok08 && ok09 && ok10 &&
                    ok11 && ok12 && ok13 && ok14 && ok15 && ok16 && ok17 && ok18 && ok19 && ok20;
    print_test_output("RunTest_Matrix_should_be_able_to_multiplication_assign", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_division_assign()
{
    const std::string e_msg = "matrix divison by zero is not allowed";

    agc::matrix<int8_t> m(3, 3, { {2,  4,  6} ,
                                  {8, 10, 12} ,
                                  {6,  4,  2} });
    m /= 2;

    const bool ok1 = m[1][1] == 1 && m[1][2] == 2 && m[1][3] == 3 &&
                     m[2][1] == 4 && m[2][2] == 5 && m[2][3] == 6 &&
                     m[3][1] == 3 && m[3][2] == 2 && m[3][3] == 1;

    bool ok2 = false;
    try { m /= 0; }
    catch (const std::domain_error& e) { ok2 = std::string(e.what()) == e_msg; }

    const bool ok = ok1 && ok2;
    print_test_output("RunTest_Matrix_should_be_able_to_division_assign", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_times()
{
    const std::string e_msg = "matrix times must have same size";

    agc::matrix<int8_t> m1(3, 3, { {1, 2, 3} ,
                                   {4, 5, 6} ,
                                   {3, 2, 1} });

    agc::matrix<int8_t> m2(3, 3, { {2, 1, 3} ,
                                   {5, 4, 6} ,
                                   {2, 3, 1} });

    agc::matrix<int8_t> m3 = m1.times(m2);

    const bool ok1 = m3[1][1] ==  2 && m3[1][2] ==  2 && m3[1][3] ==  9 &&
                     m3[2][1] == 20 && m3[2][2] == 20 && m3[2][3] == 36 &&
                     m3[3][1] ==  6 && m3[3][2] ==  6 && m3[3][3] ==  1;

    bool ok2 = false;
    try { m1.times(agc::matrix<int8_t>(2, 2)); }
    catch (const std::domain_error& e) { ok2 = std::string(e.what()) == e_msg; }

    const bool ok = ok1 && ok2;
    print_test_output("RunTest_Matrix_should_be_able_to_times", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_pow()
{
    const std::string e_sqr_m_msg = "matrix pow requires a square matrix";
    const std::string e_inv_n_msg = "matrix pow requires n >= 1";

    agc::matrix<int8_t> m1(3, 3, { {1,  2,  3} ,
                                   {0, -1, -2} ,
                                   {1,  4,  1} });

    auto m2 = m1.pow(1);
    auto m3 = m1.pow(3);

    const bool ok1 = m2[1][1] == 1 && m2[1][2] ==  2 && m2[1][3] ==  3 &&
                     m2[2][1] == 0 && m2[2][2] == -1 && m2[2][3] == -2 &&
                     m2[3][1] == 1 && m2[3][2] ==  4 && m2[3][3] ==  1;

    const bool ok2 = m3[1][1] ==  6 && m3[1][2] ==  4 && m3[1][3] == -10 &&
                     m3[2][1] == -2 && m3[2][2] ==  3 && m3[2][3] ==   8 &&
                     m3[3][1] == -2 && m3[3][2] == -14 && m3[3][3] == -2;

    bool ok3 = false;
    try { agc::matrix<int8_t>(3, 2).pow(1); }
    catch (const std::domain_error& e) { ok3 = std::string(e.what()) == e_sqr_m_msg; }

    bool ok4 = false;
    try { agc::matrix<int8_t>(3, 3).pow(0); }
    catch (const std::domain_error& e) { ok4 = std::string(e.what()) == e_inv_n_msg; }

    const bool ok = ok1 && ok2 && ok3 && ok4;
    print_test_output("RunTest_Matrix_should_be_able_to_pow", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_transpose()
{
    agc::matrix<int8_t> m1(3, 2, { {1,  2} ,
                                   {0, -1} ,
                                   {1,  4} });
    auto m2 = m1.transpose();

    const bool ok = m2[1][1] == 1 && m2[1][2] ==  0 && m2[1][3] == 1 &&
                    m2[2][1] == 2 && m2[2][2] == -1 && m2[2][3] == 4;
    print_test_output("RunTest_Matrix_should_be_able_to_transpose", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_get_identity()
{
    const std::string e_msg = "matrix identity requires a square matrix";

    agc::matrix<int8_t> m1(1, 1);
    agc::matrix<int8_t> m2(3, 3);
    auto m3 = m1.identity();
    auto m4 = m2.identity();

    const bool ok1 = m3[1][1] == 1;

    const bool ok2 = m4[1][1] == 1 && m4[1][2] == 0 && m4[1][3] == 0 &&
                     m4[2][1] == 0 && m4[2][2] == 1 && m4[2][3] == 0 &&
                     m4[3][1] == 0 && m4[3][2] == 0 && m4[3][3] == 1;

    bool ok3 = false;
    try { agc::matrix<int8_t>(3, 2).identity(); }
    catch (const std::domain_error& e) { ok3 = std::string(e.what()) == e_msg; }

    const bool ok = ok1 && ok2 && ok3;
    print_test_output("RunTest_Matrix_should_be_able_to_get_identity", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_symmetric()
{
    agc::matrix<int8_t> m1(3, 3, { {1, 7, 3} ,
                                   {7, 4, 5} ,
                                   {3, 5, 0} });

    agc::matrix<int8_t> m2(3, 3, { {1, 0, 0} ,
                                   {0, 1, 0} ,
                                   {0, 0, 1} });

    agc::matrix<int8_t> m3(1, 1, { {1} });

    agc::matrix<int8_t> m4(1, 1);

    agc::matrix<int8_t> m5(3, 3, { {1, 7, 3} ,
                                   {6, 4, 5} ,
                                   {3, 5, 0} });

    const bool ok1 = m1.is_symmetric();
    const bool ok2 = m2.is_symmetric();
    const bool ok3 = m3.is_symmetric();
    const bool ok4 = m4.is_symmetric();
    const bool ok5 = !m5.is_symmetric();

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_symmetric", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_skew_symmetric()
{
    agc::matrix<int8_t> m1(3, 3, { { 0, 2, -45} ,
                                   {-2, 0,  -4} ,
                                   {45, 4,   0} });

    agc::matrix<int8_t> m2(3, 3, { {1, 0, 0} ,
                                   {0, 1, 0} ,
                                   {0, 0, 1} });

    agc::matrix<int8_t> m3(1, 1, { {1} });

    agc::matrix<int8_t> m4(1, 1);

    agc::matrix<int8_t> m5(3, 3, { {1, 7, 3} ,
                                   {6, 4, 5} ,
                                   {3, 5, 0} });

    const bool ok1 = m1.is_skew_symmetric();
    const bool ok2 = !m2.is_skew_symmetric();
    const bool ok3 = !m3.is_skew_symmetric();
    const bool ok4 = m4.is_skew_symmetric();
    const bool ok5 = !m5.is_skew_symmetric();

    const bool ok = ok1 && ok2 && ok3 && ok4 && ok5;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_skew_symmetric", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_inverse()
{
    agc::matrix<double> m1(2, 2, { {3, 4} ,
                                   {1, 2} });
    agc::matrix<double> m2(2, 2, { {   1,  -2} ,
                                   {-0.5, 1.5} });

    agc::matrix<int8_t> m3(3, 3, { {1, 2, 3} ,
                                   {0, 1, 4} ,
                                   {5, 6, 0} });
    agc::matrix<int8_t> m4(3, 3, { {-24,  18,  5} ,
                                   { 20, -15, -4} ,
                                   { -5,   4,  1} });

    const bool ok1 = m1.is_inverse(m2);
    const bool ok2 = !m1.is_inverse(++m2);
    const bool ok3 = m3.is_inverse(m4);
    const bool ok4 = !m3.is_inverse(--m4);

    const bool ok = ok1 && ok2 && ok3 && ok4;
    print_test_output("RunTest_Matrix_should_be_able_to_check_if_is_inverse", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_calc_determinant()
{
    agc::matrix<double> m1(2, 2, { {3, 2} ,
                                   {1, 4} });
    const bool ok1 = m1.det() == 10.0;

    agc::matrix<int8_t> m2(3, 3, { {2, -3,  1} ,
                                   {2,  0, -1} ,
                                   {1,  4,  5} });
    const bool ok2 = m2.det() == 49.0;

    agc::matrix<int8_t> m3(3, 3, { {1, 2, 4} ,
                                   {3, 4, 2} ,
                                   {2, 2, 1} });
    const bool ok3 = m3.det() == -6.0;

    const bool ok = ok1 && ok2 && ok3;
    print_test_output("RunTest_Matrix_should_be_able_to_calc_determinant", ok);
}

// ---------------------------------------------------------------------------------

int main()
{
    RunTest_Matrix_should_be_able_to_construct();
    RunTest_Matrix_should_be_able_to_get_size();
    RunTest_Matrix_should_be_able_to_compare_sizes();
    RunTest_Matrix_should_be_able_to_check_if_is_empty();
    RunTest_Matrix_should_be_able_to_check_if_is_a_square_matrix();
    RunTest_Matrix_should_be_able_to_check_if_is_a_rect_matrix();
    RunTest_Matrix_should_be_able_to_check_if_is_a_row_matrix();
    RunTest_Matrix_should_be_able_to_check_if_is_a_col_matrix();
    RunTest_Matrix_should_be_able_to_check_if_is_null_matrix();
    RunTest_Matrix_should_be_able_to_check_if_is_triangular_upper();
    RunTest_Matrix_should_be_able_to_check_if_is_triangular_lower();
    RunTest_Matrix_should_be_able_to_check_if_is_triangular();
    RunTest_Matrix_should_be_able_to_check_if_is_diagonal();
    RunTest_Matrix_should_be_able_to_check_if_is_scalar();
    RunTest_Matrix_should_be_able_to_check_if_is_identity();
    RunTest_Matrix_should_be_able_to_transform_its_elements();
    RunTest_Matrix_should_be_able_to_access_elements_safely();
    RunTest_Matrix_should_be_able_to_assign_copy();
    RunTest_Matrix_should_be_able_to_assign_move();
    RunTest_Matrix_should_be_able_to_compare();
    RunTest_Matrix_should_be_able_to_increment();
    RunTest_Matrix_should_be_able_to_decrement();
    RunTest_Matrix_should_be_able_to_addition_assign();
    RunTest_Matrix_should_be_able_to_subtraction_assign();
    RunTest_Matrix_should_be_able_to_multiplication_assign();
    RunTest_Matrix_should_be_able_to_division_assign();
    RunTest_Matrix_should_be_able_to_times();
    RunTest_Matrix_should_be_able_to_pow();
    RunTest_Matrix_should_be_able_to_transpose();
    RunTest_Matrix_should_be_able_to_get_identity();
    RunTest_Matrix_should_be_able_to_check_if_is_symmetric();
    RunTest_Matrix_should_be_able_to_check_if_is_skew_symmetric();
    RunTest_Matrix_should_be_able_to_check_if_is_inverse();
    RunTest_Matrix_should_be_able_to_calc_determinant();

    print_tests_output();

    return 0;
}

// ---------------------------------------------------------------------------------

std::string fstr(const char* str, int code)
{ return "\x1B[" + std::to_string(code) + "m" + std::string(str) + "\033[0m"; }
std::string gstr(const char* s) { return fstr(s, AECC::FG_BRIGHT_GREEN); }
std::string rstr(const char* s) { return fstr(s, AECC::FG_BRIGHT_RED); }
std::string bstr(const char* s) { return "\x1b[1m" + std::string(s) + "\x1b[0m"; }

// ---------------------------------------------------------------------------------

void print_test_output(const char* test_name, bool ok)
{
    num_runs++;

    if (ok)
    {
        num_pass++;
        std::cout << "[x] " << test_name << " : " << gstr("PASSED") << "\n";
    }
    else
    {
        std::cout << "\x1b[1m[ ]\x1b[0m " << test_name << " : " << rstr("NOT PASSED") << "\n";
    }
}

// ---------------------------------------------------------------------------------

void print_tests_output()
{
    const char* str_suc = "ALL PASS";
    const char* str_err = "FAILED";

    const bool all_pass = num_runs == num_pass;
    std::cout << "\n-----------------------\n  num_runs : " << num_runs << "\n"
              << "  num_pass : " << num_pass << "\n"
              << "-----------------------\n  Status   : "
              << bstr(all_pass ? gstr(str_suc).c_str() : rstr(str_err).c_str())
              << "\n\n";
}

// ---------------------------------------------------------------------------------
