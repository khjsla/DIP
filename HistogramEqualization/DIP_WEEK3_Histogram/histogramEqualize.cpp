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
      int const height = cvRound( binVal * hist_height / max_val);
      cv::line
         (hist_image
         , cv::Point(b, hist_height - height), cv::Point(b, hist_height)
         , cv::Scalar::all(255)
         );
   }
   cv::imshow(name, hist_image);
}

int main(int, char**){
    Mat src, dst, src_, dst_, EH;
    src = imread("x-ray.png");
    src_ = imread("x-ray.png");

    cvtColor(src, dst, COLOR_RGB2GRAY);
    cvtColor(src_, dst_, COLOR_RGB2GRAY);

    equalizeHist(dst, EH);

    show_histogram("hi", dst_);
    show_histogram("bye", EH);

    imshow("1", dst_);
    imshow("2", EH);

    waitKey();
    return 0;
}