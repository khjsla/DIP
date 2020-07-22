#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace cv;
using namespace std;

//kernel을 만들어서 vertical과 horizental 을 추출해낸다
void kernel(Mat src, Mat dst, vector <vector <float> > Kernel) //가로세로 이므로 
{
    float sum;
    for (int y = 3 / 2; y < src.rows - 3 / 2; y++) {
        for (int x = 3 / 2; x < src.cols - 3 / 2; x++) {
            sum = 0;
            for (int i = -3 / 2; i <= 3 / 2; i++) {
                for (int j = -3 / 2; j <= 3 / 2; j++) {
                    sum = sum + Kernel[j + 3 / 2][i + 3 / 2] * src.at<uchar>(y - j, x - i);
                }
            }
            dst.at<uchar>(y, x) = sum;
        }
    }
}

int main()
{
    Mat src, finalH, finalV;

    src = imread("Q1.jpg", IMREAD_GRAYSCALE); //gray스케일로 안받으면 안됨
    imshow("r", src);

    medianBlur(src, src, 7); //
    vector < vector <float> > KH(3, vector <float>(3));
    vector < vector <float> > KV(3, vector <float>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 3 / 2)
                KH[i][j] = 2.0;
            else
                KH[i][j] = -1.0;
            if (j == 3 / 2)
                KV[i][j] = 2.0;
            else
                KV[i][j] = -1.0;
        }
    }

    finalH = src.clone();
    finalV = src.clone();
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            finalH.at<uchar>(y, x) = 0.0;
            finalV.at<uchar>(y, x) = 0.0;
        }
    }

    kernel(src, finalH, KH);
    kernel(src, finalV, KV);

    imshow("Hor", finalH);
    imshow("Ver", finalV);

    waitKey(0);
    return 0;;
}

