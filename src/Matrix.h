//Student ID: 20384891


// Created by Administrator on 10/11/2020.
//
// Resize() is still hanging, waiting to see how to implement it

#ifndef STILT_MATRIX_H
#define STILT_MATRIX_H
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

template <typename T>
class Matrix{
protected:
 vector<vector<T>> _rows;
public:
   Matrix(size_t nr = 0, size_t nc = 0);

   Matrix(Matrix<T> const &original);

    size_t get_num_rows() const{return  _rows.size();}
    size_t get_num_cols() const{
        if(_rows.size() == 0)
            return 0;

        return _rows[0].size()>0? _rows[0].size():0;
    };
    void clear(){ _rows.clear();}
    void resize(size_t nr, size_t nc);
    T &at(size_t r, size_t c){//throws OOB  // It practically is []
        if(!is_valid(r,c)){
            throw OOB_exception();
        }

        return _rows[r][c]; // [r][c] shou be correct because it generate 2 points

    };

    string to_string() const{
        stringstream  ss;
        string str  = "# Matrix\n";
        for(size_t r = 0;r < get_num_rows(); r++) {
            for (size_t c = 0; c < get_num_cols(); c++) {
                ss.clear();
                ss.str("");
                ss << setw(6) << _rows[r][c];
                str += ss.str() + " ";
            }
            str = str.substr(0, str.length() - 1);// Take off last char
            str += '\n';
        }
        return str;
    };

    bool is_valid(size_t r, size_t c){
        if(r < 0 || r >= get_num_rows())
            return false;

        if(c < 0 || c >= get_num_cols())
            return false;

        return true;
    }

    class OOB_exception : public exception {public: string what() { return "Out of bounds access" ;}};

    //Friends---------------------------------
    friend ostream &operator<< (ostream& os, const  Matrix<T> &mat){
        return  os << mat.to_string();
    }

    friend bool operator== (const Matrix<T> &m1, const Matrix<T> &m2){
        if(m1.get_num_cols() != m2.get_num_cols()) return false;
        if(m1.get_num_rows() != m2.get_num_rows()) return false;

        for(size_t r = 0; r < m1.get_num_rows(); r++ ) {
            for (size_t c = 0; c < m1.get_num_cols(); c++) {
                if(m1._rows[r][c] != m2._rows[r][c])
                    return false;
            }
        }

        return true;
    }

    friend bool operator!= (const Matrix<T> &m1,const Matrix<T> &m2){
        return  !(m1 == m2);
    }

    void operator= (const Matrix<T> &original){
        _rows = original._rows;
    }

    friend class Tests;

    friend class Mx;

//    methods that are not in the pdf description;

    void set(size_t nr,size_t nc,T newObj);

//    bool is_valid(size_t r, size_t c);

    string pad (string str ) const;

};

template <class T>
Matrix<T>::Matrix(size_t nr, size_t nc) {
    if(nr > 0 && nc >0){
        for(size_t i = 0; i < nr;i ++){// nr and nc coule be wrong
            _rows.push_back( vector<T>(nc)); //
        }
    }

}

template <class T>
string Matrix<T> :: pad(string str) const{

    for(int i = str.size(); i < 6; i++)
        str = " " + str;
    return str;
}


template <class T>
void Matrix<T> ::resize(size_t nr, size_t nc) {
    if(nr < 0 || nc < 0)
        return; // do nothing

        // Trim nums of rows
    while(_rows.size() != nr)
        _rows.size() > nr? _rows.pop_back():_rows.push_back( vector<T>(nc));


    for(size_t i = 0; i < _rows.size(); i ++){
        while (_rows[i].size() != nc){
            _rows[i].size() > nc? _rows[i].pop_back(): _rows[i].push_back(T());
        }
    }

}

template <typename T>
void Matrix<T> ::set(size_t nr, size_t nc, T newObj) {
//    if (is_valid(nr,nc))
        this->at(nr, nc)  = newObj;
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> const &original) {
    *this = original;
}




#endif //STILT_MATRIX_H
