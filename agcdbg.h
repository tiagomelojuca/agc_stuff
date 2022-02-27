#ifndef AGCDBG_H_
#define AGCDBG_H_

#define print_boolean(_method) #_method << " ? " << (_method ? "true" : "false")

#define print_vector(_vname) std::cout << #_vname << " = " << std::endl;           \
                             for(int i = 1; i <= _vname.size(); i++)               \
                             { std::cout << "    " << _vname[i] << std::endl; }

#define print_matrix(_mname) std::cout << #_mname << " = " << std::endl;           \
                             for (int i = 1; i <= _mname.size_rows(); i++)         \
                             { std::cout << "    ";                                \
                               for (int j = 1; j <= _mname.size_cols(); j++)       \
                               { std::cout << _mname[i][j] << " "; }               \
                               std::cout << std::endl; }

#endif
