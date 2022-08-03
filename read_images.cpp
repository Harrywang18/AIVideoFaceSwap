#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
using namespace cv;

int main(int argc, char* argv[]) {
    
    std::string path = "/home/harry/workspace/data/frame/1.png";
    Mat img_mat;
    img_mat = imread(path);
    if (!img_mat.data) {
        printf("NO image data\n");
        return -1;
    }
    imshow("img", img_mat);
    waitKey(0);
    return 0;
}
