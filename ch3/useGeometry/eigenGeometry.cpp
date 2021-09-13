#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;

/**************************************************
 * A demo for the Geometry module in Eigen
 * including roatation matrix, quarternion and euler number
 * to install Eigen, use: sudo apt-get install libeigen3-dev
 * Official documentation: https://eigen.tuxfamily.org/dox/group__TutorialGeometry.html
 * *************************************************/

int main(int argc, char **argv) {
    // Different ways to represent Rotations and Translations
    // 1. 3d rotation matrix
    Matrix3d rotation_matrix = Matrix3d::Identity();        // initialized to Identity matrix

    // 2. Roatation vector: AngleAxis
    // The bottom is not a matrix, but it supports matrix operations through overloading
    AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1));     // rotate 45 degree on z axis
    cout.precision(3);
    cout << "rotation matrix = \n" << rotation_vector.matrix() << endl;  // use .matrix() to convert it into a matrix
    // can also use .toRotationMatrix() and assign it to a matrix
    rotation_matrix = rotation_vector.toRotationMatrix();

    // Use AngleAxis to do coordinate transformation, just use *
    Vector3d v(1, 0, 0);                    // the vector to be rotated
    Vector3d v_rotated = rotation_vector * v;
    cout << "(1, 0, 0) after rotation (by angle axis) = " << v_rotated.transpose() << endl;
    // Use rotation matrix to do coordinate transformation
    v_rotated = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation (by matrix) = " << v_rotated.transpose() << endl;

    // 3. Euler angle
    // We can transfer rotation matrix into Euler angle directly, through .eulerAngles(2, 1, 0)
    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);  // ZYX, i.e. roll, pitch, yaw
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;

    // 4. Euclidean transform matrix (rotation + translation): Eigen::Isometry
    Isometry3d T = Isometry3d::Identity();     // 4*4 matrix
    T.rotate(rotation_vector);                 // rotate according to rotation vector
    T.pretranslate(Vector3d(1, 3, 4));         // Set the translation vector as (1, 3, 4)
    cout << "Transform matrix = \n" << T.matrix() << endl;

    // use the transform matrix to do transformation: left-multiply it
    Vector3d v_transformed = T * v;             // same as: R * v + t
    cout << "v transformed = " << v_transformed.transpose() << endl;

    // For affine transform, use Eigen::Affine3d
    // For Projective transform, use Eigen::Projective3d


    // 5. Quaternion
    // can initalize quaternion through AngleAxis, and vice versa
    Quaterniond q = Quaterniond(rotation_vector);
    // q.coeffs() returns (x, y, z, w), where w is the real part
    cout << "quaternion from rotation vector = " << q.coeffs().transpose() << endl;
    // can also assign the roation matrix to it
    q = Quaterniond(rotation_matrix);
    cout << "quaternion from rotation matrix = " << q.coeffs().transpose() << endl;

    // Use the overloaded * to rotate a vector through quaternion
    v_rotated = q * v;     // Actually, is qvq^{-1} in mathematical
    cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;
    // Can also use qvq^{-1} to do the rotation
    cout << "it's equivalent to: " << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << endl; 

    return 0;
    
    // For reference: Different types of transformation matrices
    // Rotation matrix (3 * 3): Eigen::Matrix3d
    // Rotation vector (3 * 1): Eigen::AngleAxisd
    // Euler angle (3 * 1): Eigen::Vector3d
    // Quaternion (4 * 1): Eigen::Quaterniond
    // Euclidean transformation matrix (4 * 4): Eigen::Isometry3d
    // Affine transform (4 * 4): Eigen::Affine3d
    // Perspective transformation (4 * 4): Eigen::Projective3d


}





