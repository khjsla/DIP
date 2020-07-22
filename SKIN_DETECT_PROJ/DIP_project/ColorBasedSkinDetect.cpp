#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

#include <iostream>

using namespace cv;
using namespace std;

//imagewatch로 RGB BGR 비교
//*** inRange *** (R ,G ,B) min , (R,G,B) max
//.txt.에 R,G,B 추출하는 inrange값 있음
//그 R1 값이랑 inRange값 바꿔보기

bool R1(int R, int G, int B) { //RGB 피부색 검출 고유값 //빨간색이 너무 많이 잡힘
    bool e1 = (R > 95) && (G > 40) && (B > 20) && ((max(R, max(G, B)) - min(R, min(G, B))) > 15) && (abs(R - G) > 15) && (R > G) && (R > B);
    bool e2 = (R > 220) && (G > 210) && (B > 170) && (abs(R - G) <= 15) && (R > B) && (G > B);
    bool e1_ = (R > 45) && (G > 34) && (B > 30) && (G < 206) && (B < 180);
    bool e1__ = (R < 219) || (R > 227) || (G < 107) || (G > 110) || (B < 166) || (B > 180);
    return ((e1 || e2) && (e1_) /*&& (e1__)*/); //e1 이거나 e2면 피부색임
}
//abs(R - G)  = brown

bool R2(float Y, float Cr, float Cb) { //YCrCb 피부색
    bool e3 = Cr <= 1.5862 * Cb + 20;
    bool e4 = Cr >= 0.3448 * Cb + 76.2069;
    bool e5 = Cr >= -4.5652 * Cb + 234.5652;
    bool e6 = Cr <= -1.15 * Cb + 301.75;
    bool e7 = Cr <= -2.2857 * Cb + 432.85; //default
    //new value
    bool e8 = Cr > 135;
    bool e8_ = Cr > 133;
    bool e9 = Cb > 85; //85
    bool e9_ = Cb > 77; //85
    bool e10 = Y > 80; //여기까지는 논문
    bool e11 = Cr < 173;
    bool e11_ = Cr < 180;
    bool e12 = Cb < 127;

    return e3 && e4 && e5 && e6 && e7 && e8 && e9 && e10 && e11 && e12;
}
//YCrCb 색 영역으로 살색을 검출 할 경우 조명에 보다 강해지는 효과가 있다
//살색은 Cb이미지의 경우 77~127 or 80 - 120 사이 Cr이미지는 (or 137 - 177)133~173 사이일 경우 살색이다.
//Y > 80
//85 < Cb < 135
//135 < Cr < 180,
//Where Y, Cb, Cr = [0, 255]

//+ 190 < Cb + 0.6Cr < 215

/*
Y = (299*R + 587*G + 114*B)/1000
Cb = 0.5643*(B - Y) + 128
Cr = 0.7132*(R - Y) + 128
R = (1000*Y + 1402*(Cr-128))/1000
G = (1000*Y - 714*(Cr-128) - 334(Cb-128))/1000
B = (1000*Y + 1772*(Cb-128))/1000
*/

//yellow = (255,255,0)

bool R3(float H, float S, float V) { //HSI 피부색
    bool e1212 = (H < 30) || (H > 230); //default
    bool e12_ = (((H < 30)) || ((S > 11) && (S < 84.39))) && (H > 8); 
    //white = Hue = 0 !
    return (e12_); //빨간색이 너무 많음
    //(H < 30) || (H > 230) default
}

Mat GetSkin(Mat const& src) {
    // allocate the result matrix
    Mat dst = src.clone();

    Vec3b cwhite = Vec3b::all(255);
    Vec3b cblack = Vec3b::all(0);

    Mat src_ycrcb, src_hsv;

    // OpenCV scales the YCrCb components, so that they
    // cover the whole value range of [0,255], so there's
    // no need to scale the values:
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

    // OpenCV scales the Hue Channel to [0,180] for
    // 8bit images, so make sure we are operating on
    // the full spectrum from [0,360] by using floating
    // point precision:
    src.convertTo(src_hsv, CV_32FC3);

    cvtColor(src_hsv, src_hsv, COLOR_BGR2HSV);

    // Now scale the values between [0,255]:
    normalize(src_hsv, src_hsv, 0.0, 255.0, NORM_MINMAX, CV_32FC3);

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) { //모두 확인

            Vec3b pix_bgr = src.ptr<Vec3b>(i)[j];
            int B = pix_bgr.val[0];
            int G = pix_bgr.val[1];
            int R = pix_bgr.val[2];
            // apply rgb rule
            bool a = R1(R, G, B);

            Vec3b pix_ycrcb = src_ycrcb.ptr<Vec3b>(i)[j];
            int Y = pix_ycrcb.val[0];
            int Cr = pix_ycrcb.val[1];
            int Cb = pix_ycrcb.val[2];
            // apply ycrcb rule
            bool b = R2(Y, Cr, Cb);

            Vec3f pix_hsv = src_hsv.ptr<Vec3f>(i)[j];
            float H = pix_hsv.val[0];
            float S = pix_hsv.val[1];
            float V = pix_hsv.val[2];
            // apply hsv rule
            bool c = R3(H, S, V);

            if (!(c /*&& b && c*/)) {
                dst.ptr<Vec3b>(i)[j] = cblack;
            } //만약에 a,b,c 에 해당하는 색이 아니면, 검은색으로만들어버려
            else {
               dst.ptr<Vec3b>(i)[j] = cwhite; //binary로
            }
        }
    }
    return dst;
}

////////////////SKIN DETECT WITH COLORBASED

int main() {
    // Get filename to the source image:
    Mat image = imread("bc.jpg", 1);
    Mat image_; //for size

    Mat image__;
    cv::resize(image, image__, cv::Size(image.cols * 0.15, image.rows * 0.15), 0, 0);
    //아이폰으로 사진 찍을경우 사진이 너무 크므로 resize해줍니다.

    //Blur for reduce noise
    GaussianBlur(image__, image_, Size(11, 11), 0, 0); //0,0 height and width maybe?

    Mat skin = GetSkin(image_); //피부색 검출

    // Show the results:
    namedWindow("original");
    namedWindow("skin");

    imshow("original", image__);
    imshow("skin", skin);

    waitKey(0);
    return 0;
}

////////////////SKIN DETECT WITH TRAFFIC LIGHT DETECTION

//Use the below program IF YOU DO NOT HAVE ACCESS TO A WEBCAM
//
//int main()
//{
//    Mat3b bgr = imread("easy.jpg", IMREAD_COLOR);
//    //Mat3b hsv;
//    Mat3b rgb;
//    //cvtColor(bgr, hsv, COLOR_BGR2HSV);
//    //cvtColor(bgr, rgb, COLOR_BGR2RGB);
//
//    Mat3b rgb_;
//    GaussianBlur(bgr, rgb_, Size(3, 3), 0, 0); //0,0 height and width maybe?
//
//    Mat1b mask1;
//    inRange(rgb_, Scalar(180, 138, 120), Scalar(255, 206, 180), mask1);
//    imshow("Original", rgb_);
//    imshow("SkinDetect", mask1);
//
//    waitKey();
//    return 0;
//}