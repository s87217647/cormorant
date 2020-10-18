
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

    Sparse_Matrix<int> m1(3,3);
    Sparse_Matrix<int> m2(3,3);
    Sparse_Matrix<int> res(3,3);

//    Mx::setRandom(m1,"Not 0");
//    Mx::setRandom(m2, "Not 0");

//    Mx::setRandom(m1,"zero");
    size_t x = -5;
    size_t y = 5;
    cout << x*y << endl;


    cout<< m1.toString() << endl;
    cout << m2.toString() << endl;

    Mx::multiply(m1,m2,res);
    cout << res.toString() << endl;

}


