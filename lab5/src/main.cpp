#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0);
    Mat img;
    while (true) {
        int64 start = cv::getTickCount();
        cap.read(img);
        if (img.empty()) {
            break;
        }
        cv::flip(img, img, 1);
        cv::GaussianBlur(img, img, Size(5, 5), 0);
        imshow("test", img);
        int c = waitKey(15);
        if (c == 27) {
            break;
        }
        cout << "FPS: " << cv::getTickFrequency() / (cv::getTickCount() - start) << endl;
    }
    cap.release();
    destroyWindow("test");
}