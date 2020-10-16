
#include <iostream>
#include <vector>
#include "Matrix.h"
#include <string>
#include "Sparse_Matrix.h"
#include <iomanip>


using namespace std;
int main(){

    Sparse_Matrix<double> spaMat(5,5,6.66);

    spaMat.clear();

    cout << spaMat.toString() <<endl;

    vector<int> x;
    x.push_back(1);
    x.push_back(2);

    x.clear();




}
