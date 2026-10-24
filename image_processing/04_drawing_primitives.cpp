#include <opencv2/opencv.hpp>
using namespace cv;
int main(){
    // 画像バッファを確保: サイズ 640 x 480, RGB3チャンネル 8-bits
    Mat img(480, 640, CV_8UC3);
    // 画像を白く塗りつぶす
    img = CV_RGB(255, 255, 255);
    // (10,10)-(100,30)に幅3、赤で線を引く。アンチエリアシングをかける。
    line(img, Point(10, 10), Point(100, 30), CV_RGB(255, 0, 0), 3, LINE_AA);
    // 四角形を描く: 始点(30,230)から幅120,高さ80、緑。-1は塗りつぶし
    rectangle(img, Rect(30,230,120,80), CV_RGB(0,255,0), -1);
    // 円を描く
    for (int r = 5; r < 120; r += 10) {
        circle(img, Point(320, 240), r, CV_RGB(0, 0, r * 2), 3, LINE_AA);
    }
    // 表示・ファイル保存
    imshow("img", img);
    imwrite("ex2_1.png", img);
    waitKey(0);
    return 0;
}
