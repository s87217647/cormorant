
#include <iostream>
#include <vector>
#include "Matrix.h"
#include <string>
#include "Sparse_Matrix.h"
#include <iomanip>


using namespace std;
int main(){

    Sparse_Matrix<double> spaMat(5,5,6.66);

    spaMat.set(1,1,5);
    spaMat.set(1,0,5);


    cout << spaMat.toString() << endl;

}
