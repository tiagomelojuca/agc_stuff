#include <iostream>
#include <stdint.h>
#include <string>

#include "aecc.h"
#include "agc.hpp"

// ---------------------------------------------------------------------------------

int num_runs = 0;
int num_pass = 0;
void print_test_output(const char*, bool);
void print_tests_output();

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_get_size()
{
    agc::matrix<uint8_t> m(3, 7);
    const bool ok1 = m.size_rows() == 3;
    const bool ok2 = m.size_cols() == 7;

    const bool ok = ok1 && ok2;
    print_test_output("RunTest_Matrix_should_be_able_to_get_size", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_compare_sizes()
{
    agc::matrix<uint8_t> m1(3, 7);
    agc::matrix<uint8_t> m2(3, 7);
    agc::matrix<uint8_t> m3(7, 3);

    const bool ok1 = m1.is_same_size(m2);
    const bool ok2 = !m1.is_same_size(m3);

    const bool ok = ok1 && ok2;
    print_test_output("RunTest_Matrix_should_be_able_to_compare_sizes", ok);
}

// ---------------------------------------------------------------------------------

void RunTest_Matrix_should_be_able_to_check_if_is_empty()
{
    agc::matrix<uint8_t> m1(0, 0);
    agc::matrix<uint8_t> m2(0, 1);
    agc::matrix<uint8_t> m3(1, 0);
    agc::matrix<uint8_t> m4(1, 1);

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
    agc::matrix<uint8_t> m1(0, 0);
    agc::matrix<uint8_t> m2(0, 1);
    agc::matrix<uint8_t> m3(1, 0);
    agc::matrix<uint8_t> m4(1, 1);
    agc::matrix<uint8_t> m5(2, 2);
    agc::matrix<uint8_t> m6(1, 2);
    agc::matrix<uint8_t> m7(2, 1);

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
    agc::matrix<uint8_t> m1(0, 0);
    agc::matrix<uint8_t> m2(0, 1);
    agc::matrix<uint8_t> m3(1, 0);
    agc::matrix<uint8_t> m4(1, 1);
    agc::matrix<uint8_t> m5(2, 2);
    agc::matrix<uint8_t> m6(1, 2);
    agc::matrix<uint8_t> m7(2, 1);

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
    agc::matrix<uint8_t> m1(0, 0);
    agc::matrix<uint8_t> m2(0, 1);
    agc::matrix<uint8_t> m3(1, 0);
    agc::matrix<uint8_t> m4(1, 1);
    agc::matrix<uint8_t> m5(2, 2);
    agc::matrix<uint8_t> m6(1, 2);
    agc::matrix<uint8_t> m7(2, 1);

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
    agc::matrix<uint8_t> m1(0, 0);
    agc::matrix<uint8_t> m2(0, 1);
    agc::matrix<uint8_t> m3(1, 0);
    agc::matrix<uint8_t> m4(1, 1);
    agc::matrix<uint8_t> m5(2, 2);
    agc::matrix<uint8_t> m6(1, 2);
    agc::matrix<uint8_t> m7(2, 1);

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
    agc::matrix<uint8_t> m1(3, 3);
    agc::matrix<uint8_t> m2(5, 5);
    agc::matrix<uint8_t> m3(5, 5);
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
    agc::matrix<uint8_t> m01(3, 3, { {0, 0, 0} ,
                                     {0, 0, 0} ,
                                     {0, 0, 0} });

    agc::matrix<uint8_t> m02(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m03(3, 3, { {1, 2, 3} ,
                                     {0, 5, 6} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m04(3, 3, { {1, 0, 3} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m05(3, 3, { {1, 0, 0} ,
                                     {0, 5, 6} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m06(3, 3, { {1, 2, 0} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m07(3, 3, { {1, 0, 0} ,
                                     {4, 5, 0} ,
                                     {7, 8, 9} });

    agc::matrix<uint8_t> m08(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {7, 0, 9} });

    agc::matrix<uint8_t> m09(3, 3, { {1, 0, 0} ,
                                     {4, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m10(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {0, 8, 9} });

    agc::matrix<uint8_t> m11(3, 3, { {1, 2, 3} ,
                                     {4, 5, 6} ,
                                     {7, 8, 9} });

    agc::matrix<uint8_t> m12(1, 1, { {1} });

    agc::matrix<uint8_t> m13(1, 2);

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
    agc::matrix<uint8_t> m01(3, 3, { {0, 0, 0} ,
                                     {0, 0, 0} ,
                                     {0, 0, 0} });

    agc::matrix<uint8_t> m02(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m03(3, 3, { {1, 2, 3} ,
                                     {0, 5, 6} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m04(3, 3, { {1, 0, 3} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m05(3, 3, { {1, 0, 0} ,
                                     {0, 5, 6} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m06(3, 3, { {1, 2, 0} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m07(3, 3, { {1, 0, 0} ,
                                     {4, 5, 0} ,
                                     {7, 8, 9} });

    agc::matrix<uint8_t> m08(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {7, 0, 9} });

    agc::matrix<uint8_t> m09(3, 3, { {1, 0, 0} ,
                                     {4, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m10(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {0, 8, 9} });

    agc::matrix<uint8_t> m11(3, 3, { {1, 2, 3} ,
                                     {4, 5, 6} ,
                                     {7, 8, 9} });

    agc::matrix<uint8_t> m12(1, 1, { {1} });

    agc::matrix<uint8_t> m13(1, 2);

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
    agc::matrix<uint8_t> m01(3, 3, { {0, 0, 0} ,
                                     {0, 0, 0} ,
                                     {0, 0, 0} });

    agc::matrix<uint8_t> m02(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m03(3, 3, { {1, 2, 3} ,
                                     {0, 5, 6} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m04(3, 3, { {1, 0, 3} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m05(3, 3, { {1, 0, 0} ,
                                     {0, 5, 6} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m06(3, 3, { {1, 2, 0} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m07(3, 3, { {1, 0, 0} ,
                                     {4, 5, 0} ,
                                     {7, 8, 9} });

    agc::matrix<uint8_t> m08(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {7, 0, 9} });

    agc::matrix<uint8_t> m09(3, 3, { {1, 0, 0} ,
                                     {4, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m10(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {0, 8, 9} });

    agc::matrix<uint8_t> m11(3, 3, { {1, 2, 3} ,
                                     {4, 5, 6} ,
                                     {7, 8, 9} });

    agc::matrix<uint8_t> m12(1, 1, { {1} });

    agc::matrix<uint8_t> m13(1, 2);

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
    agc::matrix<uint8_t> m01(3, 3, { {0, 0, 0} ,
                                     {0, 0, 0} ,
                                     {0, 0, 0} });

    agc::matrix<uint8_t> m02(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m03(3, 3, { {1, 2, 3} ,
                                     {0, 5, 6} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m04(3, 3, { {1, 0, 3} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m05(3, 3, { {1, 0, 0} ,
                                     {0, 5, 6} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m06(3, 3, { {1, 2, 0} ,
                                     {0, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m07(3, 3, { {1, 0, 0} ,
                                     {4, 5, 0} ,
                                     {7, 8, 9} });

    agc::matrix<uint8_t> m08(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {7, 0, 9} });

    agc::matrix<uint8_t> m09(3, 3, { {1, 0, 0} ,
                                     {4, 5, 0} ,
                                     {0, 0, 9} });

    agc::matrix<uint8_t> m10(3, 3, { {1, 0, 0} ,
                                     {0, 5, 0} ,
                                     {0, 8, 9} });

    agc::matrix<uint8_t> m11(3, 3, { {1, 2, 3} ,
                                     {4, 5, 6} ,
                                     {7, 8, 9} });

    agc::matrix<uint8_t> m12(1, 1, { {1} });

    agc::matrix<uint8_t> m13(1, 2);

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
    agc::matrix<uint8_t> m1(3, 3, { {0, 0, 0} ,
                                    {0, 0, 0} ,
                                    {0, 0, 0} });

    agc::matrix<uint8_t> m2(3, 3, { {1, 0, 0} ,
                                    {0, 1, 0} ,
                                    {0, 0, 1} });

    agc::matrix<uint8_t> m3(3, 3, { {3, 0, 0} ,
                                    {0, 3, 0} ,
                                    {0, 0, 3} });

    agc::matrix<uint8_t> m4(3, 3, { {3, 0, 0} ,
                                    {0, 3, 0} ,
                                    {3, 0, 3} });

    agc::matrix<uint8_t> m5(3, 3, { {3, 0, 3} ,
                                    {0, 3, 0} ,
                                    {0, 0, 3} });

    agc::matrix<uint8_t> m6(1, 1, { {1} });

    agc::matrix<uint8_t> m7(1, 2);

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
    agc::matrix<uint8_t> m1(3, 3, { {0, 0, 0} ,
                                    {0, 0, 0} ,
                                    {0, 0, 0} });

    agc::matrix<uint8_t> m2(3, 3, { {1, 0, 0} ,
                                    {0, 1, 0} ,
                                    {0, 0, 1} });

    agc::matrix<uint8_t> m3(3, 3, { {3, 0, 0} ,
                                    {0, 3, 0} ,
                                    {0, 0, 3} });

    agc::matrix<uint8_t> m4(3, 3, { {3, 0, 0} ,
                                    {0, 3, 0} ,
                                    {3, 0, 3} });

    agc::matrix<uint8_t> m5(3, 3, { {3, 0, 3} ,
                                    {0, 3, 0} ,
                                    {0, 0, 3} });

    agc::matrix<uint8_t> m6(1, 1, { {1} });

    agc::matrix<uint8_t> m7(1, 2);

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

int main()
{
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
