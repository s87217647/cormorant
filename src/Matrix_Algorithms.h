//
// Created by Administrator on 10/15/2020.
//
#include "Matrix.h"
#include "Sparse_Matrix.h"

#ifndef MAIN_CPP_MX_H
#define MAIN_CPP_MX_H

class Mx{
public:
    template<typename T>
    static bool can_multiply(const Matrix<T> &a, const Matrix<T> &b) {
        return a.get_num_cols() == b.get_num_rows();
    }

    template<typename T>
    static bool multiply(const Matrix<T> &a, const Matrix<T> &b) {
        if(! can_multiply(a,b))
            return  false;

        Matrix<T> rtn(a.get_num_rows(),b.get_num_cols());

        return true;
    }
    template<typename T>
    static bool multiply(const Matrix<T> &a, const Matrix<T> &b, const Matrix<T> &c) {
        return true;
    }

//Sparse_Matrix utils

    template<typename T>
    static bool can_multiply(const Sparse_Matrix<T> &a, const  Sparse_Matrix<T> &b) {
        return a.get_num_cols() == b.get_num_rows();
    }

    template<typename T>
    static bool multiply(const Sparse_Matrix<T> &a, const  Sparse_Matrix<T> &b,const  Sparse_Matrix<T> &c) {
        return true;
    }

    template<typename T>
    static bool multiply(const Sparse_Matrix<T> &a, const  Sparse_Matrix<T> &b) {
        return true;
    }

    template<typename T>
    static bool add_to_cell(Sparse_Matrix<T> &a, size_t &r, size_t &c, const T &old_val) {
        return true;
    }

    //Helper class


};


#endif //MAIN_CPP_MX_H
