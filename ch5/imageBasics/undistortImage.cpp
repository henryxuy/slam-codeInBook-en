#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
string image_file = "./distorted.png";

int main(int argc, char **argv){
    // in opencv, can use cv::Undistort() directly
    // Here is only for illustration

    // the parameter for distortion
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
    // intrinsics
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;

    cv::Mat image = cv::imread(image_file, 0);        // the image type is CV_8UC1
    int rows = image.rows, cols = image.cols;
    cv::Mat image_undistort = cv::Mat(rows, cols, CV_8UC1);     // the undistored image

    // compute the pixels in the undistored image through the formula
    for(int v = 0; v < rows; v++){
        for (int u = 0; u < cols; u++){

            double x = (u - cx) / fx, y = (v - cy) / fy;
            double r = sqrt(x * x + y * y);
            double x_distorted = x * (1 + k1 * r * r + k2 * r * r * r * r) + 2 * p1 * x * y + p2 * (r * r + 2 * x * x);
            double y_distorted = y * (1 + k1 * r * r + k2 * r * r * r * r) + p1 * (r * r + 2 * y * y) + 2 * p2 * x * y;
            double u_distorted = fx * x_distorted + cx;
            double v_distorted = fy * y_distorted + cy;
            

        }

    }




}




