#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    // ファイルの読み込み
    Mat img = imread("./lena.png");
    // 表示・ファイル保存
    imshow("img", img);
    imwrite("ex1.png", img);
    waitKey(0);
    return 0;
}
