#include "iostream"
using namespace std;

#include <ctime>
// include Core and Dense compuation parts from Eigen
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace Eigen;

# define MATRIX_SIZE 50

/**************************************************
 * Exercise 5
 * Suppose there is a large Eigen matrix, we want to know the value in the top
 * left 3 x 3 blocks, and then assign it to Identity 3×3.
 * *************************************************/


int main(int argc, char** argv){
    // the large matrix
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE); 

    // Extract the top-left 3*3
    Matrix3d matrix_33;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            matrix_33(i, j) = matrix_NN(i, j);
        }
    }
    // print it out
    cout << "The top left 3*3 matrix is: " << endl << matrix_33 << endl;

    // assign an Identity to it
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(i == j){
                matrix_NN(i, j) = 1;
            }
            else{
                matrix_NN(i, j) = 0;
            }
        }
    }

}


