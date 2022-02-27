/*
MIT LICENSE
Copyright 2022 Tiago Melo Juca

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in the
Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// ---------------------------------------------------------------------------------

#ifndef AGC_HPP_
#define AGC_HPP_

#include <algorithm>
#include <functional>
#include <vector>

// ---------------------------------------------------------------------------------

namespace agc
{
    template <typename T>
    class matrix;

    template <typename T>
    class vector;

    template <typename T>
    class solver;
}

// ---------------------------------------------------------------------------------

template <typename T>
class agc::matrix
{
public:
    class matrix_row
    {
    public:
        matrix_row() = delete;
        matrix_row& operator=(const matrix_row&) = delete;

        matrix_row(const matrix_row& other)
        {
            const std::vector<T>& src = other.row;
            std::copy(src.begin(), src.end(), std::back_inserter(row));
        }
        matrix_row(matrix_row&& other)
        {
            row = std::move(other.row);
        }
        explicit matrix_row(const std::vector<T>& _row)
        {
            row = std::move(_row);
        }

        T& operator[](int idx)
        {
            if (idx < 1 || idx > row.size())
            {
                throw std::out_of_range("matrix column access out of boundary");
            }

            return row[idx - 1];
        }
        const T& operator[](int idx) const
        {
            if (idx < 1 || idx > row.size())
            {
                throw std::out_of_range("matrix column access out of boundary");
            }

            return row[idx - 1];
        }

    private:
        std::vector<T> row;
    };

    matrix() = delete;
    matrix(const matrix& other) : rows(other.rows), cols(other.cols)
    {
        for (auto&& row : other.mtx)
        {
            mtx.push_back(matrix_row(row));
        }
    }
    matrix(matrix&& other) : rows(other.rows), cols(other.cols)
    {
        for (int i = 0; i < rows; i++)
        {
            mtx.push_back(std::move(other.mtx[i]));
        }

        other.rows = 0;
        other.cols = 0;
    }
    explicit matrix(int _r, int _c)
        : rows(_r), cols(_c)
    {
        if (rows < 0 || cols < 0)
        {
            throw std::invalid_argument("matrix size cannot be negative");
        }

        for (int i = 0; i < rows; i++)
        {
            std::vector<T> row;
            for (int j = 0; j < cols; j++)
            {
                row.push_back(0);
            }

            mtx.push_back(matrix_row(row));
        }
    }
    explicit matrix(int _r, int _c, const std::vector<std::vector<T>>& _elems)
        : rows(_r), cols(_c)
    {
        if (rows < 0 || cols < 0)
        {
            throw std::invalid_argument("matrix size cannot be negative");
        }

        const size_t target_rows = _elems.size();
        for (int i = 0; i < rows; i++)
        {
            std::vector<T> row;

            if (i < target_rows)
            {
                const size_t target_cols = _elems[i].size();
                for (int j = 0; j < cols; j++)
                {
                    row.push_back(j < target_cols ? _elems[i][j] : 0);
                }
            }
            else
            {
                for (int j = 0; j < cols; j++)
                {
                    row.push_back(0);
                }
            }
            
            mtx.push_back(matrix_row(row));
        }
    }

    int size_rows() const
    {
        return rows;
    }
    int size_cols() const
    {
        return cols;
    }
    bool is_same_size(const matrix& other) const
    {
        return rows == other.rows && cols == other.cols;
    }
    bool is_empty() const
    {
        return rows == 0 || cols == 0;
    }
    bool is_square_matrix() const
    {
        return !is_empty() && rows == cols;
    }
    bool is_rectangular_matrix() const
    {
        return !is_empty() && !is_square_matrix();
    }
    bool is_row_matrix() const
    {
        return is_rectangular_matrix() && rows == 1;
    }
    bool is_column_matrix() const
    {
        return is_rectangular_matrix() && cols == 1;
    }
    bool is_null_matrix() const
    {
        if (is_empty())
        {
            return false;
        }

        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= cols; j++)
            {
                if ((*this)[i][j] != 0)
                {
                    return false;
                }
            }
        }

        return true;
    }
    bool is_triangular_upper_matrix() const
    {
        if (!is_square_matrix())
        {
            return false;
        }

        for (int i = 1; i < rows; i++)
        {
            for (int j = i + 1; j <= cols; j++)
            {
                if ((*this)[i][j] != 0)
                {
                    return false;
                }
            }
        }

        return true;
    }
    bool is_triangular_lower_matrix() const
    {
        if (!is_square_matrix())
        {
            return false;
        }

        for (int i = 2; i <= rows; i++)
        {
            for (int j = 1; j <= i - 1; j++)
            {
                if ((*this)[i][j] != 0)
                {
                    return false;
                }
            }
        }

        return true;
    }
    bool is_triangular_matrix() const
    {
        return is_triangular_upper_matrix() || is_triangular_lower_matrix();
    }
    bool is_diagonal_matrix() const
    {
        return is_triangular_upper_matrix() && is_triangular_lower_matrix();
    }
    bool is_scalar_matrix() const
    {
        T a11 = (*this)[1][1];
        if (a11 == 0)
        {
            return false;
        }

        if (!is_diagonal_matrix())
        {
            return false;
        }

        const int diagonal_size = rows;
        for(int i = 2; i <= diagonal_size; i++)
        {
            if ((*this)[i][i] != a11)
            {
                return false;
            }
        }

        return true;
    }
    bool is_identity_matrix() const
    {
        return (*this)[1][1] == 1 && is_scalar_matrix();
    }

    void transform(int row_begin, int row_end, int col_begin, int col_end,
                   std::function<T(T)> unary_op)
    {
        for (int i = row_begin; i <= row_end; i++)
        {
            for (int j = col_begin; j <= col_end; j++)
            {
                T old_value = (*this)[i][j];
                (*this)[i][j] = unary_op(old_value);
            }
        }
    }
    void transform(int row_begin, int row_end, int col_begin, int col_end,
                   const matrix& other, std::function<T(T, T)> binary_op)
    {
        if (!is_same_size(other))
        {
            throw std::domain_error("matrix transform must have same size");
        }

        for (int i = row_begin; i <= row_end; i++)
        {
            for (int j = col_begin; j <= col_end; j++)
            {
                T old_value = (*this)[i][j];
                (*this)[i][j] = binary_op(old_value, other[i][j]);
            }
        }
    }
    void transform(std::function<T(T)> unary_op)
    {
        transform(1, rows, 1, cols, unary_op);
    }
    void transform(const matrix& other, std::function<T(T, T)> binary_op)
    {
        transform(1, rows, 1, cols, other, binary_op);
    }
    void fill_with(T val)
    {
        transform([&val](T) -> T { return val; });
    }

    matrix_row& operator[](int idx)
    {
        if (idx < 1 || idx > rows)
        {
            throw std::out_of_range("matrix row access out of boundary");
        }

        return mtx[idx - 1];
    };
    const matrix_row& operator[](int idx) const
    {
        if (idx < 1 || idx > rows)
        {
            throw std::out_of_range("matrix row access out of boundary");
        }

        return mtx[idx - 1];
    };
    matrix& operator=(const matrix& other)
    {
        if (this != &other)
        {
            mtx.clear();
            rows = other.rows;
            cols = other.cols;
            for (auto&& row : other.mtx)
            {
                mtx.push_back(matrix_row(row));
            }
        }

        return *this;
    }
    matrix& operator=(matrix&& other)
    {
        if (this != &other)
        {
            mtx.clear();
            rows = other.rows;
            cols = other.cols;
            for (int i = 0; i < rows; i++)
            {
                mtx.push_back(std::move(other.mtx[i]));
            }
            other.rows = 0;
            other.cols = 0;
        }

        return *this;
    }
    bool operator==(const matrix& other) const
    {
        if (!is_same_size(other)) {
            return false;
        }

        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= cols; j++)
            {
                if ((*this)[i][j] != other[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    }
    bool operator!=(const matrix& other) const
    {
        return !operator==(other);
    }
    bool operator< (const matrix& other) const = delete;
    bool operator> (const matrix& other) const = delete;
    bool operator<=(const matrix& other) const = delete;
    bool operator>=(const matrix& other) const = delete;
    matrix& operator++()
    {
        transform([](T a_ij) -> T { return ++a_ij; });
        return *this;
    }
    matrix operator++(int)
    {
        matrix tmp(*this);
        operator++();
        return tmp;
    }
    matrix& operator--()
    {
        transform([](T a_ij) -> T { return --a_ij; });
        return *this;
    }
    matrix operator--(int)
    {
        matrix tmp(*this);
        operator--();
        return tmp;
    }
    matrix& operator+=(const matrix& other)
    {
        if (!is_same_size(other))
        {
            throw std::domain_error("matrix addition must have same size");
        }

        transform(other, [](T a_ij, T b_ij) -> T { return a_ij + b_ij; });

        return *this;
    }
    matrix& operator-=(const matrix& other)
    {
        if (!is_same_size(other))
        {
            throw std::domain_error("matrix subtraction must have same size");
        }

        transform(other, [](T a_ij, T b_ij) -> T { return a_ij - b_ij; });

        return *this;
    }
    matrix& operator*=(T value)
    {
        transform([&value](T a_ij) -> T { return value * a_ij; });
        return *this;
    }
    matrix& operator/=(T value)
    {
        if (value == 0) {
            throw std::domain_error("matrix divison by zero is not allowed");
        }

        transform([&value](T a_ij) -> T { return a_ij / value; });
        return *this;
    }
    matrix& operator*=(const matrix& other)
    {
        if (cols != other.rows)
        {
            throw std::domain_error(
                "matrix multiplication requires numColumns(A) == numRows(B)"
            );
        }

        matrix<T> P(rows, other.cols);
        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= other.cols; j++)
            {
                for (int k = 1; k <= cols; k++) {
                    P[i][j] += (*this)[i][k] * other[k][j];
                }
            }
        }
        *this = P;

        return *this;
    }
    matrix times(const matrix& other) const
    {
        if (!is_same_size(other))
        {
            throw std::domain_error("matrix times must have same size");
        }

        matrix<T> P(rows, cols);
        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= cols; j++)
            {
                P[i][j] = (*this)[i][j] * other[i][j];
            }
        }

        return P;
    }
    matrix pow(int n) const
    {
        if (!is_square_matrix())
        {
            throw std::domain_error("matrix pow requires a square matrix");
        }
        if (n < 1)
        {
            throw std::domain_error("matrix pow requires n >= 1");
        }

        matrix<T> P(*this);
        for (int i = 1; i < n; i++)
        {
            P *= *this;
        }

        return P;
    }
    matrix transpose() const
    {
        matrix<T> aT(cols, rows);

        for (int i = 1; i <= rows; i++)
        {
            for (int j = 1; j <= cols; j++)
            {
                aT[j][i] = (*this)[i][j];
            }
        }

        return aT;
    }
    matrix identity() const
    {
        matrix<T> I(rows, cols);
        
        const int diagonal_size = rows;
        for (int i = 1; i <= diagonal_size; i++)
        {
            I[i][i] = 1;
        }

        return I;
    }
    bool is_symmetric() const
    {
        if (!is_square_matrix())
        {
            return false;
        }

        const matrix<T> aT = this->transpose();

        return (*this) == aT;
    }
    bool is_inverse(const matrix& other)
    {
        return (*this) * other == this->identity();
    }

private:
    std::vector<matrix_row> mtx;
    int rows;
    int cols;
};

// ---------------------------------------------------------------------------------

namespace agc
{
    template <typename T>
    inline matrix<T> operator+(matrix<T> lhs, const matrix<T>& rhs)
    {
        lhs += rhs;
        return lhs;
    }
    template <typename T>
    inline matrix<T> operator-(matrix<T> lhs, const matrix<T>& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    template <typename T>
    inline matrix<T> operator*(matrix<T> lhs, T rhs)
    {
        lhs *= rhs;
        return lhs;
    }
    template <typename T>
    inline matrix<T> operator*(T rhs, matrix<T> lhs)
    {
        lhs *= rhs;
        return lhs;
    }
    template <typename T>
    inline matrix<T> operator/(matrix<T> lhs, T rhs)
    {
        lhs /= rhs;
        return lhs;
    }
    template <typename T>
    inline matrix<T> operator*(matrix<T> lhs, const matrix<T>& rhs)
    {
        lhs *= rhs;
        return lhs;
    }
}

// ---------------------------------------------------------------------------------

template <typename T>
class agc::vector
{
public:
    vector() = delete;
    vector(const vector& other) : vec_size(other.vec_size)
    {
        for (auto&& val : other.vec)
        {
            vec.push_back(val);
        }
    }
    vector(vector&& other) : vec_size(other.vec_size)
    {
        vec = std::move(other.vec);
    }
    vector& operator=(const vector& other)
    {
        if (this != &other)
        {
            vec.clear();
            vec_size = other.vec_size;
            std::copy(other.vec.begin(), other.vec.end(), std::back_inserter(vec));
        }

        return *this;
    }
    vector& operator=(vector&& other)
    {
        if (this != &other)
        {
            vec.clear();
            vec_size = other.vec_size;
            vec = std::move(other.vec);
            other.vec_size = 0;
        }

        return *this;
    }
    explicit vector(int _size) : vec_size(_size)
    {
        if (vec_size < 0)
        {
            throw std::invalid_argument("vector size cannot be negative");
        }

        for (int i = 0; i < vec_size; i++)
        {
            vec.push_back(0);
        }
    }
    explicit vector(int _size, const std::vector<T>& _elements) : vec_size(_size)
    {
        if (vec_size < 0)
        {
            throw std::invalid_argument("vector size cannot be negative");
        }

        const size_t target_size = _elements.size();
        for (int i = 0; i < vec_size; i++)
        {
            vec.push_back(i < target_size ? _elements[i] : 0);
        }
    }

    T& operator[](int idx)
    {
        if (idx < 1 || idx > vec_size)
        {
            throw std::out_of_range("vector access out of boundary");
        }

        return vec[idx - 1];
    };
    const T& operator[](int idx) const
    {
        if (idx < 1 || idx > vec_size)
        {
            throw std::out_of_range("vector access out of boundary");
        }

        return vec[idx - 1];
    };

    int size() const
    {
        return vec_size;
    }
    bool is_same_size(const vector& other) const
    {
        return vec_size == other.vec_size;
    }
    bool is_empty() const
    {
        return vec_size == 0;
    }
    bool is_null_vector() const
    {
        return !std::any_of(vec.begin(), vec.end(), [](T it) { return it != 0; });
    }

private:
    std::vector<T> vec;
    int vec_size;
};

// ---------------------------------------------------------------------------------

template <typename T>
class agc::solver
{
public:
    solver() = delete;
    solver(const solver&) = delete;
    solver(solver&&) = delete;
    solver& operator=(const solver&) = delete;
    explicit solver(const matrix<T>& sysmtx) : sysmtx(sysmtx) {};

    explicit solver(int _r, int _c, const std::vector<std::vector<T>>& _elems)
        : sysmtx(_r, _c, _elems)
    {};

    matrix<T> gauss() const
    {
        if (sysmtx.size_cols() != sysmtx.size_rows() + 1)
        {
            throw std::domain_error("invalid augmented matrix");
        }

        matrix<T> G(sysmtx);

        const int size_eqsys = sysmtx.size_rows();
        for (int i = 1; i <= size_eqsys - 1; i++)
        {
            T aii = G[i][i];
            if (aii == 0)
            {
                throw std::domain_error(
                    "reached a division by zero in augmented matrix"
                );
            }

            for (int j = i + 1; j <= size_eqsys; j++)
            {
                T ratio = G[j][i] / aii;
                for (int k = 1; k <= size_eqsys + 1; k++)
                {
                    G[j][k] -= ratio * G[i][k];
                }
            }
        }

        return G;
    }
    
    matrix<T> solve() const
    {
        matrix<T> G = gauss();
        const int rows = sysmtx.size_rows();
        const int cols = sysmtx.size_cols();

        matrix<T> V(rows, 1);
        V[rows][1] = G[rows][cols] / G[rows][rows];
        for (int i = rows - 1; i >= 1; i--)
        {
            V[i][1] = G[i][cols];
            for (int j = i + 1; j <= rows; j++)
            {
                V[i][1] -= G[i][j] * V[j][1];
            }
            V[i][1] /= G[i][i];
        }

        return V;
    }

private:
    const matrix<T> sysmtx;
};

// ---------------------------------------------------------------------------------

#endif
