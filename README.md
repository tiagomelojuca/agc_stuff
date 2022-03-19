# agc_stuff
Just some work for college (Linear Algebra course)</br></br>

### TODO:

1) Impl following:
- [ ] Determinant calc
- [ ] Gauss-Jordan solver

2) Tests for throwing at:
- [ ] `explicit matrix(int _r, int _c);`
- [ ] `explicit matrix(int _r, int _c, const std::vector<std::vector<T>>& _elems);`
- [ ] `explicit vector(int _size) : vec_size(_size);`
- [ ] `explicit vector(int _size, const std::vector<T>& _elements) : vec_size(_size);`
- [ ] `void transform(int idx_begin, int idx_end, const vector& other, std::function<T(T, T)> binary_op);`
- [ ] `T& operator[](int idx);`
- [ ] `const T& operator[](int idx) const;`
- [ ] `vector& operator+=(const vector& other);`
- [ ] `vector& operator-=(const vector& other);`
- [ ] `vector& operator/=(T value);`
- [ ] `vector times(const vector& other) const;`
- [ ] `matrix<double> gauss() const;`
- [ ] `void swap_row(matrix<double>& m, int r1, int r2) const;`
- [ ] `int get_higher_column(const std::vector<std::vector<double>>& mtx) const;`

3) Review potential precision problems due to IEE-754 at:
- [ ] matrix::is_null_matrix
- [ ] matrix::is_triangular_lower_matrix
- [ ] matrix::is_triangular_upper_matrix
- [ ] matrix::is_scalar_matrix
- [ ] matrix::is_identity_matrix
- [ ] matrix::operator== && matrix::operator!=

4) Review potential precision problems due to hard coded values at:
- [ ] matrix::identity (?)
- [ ] matrix::is_skew_symmetric (?)
