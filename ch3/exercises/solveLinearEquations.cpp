#include "iostream"
using namespace std;

#include <ctime>
// include Core and Dense compuation parts from Eigen
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;

#define MATRIX_SIZE 20

/**************************************************
 * Exercise 6
 * Different ways to solve linear equation: Ax = b
 * For more info, can refer to: https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html
 * https://eigen.tuxfamily.org/dox/group__LeastSquares.html
 * 1. (If invertible): Take A^-1 and left multiply to b
 * 2. SVD decomposition
 * 3. QR decomposition
 * 4. Use Normal equations: solve A^T Ax = A^T b
 * 5. LU decomposition
 * 6. LLT decomposition: Need A to be positive definite
 * 7. LDLT decomposition (Cholesky algorithm): Need A to be positive/negative semi-definite
 * *************************************************/

int main(int argc, char** argv) {
    Matrix<double, Dynamic, Dynamic> A = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    // since A*A^T is always positive definite, use it as an example
    A = A * A.transpose();
    
    Matrix<double, Dynamic, Dynamic> b = MatrixXd::Random(MATRIX_SIZE, 1);

    // 1. take the inverse
    // count the time
    clock_t start_time = clock();
    Matrix<double, MATRIX_SIZE, 1> x1 = A.inverse() * b;
    cout << "time of normal inverse is " << 1000 * (clock() - start_time) / (double) CLOCKS_PER_SEC << "ms" << endl;
    cout << "result is: " << x1.transpose() << endl;


    // 2. SVD decomposition
    start_time = clock();
    cout << "The least-square SVD solution is: \n" << A.bdcSvd(ComputeThinU | ComputeThinV).solve(b) << endl;
    cout << "time of SVD decomposition is " << 1000 * (clock() - start_time) / (double) CLOCKS_PER_SEC << "ms" << endl;


    // 3. QR decomposition
    /**
     * The solve() method in QR decomposition classes also computes the least squares solution. 
     * There are three QR decomposition classes: HouseholderQR (no pivoting, fast but unstable if your matrix is not rull rank), 
     * ColPivHouseholderQR (column pivoting, thus a bit slower but more stable) 
     * and FullPivHouseholderQR (full pivoting, so slowest and slightly more stable than ColPivHouseholderQR).
     */
    start_time = clock();
    cout << "The least-square QR decomposition solution is: \n" << A.colPivHouseholderQr().solve(b) << endl;
    cout << "time of QR decomposition is " << 1000 * (clock() - start_time) / (double) CLOCKS_PER_SEC << "ms" << endl;


    // 4. Normal Equation
    /**
     * This method is usually the fastest, especially when A is "tall and skinny". 
     * However, if the matrix A is even mildly ill-conditioned, this is not a good method, 
     * because the condition number of ATA is the square of the condition number of A. 
     * This means that you lose roughly twice as many digits of accuracy using the normal equation, compared to the more stable methods mentioned above.
     */
    start_time = clock();
    cout << "The Normal equation solution is: \n" << (A.transpose() * A).ldlt().solve(A.transpose() * b) << endl;
    cout << "time of Normal Equation is " << 1000 * (clock() - start_time) / (double) CLOCKS_PER_SEC << "ms" << endl;


    // 5. LU decomposition
    start_time = clock();
    cout << "The LU decomposition solution is: \n" << A.lu().solve(b) << endl;
    cout << "time of LU decomposition is " << 1000 * (clock() - start_time) / (double) CLOCKS_PER_SEC << "ms" << endl;

    // 6. LLT decomposition
    start_time = clock();
    cout << "The LLT decomposition solution is: \n" << A.llt().solve(b) << endl;
    cout << "time of LLT decomposition is " << 1000 * (clock() - start_time) / (double) CLOCKS_PER_SEC << "ms" << endl;

    // 6. LDLT decomposition
    start_time = clock();
    cout << "The LDLT decomposition solution is: \n" << A.ldlt().solve(b) << endl;
    cout << "time of LDLT decomposition is " << 1000 * (clock() - start_time) / (double) CLOCKS_PER_SEC << "ms" << endl;



}






