#include <opencv2/opencv.hpp>
using namespace cv;
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
int main(){
    Mat img = imread("lena.png");
    float gamma = 2.2;
    for (int ptr = 0; ptr < 3 * img.cols * img.rows; ptr++)
        img.data[ptr] = max(min(255 * pow(img.data[ptr] / 255.0, 1.0 / gamma), 255), 0);
    imshow("img", img);
    // レポート掲載コードでは出力ファイル名も ex3_1.png になっているため、そのまま保持
    imwrite("ex3_1.png", img);
    waitKey(0);
    return 0;
}
