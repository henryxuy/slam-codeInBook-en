#include "iostream"
using namespace std;

#include <ctime>
// include Core and Dense compuation parts from Eigen
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;

# define MATRIX_SIZE 50

/**************************************************
 * A demo for the basic types in Eigen
 * to install Eigen, use: sudo apt-get install libeigen3-dev
 * Official documentation: https://eigen.tuxfamily.org/index.php?title=Main_Page
 * https://eigen.tuxfamily.org/dox/GettingStarted.html
 * *************************************************/

int main(int argc, char** argv){
    // 1. Declaration
    // All metrices and vector in Eigen use type Eigen::Matrix, which is a template class. 
    // The first 3 generic parameters are: data type, row, column.
    // Declare a 2*3 float matrix with
    Matrix<float, 2, 3> matrix_23;

    // Meanwhile, Eigen also provides many built-in types via typedef
    // but their bottom is still Eigen::Matrix<>
    // e.g. Vector3d is the same as Eigen::Matrix<double, 3, 1>
    Vector3d v_3d;
    Matrix<float, 3, 1> vd_3d;

    // Matrix3d is Eigen::Matrix<double, 3, 3>
    Matrix3d matrix_33 = Matrix3d::Zero();       // initialized to 0

    // Eigen also provides matrix with dynamic size
    // the size is not deteremined during complie time, and can be stored in some runtime variable 
    // fixed size matrix would have better performance, so it's recommended if you know the dim.
    Matrix<double, Dynamic, Dynamic> matrix_dynamic;
    // shortcut of dynmaic size matrix: MatrixXd
    MatrixXd matrix_x;


    // 2. Operation
    // 2.1 initialization
    matrix_23 << 1, 2, 3, 4, 5, 6;
    // To print the matrix, can put it to the output stream directly
    cout << "matrix 2x3 from 1 to 6: \n" << matrix_23 << endl;

    // 2.2 Access the element using (i, j) instead of [][] in array
    cout << "print matrix 2x3 one by one" << endl;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++)
            cout << matrix_23(i, j) << "\t";
        cout << endl;
    }

    // 2.3 Matrix multiplication
    v_3d << 3, 2, 1;
    vd_3d << 4, 5, 6;
    // Note: cannot mix two matrices with different types (e.g. matrix_23: float, v_3d: double)
    // the following is wrong: Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d
    // Need to do explicit casting first: matrix.cast<double>()
    Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << "[1,2,3;4,5,6]∗[3,2,1]=" << result.transpose() << endl;

    // both matrix_23 and vd_3d contain float, so the following is ok
    Matrix<float, 2, 1> result2 = matrix_23 * vd_3d;
    cout << "[1,2,3;4,5,6]∗[4,5,6]: " << result2.transpose() << endl;

    // 2.4 Other matrix operations
    // + - * / are allowed. Note that / is usually matrix / scalar
    // The operations reduing the matrix into a value in Eigen are called "Reduction operations"
    matrix_33 = Matrix3d::Random();
    cout << "random matrix: \n" << matrix_33 << endl;
    cout << "transpose: \n" << matrix_33.transpose() << endl;
    cout << "sum: " << matrix_33.sum() << endl;
    cout << "trace: " << matrix_33.trace() << endl;
    cout << "times 10: \n" << 10 * matrix_33 << endl;
    cout << "inverse: \n" << matrix_33.inverse() << endl;
    cout << "det: " << matrix_33.determinant() << endl;

    // Eigenvalues
    // Real symmetric matrix is guaranteed to be diagonalizable. Here use A^T*A as an example
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;

    // Solve equations
    // Solve matrixNN * x = v_Nd, N = 60 as defined before by macro

    // Method 1: Take the inverse directly and do multiplication, which is time-consumptive
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);  // dynamic size, determined during runtime
    // We still consider A^T*A as an example
    matrix_NN = matrix_NN * matrix_NN.transpose();
    Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);
    // do the time counting
    clock_t time_start = clock();   
    // Take the inverse directly
    Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    cout << "time of normal inverse is " << 1000 * (clock() - time_start) / (double) CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    // Method 2: Use matrix decomposition to solve (e.g. QR decomposition)
    time_start = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time of QR decomp is: " << 1000*(clock() - time_start) / (double) CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    // Method 3: for positive definite matrix, can use Cholesky decomp. to solve
    time_start = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    cout << "time of ldlt decomp is: " << 1000*(clock() - time_start) / (double) CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;


    // 3. Other stuffs
    // 3.0 Partial reductions
    MatrixXf mat(2, 4);
    mat << 1, 2, 6, 9,
           3, 1, 7, 2;
    // take the maxCoeff() at each column
    cout << "Column's maximum: " << endl << mat.colwise().maxCoeff() << endl;
    cout << "Column's maximum: " << endl << mat.rowwise().maxCoeff().transpose() << endl;

    // 3.1 Broadcasting
    // similar to partial reductions. The difference is that broadcasting constructs an expression where a vector
    // (column or row) is interpreted as a matrix by replicating it in one direction
    VectorXf v(2);
    v << 0,
         1;
    // add v to each column of m
    mat.colwise() += v;

    cout << "Broadcasting result: " << endl;
    cout << mat << endl;

    // example of broadcasting: find the nearest neighbor
    // Broadcasting can also be combined with other operations, such as Matrix or Array operations, reductions and partial reductions
    // finds the nearest neighbour of a vector v within the columns of matrix m. 
    // Note: use squaredNorm() to compute the squared Euclidean distance

    // For more info, refer to: https://eigen.tuxfamily.org/dox/group__TutorialReductionsVisitorsBroadcasting.html
    MatrixXf m(2, 4);
    v << 2,
         3;
    m << 1, 23, 6, 9,
         3, 11, 7, 2;
    MatrixXf::Index index;
    // find the nearest neighbor
    (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);

    cout << "Nearest neighbor is column " << index << ":" << endl;
    cout << m.col(index) << endl;

    return 0;
}



