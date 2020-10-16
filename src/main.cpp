
#include <iostream>
#include <vector>
#include "Matrix.h"
#include <string>
#include "Sparse_Matrix.h"
#include <iomanip>
#include "Matrix_Algorithms.h"
#include<cstdlib>


using namespace std;
int main(){

    Matrix<int> m1(2,4);
    Matrix<int> m2(4,5);

//    cout << m2 << endl;

    vector<int> x = Mx::get_row(m2 , 1);

    Mx::multiply(m1,m2);

}

//class MyClass{
static void setRandom(Matrix<int> m) {
    size_t max_C = m.get_num_cols();
    size_t max_R = m.get_num_cols();
    for (size_t c = 0; c < max_C; c++) {
        for (size_t r = 0; r < max_R; r++) {
            m.set(c,r,(rand()%10));
        }
    }

}
//};