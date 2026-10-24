#include <opencv2/opencv.hpp>
using namespace cv;
// ヒストグラム計算
void calc_histogram(const Mat & img, float *hist) {
    float wh = img.cols * img.rows;
    memset(hist, 0, sizeof(float) * 256);
    // 全画素をスキャンして、ヒストグラム加算
    for (int ptr = 0; ptr < wh; ptr++)
        hist[img.data[ptr]]++;
    // [0, 1]の範囲に正規化
    for (int i = 0; i < 256; i++)
        hist[i] /= float(wh);
}
// ヒストグラム描画
void draw_histogram(Mat & img,float *hist, Scalar col) {
    for (int i = 0; i < 256; i++) {
        line(img, Point(i, 256), Point(i, 256 - 10000 * hist[i]), col);
    }
}
int main(){
    // モノクロで画像を読み込む
    Mat img = imread("lena.png", 0);
    // ヒストグラムを計算
    float hist[256];
    calc_histogram(img, hist);
    // ヒストグラム描画
    draw_histogram(img, hist, CV_RGB(128,128,128));
    imshow("img", img);
    waitKey(0);
    return 0;
}
