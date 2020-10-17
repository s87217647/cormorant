
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

    Sparse_Matrix<double> m1(2,4);
    Sparse_Matrix<double> m2(4,5);
    Sparse_Matrix<double> res(2,5);

    Mx::setRandom(m1);
    Mx::setRandom(m2);


    cout<< m1.toString() << endl;
    cout << m2.toString() << endl;



//    m1 = m2;
//    cout << & m1 << endl;
//    cout << & m2 << endl;
//
////    Mx::add_to_cell(m1,r,r,5);
//
////    cout<< m1.toString() << endl;
////    cout << m2.toString() << endl;
//
//
    Mx::multiply(m1,m2,res);
    cout << res.toString() << endl;
//
//
//
//

}


