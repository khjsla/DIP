#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

int main()
{
    VideoCapture capture(samples::findFile("vtest.avi"));
    if (!capture.isOpened()) {
        //error in opening the video input
        cerr << "Unable to open file!" << endl;
        return 0;
    }
    Mat frame1, prvs;
    //capture >> frame1;
    frame1 = imread("a.png", 1);
    cvtColor(frame1, prvs, COLOR_BGR2GRAY);
    while (true) {
        Mat frame2, next;
       // capture >> frame2;
        frame2 = imread("b.png", 1);
        if (frame2.empty())
            break;
        cvtColor(frame2, next, COLOR_BGR2GRAY);
        Mat flow(prvs.size(), CV_32FC2);
        calcOpticalFlowFarneback(prvs, next, flow, 0.2, 3, 15, 3, 5, 1.2, 0);
        // 3. pyramid scale ; parameter, specifying the image scale (<1) to build pyramids for each image; 
        // pyr_scale=0.5 means a classical pyramid, where each next layer is twice smaller than the previous one.
        // 4. levels ; number of pyramid layers including the initial image; levels=1 means that 
        // no extra layers are created and only the original images are used
        // 5. window size ; averaging window size; larger values increase the algorithm robustness 
        // to image noise and give more chances for fast motion detection, but yield more blurred motion field.
        
        // visualization
        Mat flow_parts[2];
        split(flow, flow_parts);
        Mat magnitude, angle, magn_norm;
        cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
        normalize(magnitude, magn_norm, 0.0f, 1.0f, NORM_MINMAX);
        angle *= ((1.f / 360.f) * (180.f / 255.f));
      
        //build hsv image
        Mat _hsv[3], hsv, hsv8, bgr, gray;
        _hsv[0] = angle;
        _hsv[1] = Mat::ones(angle.size(), CV_32F);
        _hsv[2] = magn_norm;
        merge(_hsv, 3, hsv);
        hsv.convertTo(hsv8, CV_8U, 255.0);
        cvtColor(hsv8, bgr, COLOR_HSV2BGR); 
        cvtColor(bgr, gray, COLOR_BGR2GRAY); //for확인, rgb to gray
        //equalizeHist(gray, gray); //대비높이기.?
        imshow("frame2", gray);
        int keyboard = waitKey(100); //10초동안 멈춤
        if (keyboard == 'q' || keyboard == 27)
            break;
        //prvs = next;
    }
}