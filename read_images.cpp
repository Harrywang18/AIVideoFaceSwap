#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;

bool cmp(String a, String b){
    int pos_a_l = a.find("data");
    int pos_b_l = b.find("data");
    pos_a_l += 5;
    pos_b_l += 5;
    int pos_a_r = a.find("png");
    int pos_b_r = b.find("png");
    pos_a_r -= 2;
    pos_b_r -= 2;
    int num_a = atoi(a.substr(pos_a_l, pos_a_r - pos_a_l + 1).c_str());
    int num_b = atoi(b.substr(pos_b_l, pos_b_r - pos_b_l + 1).c_str());
    return num_a < num_b;
}
int main(int argc, char* argv[]) {
    // get the size of img
    string path = "../test_rendering_data/1.png";
    Mat temp;
    temp = imread(path);
    cout << temp.size() << endl;
    
    // generate video
    const int fps = 50;
    VideoWriter video("../video_dir/test.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, temp.size());
    String pattern = "../test_rendering_data/*.png";
    vector<String> fn;
    glob(pattern, fn, false);
    size_t size = fn.size();
    sort(fn.begin(), fn.end(), cmp);
    for(size_t i = 0 ; i < size ; i++){
        // cout << fn[i] << endl;
        Mat img = imread(fn[i]);
        // resize(img, img, temp.size());
        video << img;
    }
    cout << "generate video complete!" << endl;
    return 0;
}
