#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;


int main(int argc, char** argv){
    Quaterniond q1 = Quaterniond(0.35, 0.2, 0.3, 0.1);
    Quaterniond q2 = Quaterniond(-0.5, 0.4, -0.1, 0.2);
    q1.normalize();
    Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
    Vector3d p1(0.5, 0, 0.2);

    // define the Euclidean transform matrix
    Isometry3d T1(q1), T2(q2);
    // assign the value of translation
    T1.pretranslate(t1);
    T2.pretranslate(t2);

    // do the transform
    Vector3d p2 = T2 * T1.inverse() * p1;
    cout << endl << p1.transpose() << endl;


    return 0;
}

