////  DFT Low and High Pass Filters ////
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/////////// Setting Position //////////////

void ChangeSignOddPositionInXY(Mat &m)
{
	int x, y;
	float fValue;
	for (y = 0; y<m.rows; y++)
		for (x = 0; x<m.cols; x++)
		{
			fValue = m.at<float>(y, x);
			//		if((x+y)%2==1 && fValue != 0)
			if ((x + y) % 2 == 1) // odd number
				m.at<float>(y, x) = -fValue;
		}
}

/////////////// Ideal LowPassFilter function //////////////////

int IdealLowPassFilter(Mat srcM, Mat dstM, double cutOff)
{
	int u, v;
	double D; //distance
	double H;
	double centerU = srcM.cols / 2;
	double centerV = srcM.rows / 2;
	Vec2d cmplxValue;

	//Ideal Low Filter
	for (v = 0; v < srcM.rows; v++)
	{
		for (u = 0; u < srcM.cols; u++)
		{
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)* (v - centerV));
			if (D <= cutOff)
				H = 1.0;
			else
				H = 0.0;
			cmplxValue = srcM.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			dstM.at<Vec2f>(v, u) = cmplxValue;
		}
	}
	return 0;
}

////////////////////// Butterworth LowPassFilter function /////////////////////////

int ButterworthLowPassFilter(Mat srcM, Mat dstM, double cutOff, int n = 2)
{
	int u, v;
	double D; //distance
	double H;
	double centerU = srcM.cols / 2;
	double centerV = srcM.rows / 2;
	Vec2d cmplxValue;

	//Butterworth Low Pass Filter
	for (v = 0; v < srcM.rows; v++)
	{
		for (u = 0; u < srcM.cols; u++)
		{
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)* (v - centerV));
			H = 1.0 / (1.0 + pow(D / cutOff, 2 * n)); //fourier에서 말했던 cut off - 0이랑 가까우면 narrow freq 

			cmplxValue = srcM.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			dstM.at<Vec2f>(v, u) = cmplxValue;
		}
	}
	return 0;
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
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)* (v - centerV));
			H = exp(-D* D / (2.0* cutOff*cutOff)); //ch4. 28p 적용된 식 

			cmplxValue = srcM.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			dstM.at<Vec2f>(v, u) = cmplxValue;
		}
	}
	return 0;
}

/////////////// Ideal HighPassFilter function //////////////////

int IdealHighPassFilter(Mat srcM, Mat dstM, double cutOff)
{
	int u, v;
	double D; //distance
	double H;
	double centerU = srcM.cols / 2;
	double centerV = srcM.rows / 2;
	Vec2d cmplxValue;

	//Ideal High Filter
	for (v = 0; v < srcM.rows; v++)
	{
		for (u = 0; u < srcM.cols; u++)
		{
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)* (v - centerV));
			if (D <= cutOff)
				H = 0.0;
			else
				H = 1.0;
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
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)* (v - centerV));
			H = 1.0 / (1.0 + pow(cutOff / D, 2 * n));

			cmplxValue = srcM.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			dstM.at<Vec2f>(v, u) = cmplxValue;
		}
	}
	return 0;
}

/////////////// Gaussian HighPassFilter function //////////////////

