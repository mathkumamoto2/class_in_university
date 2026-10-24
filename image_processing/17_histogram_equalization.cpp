#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;
unsigned char clamp_uchar(double v)
{
    if (v < 0.0) return 0;
    if (v > 255.0) return 255;
    return (unsigned char)(v + 0.5);
}
Mat equalize_channel(const Mat &channel)
{
    int w = channel.cols;
    int h = channel.rows;
    int N = w * h;
    int hist[256] = {0};
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            unsigned char value = channel.at<unsigned char>(y, x);
            hist[value]++;
        }
    }
    int cum_hist[256] = {0};
    cum_hist[0] = hist[0];
    for (int i = 1; i < 256; i++) {
        cum_hist[i] = cum_hist[i - 1] + hist[i];
    }
    unsigned char LUT[256];
    for (int i = 0; i < 256; i++) {
        LUT[i] = clamp_uchar(255.0 * cum_hist[i] / N);
    }
    Mat out(h, w, CV_8UC1);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            unsigned char value = channel.at<unsigned char>(y, x);
            out.at<unsigned char>(y, x) = LUT[value];
        }
    }
    return out;
}
int main()
{
    Mat img = imread("myphoto.jpg");
    if (img.empty()) {
        return 1;
    }
    vector<Mat> bgr;
    split(img, bgr);
    for (int i = 0; i < 3; i++) {
        bgr[i] = equalize_channel(bgr[i]);
    }
    Mat out;
    merge(bgr, out);
    imwrite("ex5_6.jpg", out);
    imshow("input", img);
    imshow("ex5_6", out);
    waitKey(0);
    return 0;
}
