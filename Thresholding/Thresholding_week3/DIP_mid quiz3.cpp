////  DFT Low and High Pass Filters ////
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/////////// Setting Position //////////////

void ChangeSignOddPositionInXY(Mat& m)
{
	int x, y;
	float fValue;
	for (y = 0; y < m.rows; y++)
		for (x = 0; x < m.cols; x++)
		{
			fValue = m.at<float>(y, x);
			//		if((x+y)%2==1 && fValue != 0)
			if ((x + y) % 2 == 1) // odd number
				m.at<float>(y, x) = -fValue;
		}
}

/////////////// Gaussian LowPassFilter function //////////////////

int GaussianLowPassFilter(Mat srcM, Mat dstM, double cutOff)
{
	int u, v;
	double D; //distance
	double H;
	double centerU = srcM.cols / 2;
	double centerV = srcM.rows / 2;
	Vec2d cmplxValue;

	//Gaussian LowPass Filter
	for (v = 0; v < srcM.rows; v++)
	{
		for (u = 0; u < srcM.cols; u++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));
			H = exp(-D * D / (2.0 * cutOff * cutOff)); //ch4. 28p 적용된 식 

			cmplxValue = srcM.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			dstM.at<Vec2f>(v, u) = cmplxValue;
		}
	}
	return 0;
}


/////////////// Butterworth HighPassFilter function //////////////////

int ButterworthHighPassFilter(Mat srcM, Mat dstM, double cutOff, int n = 2)
{
	int u, v;
	double D; //distance
	double H;
	double centerU = srcM.cols / 2;
	double centerV = srcM.rows / 2;
	Vec2d cmplxValue;

	//Butterworth High Pass Filter
	for (v = 0; v < srcM.rows; v++)
	{
		for (u = 0; u < srcM.cols; u++)
		{
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));
			H = 1.0 / (1.0 + pow(cutOff / D, 2 * n));

			cmplxValue = srcM.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			dstM.at<Vec2f>(v, u) = cmplxValue;
		}
	}
	return 0;
}

int main()
{
	Mat srcImage = imread("Q2.png", IMREAD_GRAYSCALE); //gray scale로 읽기
	imshow("original", srcImage);

	Mat fImage, Fimage2;
	srcImage.convertTo(fImage, CV_32F); //int rtype is CV_32F 
	ChangeSignOddPositionInXY(fImage);

	//DFT
	Mat gau, gau_, but, but_;
	Mat dft_org, dft_org2;
	Mat dstImageG, dstImageB; //과제용 Mat변수 하나추가
	double D0 = 30.0;
	
	dft(fImage, dft_org, DFT_COMPLEX_OUTPUT);

	//Cutoff = 5 
	dft_org.copyTo(gau);

	GaussianLowPassFilter(gau, gau, D0);

	dft(gau, gau_, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	ChangeSignOddPositionInXY(gau_);

	gau_.convertTo(dstImageG, CV_8U);
	normalize(dstImageG, dstImageG, 0, 255, NORM_MINMAX, CV_8U);
	imshow("dstImage gau", dstImageG);
	//ok
	/////////////////////////////////////////////////////////////////////////////////////

	/////////High Pass Filters/////////
	dstImageG.convertTo(Fimage2, CV_32F); //int rtype is CV_32F 
	ChangeSignOddPositionInXY(Fimage2);
	dft(Fimage2, dft_org2, DFT_COMPLEX_OUTPUT);
	dft_org2.copyTo(but);

	ButterworthHighPassFilter(but, but, D0, 4);

	dft(but, but_, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	ChangeSignOddPositionInXY(but_);

	but_.convertTo(dstImageB, CV_8U);
	normalize(dstImageB, dstImageB, 0, 255, NORM_MINMAX, CV_8U);
	imshow("dstImage but", dstImageB);
	
	waitKey();
	return 0;
}


/// Play with the threhold values and choose the best one for all the five methods