#include <opencv2/opencv.hpp>
using namespace cv;
unsigned char clamp_uchar(double v)
{
    if (v < 0.0) return 0;
    if (v > 255.0) return 255;
    return (unsigned char)(v + 0.5);
}
int main()
{
    Mat img1 = imread("myphoto.jpg");
    Mat img2 = imread("lena.png");
    if (img1.empty()) return 1;
    if (img2.empty()) return 1;
    resize(img1, img1, Size(512, 512));
    resize(img2, img2, Size(512, 512));
    Mat out(512, 512, CV_8UC3);
    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            double d = x - y;
            double slope = 200.0;
            double alpha = 0.5 + d / slope;
            if (alpha < 0.0) alpha = 0.0;
            if (alpha > 1.0) alpha = 1.0;
            Vec3b p1 = img1.at<Vec3b>(y, x);
            Vec3b p2 = img2.at<Vec3b>(y, x);
            Vec3b q;
            for (int c = 0; c < 3; c++) {
                q[c] = clamp_uchar(alpha * p1[c] + (1.0 - alpha) * p2[c]);
            }
            out.at<Vec3b>(y, x) = q;
        }
    }
    imwrite("ex5_4.jpg", out);
    imshow("ex5_4", out);
    waitKey(0);
    return 0;
}
