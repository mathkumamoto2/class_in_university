#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // 画像を読み込む
    Mat img = imread("paprika.jpg");
    Mat hsv, bin;

    // BGR画像をHSV画像へ変換
    cvtColor(img, hsv, COLOR_BGR2HSV);

    // H、S、Vの3チャンネルに分解
    vector<Mat> ch;
    split(hsv, ch);

    // 彩度Sが100より大きい部分を255にする
    threshold(ch[1], bin, 100, 255, THRESH_BINARY);

    for (int ptr = 0; ptr < bin.cols * bin.rows; ptr++) {
        uchar hue = ch[0].data[ptr];

        // 彩度が高く、かつ赤色の画素だけを選択
        if (
            bin.data[ptr] == 255 &&
            (hue >= 169 || hue <= 5)
        ) {
            // 色相を変更
            ch[0].data[ptr] = (ch[0].data[ptr]+90)%180;
        }
    }

    // H、S、Vを再合成
    merge(ch, hsv);

    // HSV画像をBGR画像へ戻す
    cvtColor(hsv, img, COLOR_HSV2BGR);

    imshow("img", img);
    imwrite("ex1_4.png", img);
    waitKey(0);

    return 0;
}
