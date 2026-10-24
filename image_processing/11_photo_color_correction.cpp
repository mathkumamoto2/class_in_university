#include <opencv2/opencv.hpp>
using namespace cv;
float calc_histgram(const Mat & img, float *hist) {
    float wh = img.cols * img.rows;
    memset(hist, 0, sizeof(float) * 256);
    for (int ptr = 0; ptr < wh; ptr++)
        hist[img.data[ptr]]++;
    float average = 0;
    for (int i = 0; i < 256; i++) {
        hist[i] /= float(wh);
        average += i * hist[i];
    }
    return average;
}
int main(){
    Mat img = imread("myphoto.jpg");
    Mat ref_img = imread("ref.jpg");
    std::vector<Mat> rgb, ref_rgb;
    split(img, rgb);
    split(ref_img, ref_rgb);
    float hist[3][256], ref_hist[3][256];
    float ave[3], ref_ave[3];
    float gain[3];
    for(int i = 0; i < 3; i++){
        ave[i] = calc_histgram(rgb[i], hist[i]);
        ref_ave[i] = calc_histgram(ref_rgb[i], ref_hist[i]);
        gain[i] = ref_ave[i] / ave[i];
        rgb[i] = rgb[i] * gain[i];
    }
    Mat out;
    merge(rgb, out);
    // 画像サイズを縮小する
    Mat resized;
    resize(out, resized, Size(525, 700));
    // 画像表示・保存
    imshow("myphoto", img);
    imshow("out", resized);
    imshow("ref", ref_img);
    imwrite("ex4.png", resized);
    waitKey(0);
    return 0;
}
