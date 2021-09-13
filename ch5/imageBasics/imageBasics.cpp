#include <iostream>
#include <chrono>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


/**************************************************
 * A demo for opencv3
 * For more tutorials:
 * https://docs.opencv.org/3.4.15/d9/df8/tutorial_root.html
 * *************************************************/


int main(int argc, char **argv) {
    // 1. Declaration and initialization
    // read the image in argv[1]
    cv::Mat image;
    // use cv.imread() to read the image
    image = cv::imread(argv[1]);

    // check whether the image has been read correctly
    if (image.data == nullptr) {
        // the file does not exist
        cerr << "file: " << argv[1] << " does not exist." << endl;
        return 0;
    }
    // output some basic information
    cout << "The width is: " << image.cols << ", the height is: " << image.rows << 
        ", the number of channels is: " << image.channels() << endl;

    // show the image using cv::imshow(). Cannot show it in the command line
    // cv::imshow("image", image);
    // wait for an arbitrary keyboard to close the window of shown image
    // cv::waitKey(0);

    // check the type of image
    if(image.type() != CV_8UC1 && image.type() != CV_8UC3) {
        // the image type does not meet the requirement
        cout << "please input a colored or greyscale image." << endl;
        return 0;
    }

    // 2. loop through the pixels in the image
    // use std::chrono to count the time
    // can also use iterator in opencv, e.g. MatIterator, Mat_<Vec3b>::iterator
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (size_t y = 0; y < image.rows; y++){
        // cv::Mat:ptr to get the row pointer of the image
        unsigned char *row_ptr = image.ptr<unsigned char>(y);    // the header pointer of y-th row
        for (size_t x = 0; x < image.cols; x++){
            // the pointer to the current pixel
            unsigned char *data_ptr = &row_ptr[x * image.channels()];
            // loop through each channel in that pixel
            for(int c = 0; c != image.channels(); c++){
                unsigned char data = data_ptr[c];           // data is the cth channel value for I(x, y)
            }
        }
    }

    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast <chrono::duration <double>>(t2 - t1);
    cout << "time used: " << time_used.count() << " seconds." << endl;

    // 3. copy the cv::Mat
    // use "=" will only copy the reference
    cv::Mat image_another = image;
    // change image_another will also change the original one
    image_another(cv::Rect(0, 0, 100, 100)).setTo(0);           // set the upper-left 100*100 block to 0
    // cv::imshow("image", image);
    // cv::waitKey(0);

    // use .clone() to do real copy
    cv::Mat image_clone = image.clone();
    image_clone(cv::Rect(0, 0, 100, 100)).setTo(255);
    // cv::imshow("image", image);
    // cv::imshow("image_clone", image_clone);
    // cv::waitKey(0);

    // For more image processing operations
    // check: https://docs.opencv.org/3.4.15/de/d7a/tutorial_table_of_content_core.html
    // https://docs.opencv.org/3.4.15/d7/da8/tutorial_table_of_content_imgproc.html
    // cv::destroyAllWindows();


    return 0;
}




