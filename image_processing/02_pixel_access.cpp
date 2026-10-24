#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    // ファイルの読み込み
    Mat img = imread("./lena.png");
    int w = img.cols; // 画像幅取得
    img.data[(128 + 128 * w) * 3] = 0;
    // 表示
    imshow("img", img);
    imwrite("ex1_2.png", img);
    waitKey(0);
    return 0;
}
