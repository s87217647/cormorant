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
        if(a.get_num_cols() == 0)
            return false;
        if(a.get_num_rows() == 0)
            return false;
        if(b.get_num_cols() == 0)
            return false;
        if(b.get_num_rows() == 0)
            return false;

        return a.get_num_cols() == b.get_num_rows();
    }

    template<typename T>
    static bool multiply(const Matrix<T> &a, const Matrix<T> &b, Matrix<T> &res) {
        if(!can_multiply(a,b))
            return false;



        size_t r = a.get_num_rows();
        size_t c = b.get_num_cols();

        Matrix<T> rtn(r,c);

        for( size_t curtC = 0; curtC < c; curtC ++){
            for( size_t curtR = 0; curtR < r; curtR ++){
                rtn.set(curtR,curtC, multiplyTwoVectors(get_row(a,curtR),get_col(b,curtC)));
            }
        }
        res = rtn;

        return true;
    }

//Sparse_Matrix utils

    template<typename T>
    static bool can_multiply(const Sparse_Matrix<T> &a, const  Sparse_Matrix<T> &b) {
        if(a.get_num_cols() == 0)
            return false;
        if(a.get_num_rows() == 0)
            return false;
        if(b.get_num_cols() == 0)
            return false;
        if(b.get_num_rows() == 0)
            return false;

        return a.get_num_cols() == b.get_num_rows();

    }

    template<typename T>
    static bool multiply(const Sparse_Matrix<T> &a, const  Sparse_Matrix<T> &b,Sparse_Matrix<T> & res) {
        if(! can_multiply(a,b))
            return  false;

        size_t r = a.get_num_rows();
        size_t c = b.get_num_cols();

        Sparse_Matrix<T> rtn(r, c, 0);

        for( size_t curtC = 0; curtC < c; curtC ++){
            for( size_t curtR = 0; curtR < r; curtR ++){
                T x = multiplyTwoVectors(get_row(a,curtR),get_col(b,curtC));
                rtn.set(curtR,curtC, x);
            }
        }

        res = rtn;

        return true;
    }



    template<typename T>
    static bool add_to_cell(Sparse_Matrix<T> &a, size_t &r, size_t &c, const T &old_val) {
        if(!a.is_valid(r,c))
            return false;

        const T &val = a.get(r, c) + old_val;
        a.set(r, c, val);
        return true;
    }

    //Helper class
    template<typename T>
    static vector<T> get_row(const Matrix<T> &a , size_t rowNum){
        return a._rows[rowNum];
    }

    template<typename T>
    static vector<T> get_row(const Sparse_Matrix<T> &a, size_t rowNum){
        vector<T> rtn;
        for(size_t c = 0; c < a.get_num_cols(); c ++){
            rtn.push_back(a.get(rowNum,c));
        }

        return rtn;
    }

    template<typename T>
    static vector<T> get_col(const Matrix<T> &a, size_t colNum){
        vector<T> rtn;
        for(size_t r = 0;r < a.get_num_rows();r++ ){
            rtn.push_back(a._rows[r][colNum]);
        }
        return rtn;
    }

    template<typename T>
    static vector<T> get_col(const Sparse_Matrix<T> &a, size_t colNum){
        vector<T> rtn;
        for(size_t r = 0;r < a.get_num_rows();r++ ){
            rtn.push_back(a.get(r, colNum));
        }
        return rtn;
    }

    template<typename T>
    static T multiplyTwoVectors(vector<T> v1, vector<T> v2){
        T answer = 0;

        for(size_t i = 0; i < v1.size(); i++){
            answer +=  (v1[i] * v2[i]);
        }

        return  answer;
    }

    template <typename T>
    static void setRandom(Matrix<T>& m) {
        size_t max_C = m.get_num_cols();
        size_t max_R = m.get_num_rows();
        for (size_t c = 0; c < max_C; c++) {
            for (size_t r = 0; r < max_R; r++) {
                m.set(r,c,(rand()%10));
            }
        }

    }

    template <typename T>
    static void setRandom(Sparse_Matrix<T>& m) {
        size_t max_C = m.get_num_cols();
        size_t max_R = m.get_num_rows();
        for (size_t c = 0; c < max_C; c++) {
            for (size_t r = 0; r < max_R; r++) {
                m.set(r,c,(rand()%10));
            }
        }

    }

};


#endif //MAIN_CPP_MX_H
