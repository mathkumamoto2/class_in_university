#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    // ファイルの読み込み
    Mat img = imread("./lena.png");
    int w = img.cols; // 画像幅取得
    int h = img.rows; // 画像高取得
    for(int ptr = 0; ptr < w * h; ptr++)
        img.data[ptr * 3] = 0;
    // 表示
    imshow("img", img);
    imwrite("ex1_3.png", img);
    waitKey(0);
    return 0;
}
