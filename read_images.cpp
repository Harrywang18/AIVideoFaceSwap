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
    
    /* generate the video */
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

    /* play the video */
    String video_show = "video";
    namedWindow(video_show, CV_WINDOW_NORMAL);
    VideoCapture capture("../video_dir/test.avi");
    if(!capture.isOpened()){
        cout << "open failed" << endl;
        return -1;
    }
    
    long total_frame = capture.get(CV_CAP_PROP_FRAME_COUNT);
    
    
    // set the start frame id
    long frame_start = 0;
    capture.set(CV_CAP_PROP_POS_FRAMES, frame_start);

    // set the stop frame id
    long frame_stop = total_frame - 1;

    double rate = capture.get(CV_CAP_PROP_FPS);
    bool stop = false;
    int delay = 1000 / rate;

    long cur_frame = frame_start;

    Mat frame;
    while(1){
        if(!capture.read(frame)){
            cout << "read video failure" << endl;
            return -1;
        }
        imshow("video", frame);
        int c = waitKey(delay);
        if(cur_frame >= frame_stop){
            cur_frame = frame_start;
            capture.set(CV_CAP_PROP_POS_FRAMES, frame_start);
        }
        cur_frame++;
    }
    capture.release();
    waitKey(0);
    return 0;


    return 0;
}
