//
// Created by Administrator on 10/15/2020.
//
#include "Matrix.h"
#include "Sparse_Matrix.h"

#ifndef MAIN_CPP_MX_H
#define MAIN_CPP_MX_H

class Mx {
public:
    template<typename T>
    static bool can_multiply(const Matrix<T> &a, const Matrix<T> &b) {
        if (a.get_num_cols() == 0)
            return false;
        if (a.get_num_rows() == 0)
            return false;
        if (b.get_num_cols() == 0)
            return false;
        if (b.get_num_rows() == 0)
            return false;

        return a.get_num_cols() == b.get_num_rows();
    }

    template<typename T>
    static bool multiply(const Matrix<T> &a, const Matrix<T> &b, Matrix<T> &res) {
        if (!can_multiply(a, b))
            return false;


        size_t r = a.get_num_rows();
        size_t c = b.get_num_cols();

        Matrix<T> rtn(r, c);

        for (size_t curtC = 0; curtC < c; curtC++) {
            for (size_t curtR = 0; curtR < r; curtR++) {
                rtn.set(curtR, curtC, multiplyTwoVectors(get_row(a, curtR), get_col(b, curtC)));
            }
        }
        res = rtn;

        return true;
    }

//Sparse_Matrix utils

    template<typename T>
    static bool can_multiply(const Sparse_Matrix<T> &a, const Sparse_Matrix<T> &b) {
        if (a.get_num_cols() == 0)
            return false;
        if (a.get_num_rows() == 0)
            return false;
        if (b.get_num_cols() == 0)
            return false;
        if (b.get_num_rows() == 0)
            return false;

        return a.get_num_cols() == b.get_num_rows();

    }

    template<typename T>
    static bool multiply(const Sparse_Matrix<T> &a, const Sparse_Matrix<T> &b, Sparse_Matrix<T> &res) {
        if (!can_multiply(a, b))
            return false;

        size_t max_R = a.get_num_rows();
        size_t max_C = b.get_num_cols();
        res.clear();
        res = Sparse_Matrix<T>(max_R, max_C);


        for (size_t r = 0; r < max_R; r++) {
            for (size_t c = 0; c < max_C; c++) {
                for (const auto &rowNode : a._rows[r]) {
                    const T &matchingBVal = (T)b.get(rowNode.get_col(), c);
                    add_to_cell(res, r, c, rowNode.get_value() * matchingBVal);
                }
            }
        }

        return true;

    }


    template<typename T>
    static bool add_to_cell(Sparse_Matrix<T> &a, size_t &r, size_t &c, const T &old_val) {
        if (!a.is_valid(r, c))
            return false;

        //This could be a serious breach of speed;
        const T &val = a.get(r, c) + old_val;

        if(a.is_default(val)){
            for(auto it = a._rows[r].begin(); it != a._rows[r].end(); ++it) {
                if(it->get_col() == c) {
                    a._rows[r].erase(it);
                    return  true;
                }
            }

        }

        a.set(r, c, val);

        return true;
    }

    //Helper class
    template<typename T>
    static vector<T> get_row(const Matrix<T> &a, size_t rowNum) {
        return a._rows[rowNum];
    }

    template<typename T>
    static vector<T> get_row(const Sparse_Matrix<T> &a, size_t rowNum) {
        vector<T> rtn;
        for (size_t c = 0; c < a.get_num_cols(); c++) {
            rtn.push_back(a.get(rowNum, c));
        }

        return rtn;
    }

    template<typename T>
    static vector<T> get_col(const Matrix<T> &a, size_t colNum) {
        vector<T> rtn;
        for (size_t r = 0; r < a.get_num_rows(); r++) {
            rtn.push_back(a._rows[r][colNum]);
        }
        return rtn;
    }

    template<typename T>
    static vector<T> get_col(const Sparse_Matrix<T> &a, size_t colNum) {
        vector<T> rtn;
        for (size_t r = 0; r < a.get_num_rows(); r++) {
            rtn.push_back(a.get(r, colNum));
        }
        return rtn;
    }


    template<typename T>
    static T multiplyTwoVectors(vector<T> v1, vector<T> v2) {
        T answer = 0;

        for (size_t i = 0; i < v1.size(); i++) {
            answer += (v1[i] * v2[i]);
        }
        return answer;
    }

    template<typename T1, typename T2>
    static T2 multiplyTwoVectors2(const T1 &v1, const vector<T2> &v2) {
        T2 answer = 0;

        for (auto x : v1) {
            answer += x.get_value() * v2[x.get_col()];
        }

        //answer += (v1[i].get_value() * v2[v1[i].get_col()]);

        return answer;
    }

    template<typename T>
    static void setRandom(Matrix<T> &m) {
        size_t max_C = m.get_num_cols();
        size_t max_R = m.get_num_rows();
        for (size_t c = 0; c < max_C; c++) {
            for (size_t r = 0; r < max_R; r++) {
                m.set(r, c, (rand() % 10));
            }
        }

    }

    template<typename T>
    static void setRandom(Sparse_Matrix<T> &m, string comd) {
        size_t max_C = m.get_num_cols();
        size_t max_R = m.get_num_rows();
        for (size_t c = 0; c < max_C; c++) {
            for (size_t r = 0; r < max_R; r++) {
                int randomInt(rand() % 10);
                if(comd.compare("zero") == 0) {
                    m.set(r, c, 0);
                }else {
                    m.set(r, c, rand() % 10 - 5);
                }
            }
        }

    }

};


#endif //MAIN_CPP_MX_H
