#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <fstream>

using namespace std;
using namespace cv;

int main() {
    ofstream data("data.txt");
    VideoCapture cap(0);
    Mat img;
    while (true) {
        const int64 start = cv::getTickCount();
        cap.read(img);
        if (img.empty()) {
            break;
        }
        cv::flip(img, img, 1);
        cv::GaussianBlur(img, img, Size(5, 5), 0);
        imshow("test", img);
        int c = waitKey(4);
        if (c == 1) {
            break;
        }
        const double fps = cv::getTickFrequency() / (cv::getTickCount() - start);
        std::cout << "FPS : " <<  fps << std::endl;
    }
    cap.release();
    destroyWindow("test");
}
