#include <math.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    const char *input = "ex4.png";
    const char *output = "ex5.png";

    if (argc >= 2)
        input = argv[1];

    if (argc >= 3)
        output = argv[2];

    // 画像を読み込む
    Mat img = imread(input);

    if (img.empty())
        return -1;

    // 画像サイズを統一
    double scale = 768.0 / img.cols;
    resize(img, img, Size(), scale, scale);

    Mat gray, gray2, hsv;

    cvtColor(img, gray, COLOR_BGR2GRAY);
    cvtColor(img, hsv, COLOR_BGR2HSV);

    equalizeHist(gray, gray2);
    GaussianBlur(gray2, gray2, Size(9, 9), 2);

    double background =
        (
            gray.at<uchar>(10, 10) +
            gray.at<uchar>(10, gray.cols - 11) +
            gray.at<uchar>(gray.rows - 11, 10) +
            gray.at<uchar>(gray.rows - 11, gray.cols - 11)
        ) / 4.0;

    vector<Vec3f> circles;

    // 円検出
    if (background < 100) {
        HoughCircles(
            gray2,
            circles,
            HOUGH_GRADIENT,
            1.2,
            100,
            100,
            40,
            40,
            120
        );
    }
    else {
        HoughCircles(
            gray2,
            circles,
            HOUGH_GRADIENT,
            1.2,
            60,
            100,
            35,
            30,
            100
        );
    }

    // 重複した円を除去
    vector<Vec3f> filtered;

    for (int i = 0; i < circles.size(); i++) {
        bool merged = false;

        for (int j = 0; j < filtered.size(); j++) {
            float dx = circles[i][0] - filtered[j][0];
            float dy = circles[i][1] - filtered[j][1];
            float distance = sqrt(dx * dx + dy * dy);
            float radius = max(circles[i][2], filtered[j][2]);

            if (distance < radius * 0.9) {
                if (circles[i][2] > filtered[j][2])
                    filtered[j] = circles[i];

                merged = true;
                break;
            }
        }

        if (!merged)
            filtered.push_back(circles[i]);
    }

    if (filtered.size() == 0)
        return -1;

    vector<Mat> ch;
    split(hsv, ch);

    vector<Point> centers;
    vector<int> radii;
    vector<double> meanS;
    vector<double> colorDifference;
    vector<int> holes;
    vector<int> copper;
    vector<int> values;

    for (int i = 0; i < filtered.size(); i++) {
        Point center(
            cvRound(filtered[i][0]),
            cvRound(filtered[i][1])
        );

        int r = cvRound(filtered[i][2]);

        Mat coinMask =
            Mat::zeros(img.rows, img.cols, CV_8UC1);

        Mat centerMask =
            Mat::zeros(img.rows, img.cols, CV_8UC1);

        Mat ringMask =
            Mat::zeros(img.rows, img.cols, CV_8UC1);

        Mat backgroundMask =
            Mat::zeros(img.rows, img.cols, CV_8UC1);

        circle(
            coinMask,
            center,
            cvRound(r * 0.75),
            Scalar(255),
            FILLED
        );

        circle(
            centerMask,
            center,
            cvRound(r * 0.16),
            Scalar(255),
            FILLED
        );

        circle(
            ringMask,
            center,
            cvRound(r * 0.70),
            Scalar(255),
            FILLED
        );

        circle(
            ringMask,
            center,
            cvRound(r * 0.35),
            Scalar(0),
            FILLED
        );

        circle(
            backgroundMask,
            center,
            cvRound(r * 1.35),
            Scalar(255),
            FILLED
        );

        circle(
            backgroundMask,
            center,
            cvRound(r * 1.10),
            Scalar(0),
            FILLED
        );

        Scalar hsvMean = mean(hsv, coinMask);
        Scalar bgrMean = mean(img, coinMask);

        Scalar centerMean, centerStd;
        Scalar ringMean, ringStd;
        Scalar backgroundMean, backgroundStd;

        meanStdDev(
            ch[2],
            centerMean,
            centerStd,
            centerMask
        );

        meanStdDev(
            ch[2],
            ringMean,
            ringStd,
            ringMask
        );

        meanStdDev(
            ch[2],
            backgroundMean,
            backgroundStd,
            backgroundMask
        );

        bool hole =
            fabs(centerMean[0] - backgroundMean[0]) < 25 &&
            fabs(centerMean[0] - ringMean[0]) > 25;

        double difference = bgrMean[2] - bgrMean[0];

        bool isCopper =
            hsvMean[1] > 75 &&
            difference > 15;

        centers.push_back(center);
        radii.push_back(r);
        meanS.push_back(hsvMean[1]);
        colorDifference.push_back(difference);
        holes.push_back(hole);
        copper.push_back(isCopper);
        values.push_back(0);
    }

    // 1円玉を大きさの基準にする
    double oneYenRadius = 10000;

    for (int i = 0; i < filtered.size(); i++) {
        if (!holes[i] && !copper[i]) {
            if (radii[i] < oneYenRadius)
                oneYenRadius = radii[i];
        }
    }

    if (oneYenRadius == 10000)
        return -1;

    int total = 0;

    for (int i = 0; i < filtered.size(); i++) {
        if (holes[i]) {
            if (copper[i])
                values[i] = 5;
            else
                values[i] = 50;
        }
        else {
            if (copper[i]) {
                if (radii[i] > 90)
                    values[i] = 500;
                else
                    values[i] = 10;
            }
            else {
                if (radii[i] <= oneYenRadius * 1.07)
                    values[i] = 1;
                else
                    values[i] = 100;
            }
        }

        total += values[i];

        circle(
            img,
            centers[i],
            radii[i],
            CV_RGB(255, 0, 0),
            3,
            LINE_AA
        );

        putText(
            img,
            format("%d yen", values[i]),
            Point(centers[i].x - 35, centers[i].y),
            FONT_HERSHEY_SIMPLEX,
            0.6,
            CV_RGB(0, 0, 0),
            2
        );

        printf(
            "%d: r=%d, S=%.2f, R-B=%.2f, hole=%d, value=%d\n",
            i + 1,
            radii[i],
            meanS[i],
            colorDifference[i],
            holes[i],
            values[i]
        );
    }

    putText(
        img,
        format("Total=%d yen", total),
        Point(10, 35),
        FONT_HERSHEY_SIMPLEX,
        0.9,
        CV_RGB(0, 0, 0),
        2
    );

    // 結果表示・ファイル出力
    imshow("result", img);
    imwrite(output, img);
    waitKey(0);

    return 0;
}
