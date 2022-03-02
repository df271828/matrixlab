#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <complex>
#include <fstream>
#include "Matrix.h"
using namespace std;
int main(){
    Matrix a(2, 2);
    Matrix b(2, 2);
    UnitMatrix e(3);
    vector<vector<double>> vec;
    vector<double> vec1 = {1, 2};
    vector<double> vec2 = {3, 4};
    vec.push_back(vec1);
    vec.push_back(vec2);
    //UpperTriangleMatrix f(vec);
    Matrix c(vec);
    cout << c;
    /*cout << c+c;
    cout << c*c;
    vector<vector<double>> vecn;
    vecn.push_back(vec1);
    Matrix c1(vecn);
    vector<vector<double>> vecn1;
    vecn1.push_back(vec2);
    Matrix c2(vecn1);
    cout << VectorsAngle(c1,c2)<<endl;*/
    cout << c.Gauss()<<endl;
    cout << InvertMatrix(c);
    //cout << c1.MaxNorma()<<endl;
    //WriteToBinary(c, "matrix1.bin");
    //ReadFromBinary(a, "matrix1.bin");
    //cout << a;
    //freopen("matrixOut.txt","w",stdout);
    //cout << c;
    //fclose(stdout);
    freopen("matrixIn.txt","r",stdin);
    cin >> a;
    fclose(stdin);
    cout << a;
    cout << e;
    return 0;
}
