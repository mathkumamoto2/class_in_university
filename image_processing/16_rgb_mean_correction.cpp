#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
unsigned char clamp_uchar(double v)
{
    if (v < 0.0) return 0;
    if (v > 255.0) return 255;
    return (unsigned char)(v + 0.5);
}
int main()
{
    Mat img = imread("myphoto.jpg");
    if (img.empty()) {
        cout << "myphoto.jpg を読み込めませんでした。" << endl;
        return 1;
    }
    int w = img.cols;
    int h = img.rows;
    int n = w * h;
    double sum_b = 0.0;
    double sum_g = 0.0;
    double sum_r = 0.0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Vec3b p = img.at<Vec3b>(y, x);
            sum_b += p[0];
            sum_g += p[1];
            sum_r += p[2];
        }
    }
    double ave_b = sum_b / n;
    double ave_g = sum_g / n;
    double ave_r = sum_r / n;
    double target_r = 128.0;
    double target_g = 80.0;
    double target_b = 192.0;
    double alpha_r = target_r / ave_r;
    double alpha_g = target_g / ave_g;
    double alpha_b = target_b / ave_b;
    Mat out = img.clone();
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Vec3b p = img.at<Vec3b>(y, x);
            Vec3b q;
            q[0] = clamp_uchar(p[0] * alpha_b);
            q[1] = clamp_uchar(p[1] * alpha_g);
            q[2] = clamp_uchar(p[2] * alpha_r);
            out.at<Vec3b>(y, x) = q;
        }
    }
    imwrite("ex5_5.jpg", out);
    imshow("input", img);
    imshow("ex5_5", out);
    cout << "入力画像の平均値" << endl;
    cout << "R = " << ave_r << endl;
    cout << "G = " << ave_g << endl;
    cout << "B = " << ave_b << endl;
    cout << "目標平均値" << endl;
    cout << "R = " << target_r << endl;
    cout << "G = " << target_g << endl;
    cout << "B = " << target_b << endl;
    cout << "倍率 alpha" << endl;
    cout << "alpha_R = " << alpha_r << endl;
    cout << "alpha_G = " << alpha_g << endl;
    cout << "alpha_B = " << alpha_b << endl;
    waitKey(0);
    return 0;
}
