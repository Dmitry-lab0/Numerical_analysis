#include "utils.h"
#include "vector.h"
#include "matrix.h"
#include "solve_linear.h"
#include "linear_system.h"
#include "utils.h"
#include <iostream>
#include <vector>

int main() {
    // //Matrix<double> matr = {
    // //{28.859, -0.008, 2.406, 19.240},
    // //{14.436,-0.001, 1.203, 9.624},
    // //{120.204, -0.032, 10.024, 80.144},
    // //{-57.714, 0.016,-4.812, -38.478}
    // //};
    // //Vector<double> vec = { 30.459, 18.248, 128.156, -60.908};
    // //Matrix<double> matr = {
    // //{10, 6, 2, 0},
    // //{5, 1, -2, 4},
    // //{3, 5, 1, -1},
    // //{0, 6, -2, 2}
    // //};

    // 25 2
    //Matrix<double> matr = { {80.0000, -4.3200, -5.0400, 3.6900},
     //{-6.7000, 149.8000, -6.7600, -1.1300},
     //{-4.5200, 1.6900, -84.8000, 0.0000},
     //{-8.5800, 5.5200, 9.1800, 65.6000} };
     //Vector<double> vec = { 584.4800, -1258.8200, -214.7600, -85.8600 };

     // 25 1
     //Matrix<double> matr = {
     //{26.4900, 42.9660, -56.7780, -72.5760},
     //{-0.4200, -0.6810, 1.0430, 0.6510},
     //{8.8200, 14.3220, -18.8960, -24.1920},
     //{2.5200, 4.0920, -5.2560, -7.4120}
     //};
     //Vector<double> vec = { -6.9180, -0.2470, -2.3060, -1.0160 };

     // 21 1
     //Matrix<double> matr = {
     //{1.840, 0.0400, 7.0840, -23.2920},
     //{27.0000, -0.0690, 108.4760, -345.3930},
     //{5.4000, -0.0100, 21.6690, -69.0570},
     //{1.8000, 0.0000, 7.2000, -23.0000}
     //};
     //Vector<double> vec = { -7.1360,  -319.6040, -62.6760, -19.8000};



    // 5
    Matrix<double> matr = {
    {28.859, -0.008, 2.406, 19.240},
    { 14.436, -0.001, 1.203, 9.624 },
    {120.204, -0.032, 10.024, 80.144},
    {-57.714, 0.016, -4.812, -38.478}
    };

    Vector<double> vec = { 30.459,  18.248, 128.156, -60.908};

   // //std::cout << NormInf(matrix) << std::endl; 
   // //Matrix<double> inverse = inverseMatrix(matr);
   // //Matrix<double> res = matr * inverse;
   // //std::cout << "inverse" << std::endl;
   // //inverse.print();
   // //std::cout << "A * inverse" << std::endl;
   // //res.print();

   // //std::cout << NormInf(vectorB) << std::endl;
   // //std::vector<std::vector<double>> matrix = {
   // //{0, 0, 0, 1},
   // //{0,0, 1, 1},
   // //{0, 1, 1, 1},
   // //{1,1,1, 1}
   // //};
   // //Vector<double> vectorB = { 1,2,3,4 };
    std::cout << "ConditionNumber" << std::endl;
    std::cout << getConditionNumber(matr, 1) << std::endl;
    std::cout << "Estimate Condition Number" << std::endl;
    std::cout << estimateConditionNumber(matr, vec, 2) << std::endl;
   // // Perform forward elimination
    QR<double> solver(matr, vec);
    Vector<double> ans = solver.solveSystem();
    Matrix<double> Q = solver.getQ();
    Matrix<double> R = solver.getR();
    std::cout << "Q*R" << std::endl;
    Matrix<double> res = Q*R;
    res.print();
   // // Print the modified matrix A
   // //std::cout << "Modified matrix A:" << std::endl;
   // //for (const auto& row : res) {
   // //    for (const auto& element : row) {
   // //        std::cout << element << " ";
   // //    }
   // //    std::cout << std::endl;
   // //}
   // solver.setEps(0.1e-15); // threshold for considering values as zero.
   // Matrix<double> A = solver.getMatrix();
   // std::cout << "A" << std::endl;
   // A.print();
    std::cout << "Answer" << std::endl;
    ans.print();
   // //std::cout << "A*x" << std::endl;
   // //Vector<double> b_ = A * ans;
   // //b_.print();
   // //std::cout << "A*x - b" << std::endl;
   // //Vector<double> diff;
    std::cout << "residual" << std::endl;
    std::cout <<  solver.getResidualNorm() << std::endl;


    //Matrix<double> matr = readMatrixFromFile<double>("data/matrix.txt");
    //Vector<double> vec = readVectorFromFile<double>("data/vector.txt");
    //QR<double> solver(matr, vec);
    //Vector<double> ans = solver.solveSystem();
    //std::cout << "ConditionNumber" << std::endl;
    //std::cout << getConditionNumber(matr, 1) << std::endl;

    return 0;
}

