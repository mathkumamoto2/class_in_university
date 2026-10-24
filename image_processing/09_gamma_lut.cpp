#include <opencv2/opencv.hpp>
using namespace cv;
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
void gen_LUT_gamma(unsigned char *LUT, float gamma) {
    for(int i = 0; i < 256; i++)
        LUT[i] = max(min(255 * pow(i / 255.0, 1.0 / gamma), 255), 0);
}
int main(){
    Mat img = imread("lena.png");
    float gamma = 0.7;
    unsigned char LUT[256];
    gen_LUT_gamma(LUT, gamma);
    for (int ptr = 0; ptr < 3 * img.cols * img.rows; ptr++)
        img.data[ptr] = LUT[img.data[ptr]];
    imshow("img", img);
    imwrite("ex3_3.png", img);
    waitKey(0);
    return 0;
}
