# include <iostream>
# include <cmath>
# include <Eigen/Core>
# include <Eigen/Geometry>
# include "sophus/se3.hpp"

using namespace std;
using namespace Eigen;

/**************************************************
 * A demo for the Sophus module 
 * Git repo: https://github.com/strasdat/Sophus
 * **************************************************/

int main(int argc, char **argv) {
    // rotate 90-degree around z axis using rotation vector
    Matrix3d R = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();
    // Can also use quaternion
    Quaterniond q(R);

    // 1. Lie Group and Lie Algebra for SO(3)
    // Both are the same to construct Lie Group: Sophus::SO3d
    Sophus::SO3d SO3_R(R);
    Sophus::SO3d SO3_q(q);
    cout << "Print the Lie group" << endl;
    cout << "SO(3) from matrix:\n" << SO3_R.matrix() << endl;
    cout << "SO(3) from quaternion:\n" << SO3_q.matrix() << endl;
    cout << "they are equal" << endl;

    // Use the logarithmic mapping to get the Lie Algebra 
    Vector3d so3 = SO3_R.log();
    cout << "Lie Algebra so3 = " << so3.transpose() << endl;
    // hat: vector to skew-symmetric matrix
    cout << "so3 hat = \n" << Sophus::SO3d::hat(so3) << endl;
    // vee: skew-symmetric matrix to vector
    cout << "so3 hat vee = " << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << endl;

    // 2. perturbation model
    // a small update 
    Vector3d update_so3(1e-4, 0, 0);
    // update: multiply in Lie Group
    Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R;
    cout << "SO3 updated = \n" << SO3_updated.matrix() << endl;

    cout << "∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗" << endl;
    // For SE(3), all are similar
    Vector3d t(1, 0, 0);          // vector for translation
    // Lie Group: can initialize SE3d either from (R, t) or (q, t)
    Sophus::SE3d SE3_Rt(R, t);
    Sophus::SE3d SE3_qt(q, t);
    // print them out
    cout << "SE3 from R,t= \n" << SE3_Rt.matrix() << endl;
    cout << "SE3 from q,t= \n" << SE3_qt.matrix() << endl;

    // Lie Algebra: 6d vector. Here use a typedef for convenience
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout << "se3 = " << se3.transpose() << endl;

    // From the output we can find that in Sophus, the translation is before the roation in se(3)
    // we also have hat (vector -> skew-symmetric matrix) and vee (skew-symmetric matrix -> vector) operators
    cout << "se3 hat = \n" << Sophus::SE3d::hat(se3) << endl;
    cout << "se3 hat vee = " << Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose() << endl;

    // update in Perturbation model
    Vector6d update_se3;
    update_se3.setZero();
    update_se3(0, 0) = 1e-4d;
    Sophus::SE3d SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_Rt;
    cout << "SE3 updated = " << endl << SE3_updated.matrix() << endl;


    return 0;
}



