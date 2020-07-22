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
        int const height = cvRound(binVal * hist_height / max_val);
        cv::line
        (hist_image
            , cv::Point(b, hist_height - height), cv::Point(b, hist_height)
            , cv::Scalar::all(255)
            );
    }
    cv::imshow(name, hist_image);
}

int main(int, char**)
{
    VideoCapture cap(0); //open default cam
    if (!cap.isOpened()) {
        return -1;
    }

    namedWindow("vid", 1);

    while (1) {
        Mat frame_s, frame_d, eh;
        cap >> frame_s;

        cvtColor(frame_s, frame_d, cv::COLOR_RGB2GRAY);
        cv::equalizeHist(frame_d, eh); //여기에서 계속 에러발생.

        show_histogram("inputIMG", frame_d);
        show_histogram("outputIMG", eh);

        imshow("video_origin", frame_d);
        imshow("video_processed", eh);

        if (waitKey(30) == 'c') {
            break;
        }
    }

    return 0;
}