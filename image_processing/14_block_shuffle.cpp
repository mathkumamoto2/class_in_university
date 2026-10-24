#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <random>
using namespace cv;
using namespace std;
int main()
{
    Mat img = imread("myphoto.jpg");
    if (img.empty()) {
        return 1;
    }
    int w = img.cols;
    int h = img.rows;
    int block_size = 32;
    int block_cols = (w + block_size - 1) / block_size;
    int block_rows = (h + block_size - 1) / block_size;
    int block_count = block_cols * block_rows;
    Mat out(h, w, CV_8UC3, Scalar(0, 0, 0));
    vector<int> indices(block_count);
    for (int i = 0; i < block_count; i++) {
        indices[i] = i;
    }
    random_device rd;
    mt19937 gen(rd());
    shuffle(indices.begin(), indices.end(), gen);
    for (int dst_id = 0; dst_id < block_count; dst_id++) {
        int src_id = indices[dst_id];
        int src_block_x = src_id % block_cols;
        int src_block_y = src_id / block_cols;
        int src_x0 = src_block_x * block_size;
        int src_y0 = src_block_y * block_size;
        int dst_block_x = dst_id % block_cols;
        int dst_block_y = dst_id / block_cols;
        int dst_x0 = dst_block_x * block_size;
        int dst_y0 = dst_block_y * block_size;
        for (int y = 0; y < block_size; y++) {
            for (int x = 0; x < block_size; x++) {
                int src_x = src_x0 + x;
                int src_y = src_y0 + y;
                int dst_x = dst_x0 + x;
                int dst_y = dst_y0 + y;
                if (dst_x >= w || dst_y >= h) {
                    continue;
                }
                if (src_x >= w || src_y >= h) {
                    out.at<Vec3b>(dst_y, dst_x) = Vec3b(0, 0, 0);
                } else {
                    out.at<Vec3b>(dst_y, dst_x) = img.at<Vec3b>(src_y, src_x);
                }
            }
        }
    }
    imwrite("ex5_3.jpg", out);
    imshow("ex5_3", out);
    waitKey(0);
    return 0;
}
