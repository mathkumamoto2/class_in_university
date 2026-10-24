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
    Mat out = img.clone();
    int block_size = 8;
    for (int by = 0; by < h; by += block_size) {
        for (int bx = 0; bx < w; bx += block_size) {
            int sum_b = 0;
            int sum_g = 0;
            int sum_r = 0;
            int count = 0;
            for (int y = by; y < by + block_size; y++) {
                for (int x = bx; x < bx + block_size; x++) {
                    if (x >= w || y >= h) {
                        continue;
                    }
                    Vec3b p = img.at<Vec3b>(y, x);
                    sum_b += p[0];
                    sum_g += p[1];
                    sum_r += p[2];
                    count++;
                }
            }
            Vec3b average;
            average[0] = sum_b / count;
            average[1] = sum_g / count;
            average[2] = sum_r / count;
            for (int y = by; y < by + block_size; y++) {
                for (int x = bx; x < bx + block_size; x++) {
                    if (x >= w || y >= h) {
                        continue;
                    }
                    out.at<Vec3b>(y, x) = average;
                }
            }
        }
    }
    imwrite("ex5_2.jpg", out);
    imshow("ex5_2", out);
    waitKey(0);
    return 0;
}
