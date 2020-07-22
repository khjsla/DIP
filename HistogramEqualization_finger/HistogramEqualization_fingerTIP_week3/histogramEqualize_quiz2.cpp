#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// FUNCTION TO DISPLAY HISTOGRAMS //

void show_histogram(std::string const& name, cv::Mat1b const& image)
{
	// Set histogram bins count
	int bins = 256;
	int histSize[] = { bins };
	// Set ranges for histogram bins
	float lranges[] = { 0, 256 };
	const float* ranges[] = { lranges };
	// create matrix for histogram
	cv::Mat hist;
	int channels[] = { 0 };

	// create matrix for histogram visualization
	int const hist_height = 256;
	cv::Mat3b hist_image = cv::Mat3b::zeros(hist_height, bins);

	cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

	double max_val = 0;
	minMaxLoc(hist, 0, &max_val);

	// visualize each bin
	for (int b = 0; b < bins; b++) {
		float const binVal = hist.at<float>(b);
		int   const height = cvRound(binVal*hist_height / max_val);
		cv::line
			(hist_image
			, cv::Point(b, hist_height - height), cv::Point(b, hist_height)
			, cv::Scalar::all(255)
			);
	}
	cv::imshow(name, hist_image);
}

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
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));
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
			D = sqrt((u - centerU) * (u - centerU) + (v - centerV) * (v - centerV));
			H = 1 - exp(-D * D / (2.0 * cutOff * cutOff));

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
	//finger, 내가 직접 해야함
	Mat src, dst, src_, dst_, EH, EMP, EMP_, final, final_;
	src = imread("Q2.png"); // "medium_quality_FP.jpg" // "worst_quality_FP.JPG"

	imshow("original", src);

	cvtColor(src, dst, cv::COLOR_RGB2GRAY);

	show_histogram("2 origin", src);

	cv::equalizeHist(dst, EH);

	show_histogram("2 histo", EH);

	imshow("histo picture", EH);

	//and ,또 EH를 sharpening 해야한다.
	//high boost . higf frequency,,
	//EH.convertTo(src_, CV_32F); //int rtype is CV_32F 
	//ChangeSignOddPositionInXY(src_);
	//
	//dft(src_, dst_, DFT_COMPLEX_OUTPUT);
	//dst_.copyTo(EMP);
	//double D0 = 90;

	//IdealHighPassFilter(EMP, EMP, D0);
	////GaussianHighPassFilter(EMP, EMP, D0);

	//dft(EMP, EMP_, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);
	//ChangeSignOddPositionInXY(EMP_);

	//EMP_.convertTo(final, CV_8U);
	//normalize(final, final_, 0, 255, NORM_MINMAX, CV_8U);

	threshold(EH, final, 30, 255, THRESH_BINARY);

	imshow("emp img", final);

	waitKey();

	return 0;
}
//우선 보류