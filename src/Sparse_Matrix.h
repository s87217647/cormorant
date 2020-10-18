//Student ID: 20384891

// Created by Administrator on 10/11/2020.
//

#ifndef STILT_SPARSE_MATRIX_H
#define STILT_SPARSE_MATRIX_H

#include <vector>
#include <list>
#include "Matrix.h"

using namespace std;



template <typename T>
class Sparse_Matrix {
public:
    struct Node {
        size_t _col;
        T _val;

        Node(size_t c = 0, T v = T()) : _col(c), _val(v) {}

        size_t get_col() const { return _col; }

        const T get_value() const { return _val; }

        void set_value(const T &val) { _val = val; }

        virtual const T &operator=(const T &val) { return _val = val; }

        friend ostream &operator<<(ostream &os, const Node &node) {
            return os << "{C: " << node.get_col() << ", V: " << node.get_value() << " }";
        }

    };

    typedef Node _Node;

    vector<list<Node>> _rows;
    size_t _num_rows, _num_cols;
    T _default_val;

    //How to deal with nodes is the key here.
public:
    Sparse_Matrix(size_t nr = 0, size_t nc = 0, const T &default_val = T()) :
            _num_rows(nr), _num_cols(nc), _default_val(default_val) {
        for (size_t i = 0; i < _num_rows; i++) {
            _rows.push_back(list<Node>(0));
        }
    }

    Sparse_Matrix(Sparse_Matrix<T> const &original) {
        *this = original;
    }

    size_t get_num_rows() const { return _num_rows; }

    size_t get_num_cols() const { return _num_cols; }

    T get_default_Val() const { return _default_val; }


    class OOB_exception : public exception {
    public:
        string what() { return "Out of bounds access"; }
    };

    bool is_valid(size_t r, size_t c) const {
        if (r < 0 || c < 0)
            return false;

        if (r >= get_num_rows() || c >= get_num_cols())
            return false;

        return true;

    };

    void clear() {
        _rows = vector<list<Node>>(get_num_rows());
        _num_cols = 0;
    };

    const T get(size_t r, size_t c) const {
        if (!is_valid(r, c)) {
            throw OOB_exception();
        }

        list<Node> theRow = _rows[r];
        for (Node x : theRow) {
            if (x.get_col() == c)
                return x.get_value();
        }

        return _default_val;
    };

    bool set(size_t row, size_t col, const T& val){
        if(!is_valid(row,col))
            return false;

        list<Node> &theRow = _rows[row];
        Node insertion(col, val);


        for(typename list<Node>::iterator it = theRow.begin(); it != theRow.end(); ++it) {
            size_t currentCol = it->get_col();

            if (currentCol > col){
                theRow.insert(it, insertion);
                return true;
            }
            else if(currentCol == col){
                if(is_default(val)) {
                    theRow.erase(it);
                    return  true;
                }
                it->set_value(val);
                return  true;
            }
        }

        //if(theRow.empty()){
            theRow.push_back(insertion);
            return true;
        //}



        return true;
    };

    const Matrix<T> get_slice(size_t r1, size_t c1, size_t r2, size_t c2) const{// Mistake most likely is here!
        if(!is_valid(r1,c1)||!is_valid(r2,c2))
             throw OOB_exception();

        Matrix<T> rtnMat((r2 - r1 + 1),(c2 - c1 + 1));

        for(size_t r = 0; r < rtnMat.get_num_rows(); r++){
            for(size_t c = 0; c < rtnMat.get_num_cols(); c++){
                rtnMat.set( r,  c, get(r1 + r, c1 + c));
            }
        }

        return rtnMat;
    };


    string toString() const{
        Matrix<T> strMat = this->get_slice(0,0,get_num_rows() - 1,get_num_cols() -1);

        return strMat.to_string();
    };


    void operator= (const Sparse_Matrix<T> &original){
        _rows = original._rows;
        _num_rows = original._num_rows;
        _num_cols = original._num_cols;
        _default_val = original._default_val;
    }

    static constexpr const float FLOOR = 1e-10;

    bool is_default(const double &val){
        return (abs(val - _default_val) < FLOOR);
    }


    friend class  Tests;

    friend class Mx;



};

#endif //STILT_SPARSE_MATRIX_H