int GaussianHighPassFilter(Mat srcM, Mat dstM, double cutOff)
{
	int u, v;
	double D; //distance
	double H;
	double centerU = srcM.cols / 2;
	double centerV = srcM.rows / 2;
	Vec2d cmplxValue;

	//Gaussian HighPass Filter
	for (v = 0; v < srcM.rows; v++)
	{
		for (u = 0; u < srcM.cols; u++)
		{
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)* (v - centerV));
			H = 1 - exp(-D* D / (2.0* cutOff*cutOff));

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
	Mat srcImage = imread("image.jpg", IMREAD_GRAYSCALE); //gray scale로 읽기
	Mat fImage;
	srcImage.convertTo(fImage, CV_32F); //int rtype is CV_32F 
	ChangeSignOddPositionInXY(fImage);

	//DFT
	Mat idftMat, dftMat, dftMat_org;
	Mat dstImage5, dstImage30, dstImage80, dstImage200, dstImageHyunji; //과제용 Mat변수 하나추가
	dft(fImage, dftMat_org, DFT_COMPLEX_OUTPUT);

	//Cutoff = 5 
	dftMat_org.copyTo(dftMat);
	double D0 = 5.0;

	/////////Low Pass Filters/////////

	//IdealLowPassFilter(dftMat, dftMat, D0);
	ButterworthLowPassFilter(dftMat, dftMat, D0, 2);
	//GaussianLowPassFilter(dftMat, dftMat, D0);
	//3para are almost same.

	/////////High Pass Filters/////////

	//IdealHighPassFilter(dftMat, dftMat, D0);
	//ButterworthHighPassFilter(dftMat, dftMat, D0, 2);
	//GaussianHighPassFilter(dftMat, dftMat, D0);

	dft(dftMat, idftMat, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	ChangeSignOddPositionInXY(idftMat);

	idftMat.convertTo(dstImage5, CV_8U);
	//normalize(magF, dstImage, 0, 255, NORM_MINMAX, CV_8U);
	imshow("dstImage D0=5", dstImage5);

	//Cutoff = 30 
	dftMat_org.copyTo(dftMat);
	double D1 = 30.0; //30, 80, 200

	/////////Low Pass Filters/////////

	//IdealLowPassFilter(dftMat, dftMat, D1);
	ButterworthLowPassFilter(dftMat, dftMat, D1, 2);
	//GaussianLowPassFilter(dftMat, dftMat, D1);

	/////////High Pass Filters/////////

	//IdealHighPassFilter(dftMat, dftMat, D1);
	//ButterworthHighPassFilter(dftMat, dftMat, D1, 2);
	//GaussianHighPassFilter(dftMat, dftMat, D1);

	dft(dftMat, idftMat, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	ChangeSignOddPositionInXY(idftMat);

	idftMat.convertTo(dstImage30, CV_8U);
	//normalize(magF, dstImage, 0, 255, NORM_MINMAX, CV_8U);
	imshow("dstImage D1=30", dstImage30);

	//Cutoff = 80
	dftMat_org.copyTo(dftMat);
	double D2 = 80.0; //30, 80, 200

	/////////Low Pass Filters/////////

	//IdealLowPassFilter(dftMat, dftMat, D2);
	ButterworthLowPassFilter(dftMat, dftMat, D2, 2);
	//GaussianLowPassFilter(dftMat, dftMat, D2);

	/////////High Pass Filters/////////

	//IdealHighPassFilter(dftMat, dftMat, D2);
	//ButterworthHighPassFilter(dftMat, dftMat, D2, 2);
	//GaussianHighPassFilter(dftMat, dftMat, D2);

	dft(dftMat, idftMat, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	ChangeSignOddPositionInXY(idftMat);

	idftMat.convertTo(dstImage80, CV_8U);
	//normalize(magF, dstImage, 0, 255, NORM_MINMAX, CV_8U);
	imshow("dstImage D2=80", dstImage80);

	//Cutoff = 200 
	dftMat_org.copyTo(dftMat);
	double D3 = 200.0; //30, 80, 200

	/////////Low Pass Filters/////////

	//IdealLowPassFilter(dftMat, dftMat, D3);
	ButterworthLowPassFilter(dftMat, dftMat, D3, 2);
	//GaussianLowPassFilter(dftMat, dftMat, D3);

	/////////High Pass Filters/////////

	//IdealHighPassFilter(dftMat, dftMat, D3);
	//ButterworthHighPassFilter(dftMat, dftMat, D3, 2);
	//GaussianHighPassFilter(dftMat, dftMat, D3);

	dft(dftMat, idftMat, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	ChangeSignOddPositionInXY(idftMat);

	idftMat.convertTo(dstImage200, CV_8U);
	//normalize(magF, dstImage, 0, 255, NORM_MINMAX, CV_8U);
	imshow("dstImage D3=200", dstImage200);

	/*----------------------------------------------------assignment------------------------------------------------------------*/

	//Cutoff = 16 
	dftMat_org.copyTo(dftMat);
	double D4 = 16.0; 

	/////////Low Pass Filters/////////
	//IdealLowPassFilter(dftMat, dftMat, D4);
	ButterworthLowPassFilter(dftMat, dftMat, D4, 4);
	//GaussianLowPassFilter(dftMat, dftMat, D4);

	/////////High Pass Filters/////////

	//IdealHighPassFilter(dftMat, dftMat, D4);
	//ButterworthHighPassFilter(dftMat, dftMat, D4, 2);
	//GaussianHighPassFilter(dftMat, dftMat, D4);

	dft(dftMat, idftMat, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT); //discrete Fourier Transform
	ChangeSignOddPositionInXY(idftMat); //odd-음수부분의 X,Y 부분 변경해주기

	idftMat.convertTo(dstImageHyunji, CV_8U); // CV_8U ; 8-bit unsigned integer: uchar ( 0..255 )

	//normalize(magF, dstImage, 0, 255, NORM_MINMAX, CV_8U); 
	//3 - 변환방식이 NORM_MINMAX일떄 변환 최소값, 4-변환 최대값, 5-변환방식

	imshow("dstImage D4=16 for assignment", dstImageHyunji);

	waitKey();
	return 0;
}

//ask do 
//#3: implement the butterworth filter with cut-off frequency 16 and make sure to have the 4 first tampered mooth tails (n) 
//and apply the high component to it
//(ch4. 25p func)
//you use just 164line - butter function
//change function in main() 219line
//
//BW high pass filter - cutoff- | D0 =16 | n = 4| with image.jpg and also with your web input
//try to implement this one(upper)
//
//#3 is have to be submitted on iclass
//make a new program and do that
