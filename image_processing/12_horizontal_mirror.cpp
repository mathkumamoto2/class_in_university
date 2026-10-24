#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat img = imread("myphoto.jpg");
    if (img.empty()) {
        return 1;
    }
    int w = img.cols;
    int h = img.rows;
    Mat out(h, w * 2, CV_8UC3);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Vec3b p = img.at<Vec3b>(y, x);
            out.at<Vec3b>(y, x) = p;
            out.at<Vec3b>(y, w + (w - 1 - x)) = p;
        }
    }
    imwrite("ex5_1.jpg", out);
    imshow("ex5_1", out);
    waitKey(0);
    return 0;
}
