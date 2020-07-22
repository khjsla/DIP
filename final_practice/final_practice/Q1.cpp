//#include "opencv2/opencv.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main(){
//	Mat3b img = imread("Q1_input/Nikon_Single_molecule_contest_winner.jpg", 1);
//	resize(img, img, Size(320, 240));
//	//이미지 크기
//	Mat3b hsv;
//	cvtColor(img, hsv, COLOR_BGR2HSV);
//
//	/* DETECT COLOR */
//	Mat1b mask1, mask2;
//	inRange(hsv, Scalar(170, 70, 50), Scalar(180, 255, 255), mask1);
//	//170-180 RED
//	inRange(hsv, Scalar(38, 70, 50), Scalar(75, 255, 255), mask2);
//	//38-75 GREEN
//	imshow("Original", img);
//	imshow("RedDetect", mask1);
//	imshow("GreenDetect", mask2);
//
//	/* DETECT HUE, SATURATION, INTENSITY */
//	Mat1b hue(img.rows, img.cols), saturation(img.rows, img.cols), intensity(img.rows, img.cols);
//
//	for (int i = 0; i < hsv.rows; i++) {
//		for (int j = 0; j < hsv.cols; j++) {
//			Vec3b pixel = hsv.ptr<Vec3b>(i)[j];
//			hue.at<uchar>(i, j) = pixel.val[0];
//			saturation.at<uchar>(i, j) = pixel.val[1];
//			intensity.at<uchar>(i, j) = pixel.val[2];
//		}
//	}
//	imshow("Hue", hue);
//	imshow("Saturation", saturation);
//	imshow("Intensity", intensity);
//
//	waitKey();
//	return 0;
//}
