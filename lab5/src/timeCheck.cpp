#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <fstream>
#include <list>
using namespace std;
using namespace cv;
#define time to_string(end - start)

int main() {
    for (const auto &delay: {1, 15, 33}) {
        ofstream data("data " + to_string(delay) + " ms.txt");
        VideoCapture cap(0);
        Mat img;
        int frame = 0;
        int64 start, end;
        while (frame < 500) {
            frame++;

            start = cv::getTickCount();
            cap.read(img);
            end = cv::getTickCount();
            data << "frame " + to_string(frame) + " read: " + time + " ticks\n";

            if (img.empty()) {
                break;
            }

            start = cv::getTickCount();
            cv::flip(img, img, 1);
            cv::GaussianBlur(img, img, Size(5, 5), 0);
            end = cv::getTickCount();
            data << "frame " + to_string(frame) + " modify: " + time + " ticks\n";

            start = cv::getTickCount();
            imshow("test", img);
            end = cv::getTickCount();
            data << "frame " + to_string(frame) + " show: " + time + " ticks\n";

            start = cv::getTickCount();
            const int c = waitKey(delay);
            end = cv::getTickCount();
            data << "frame " + to_string(frame) + " delay: " + time + " ticks\n";
            if (c == 27) {
                break;
            }
        }
        cap.release();
        destroyWindow("test");
    }
}
