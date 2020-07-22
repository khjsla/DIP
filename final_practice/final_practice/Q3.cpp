#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <ctime> //시간 재기

using namespace cv;
using namespace std;

double ticks = getTickFrequency()*10e6;
clock_t t0;

int main(int argc, char** argv)
{
	CascadeClassifier face_cascade_haar, face_cascade_lbp;
	face_cascade_haar.load("xml/cascade.xml");
	face_cascade_lbp.load("xml/lbpcascade_frontalface.xml");

	Mat img = imread("faces_linear.jpg");
	//face_linear or face_rotated ( good or bad )
	resize(img, img, Size(1000, 640));

	// Container of faces
	vector<Rect> faces;

	t0 = getTickCount();
	// Detect faces
	face_cascade_haar.detectMultiScale(img, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));
	//맨뒤 size 값 작을수록 더 많은 얼굴을 detect합니다.
	//대신 시간이 더 오래걸립니다.
	t0 = getTickCount() - t0;
	printf("HAAR Processing Time : %.3f sec\n", (double)t0 / CLOCKS_PER_SEC);

	// To draw rectangles around detected faces
	for (unsigned i = 0; i < faces.size(); i++)
		rectangle(img, faces[i], Scalar(255, 0, 0), 2, 1);

	imshow("face_HAAR", img);


	t0 = getTickCount();
	// Detect faces
	face_cascade_lbp.detectMultiScale(img, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(10, 10));
	//맨뒤 size 값 작을수록 더 많은 얼굴을 detect합니다.
	//대신 시간이 더 오래걸립니다.
	t0 = getTickCount() - t0;
	printf("LBP Processing Time : %.3f sec\n", (double)t0 / CLOCKS_PER_SEC);

	// To draw rectangles around detected faces
	for (unsigned i = 0; i < faces.size(); i++)
		rectangle(img, faces[i], Scalar(255, 0, 0), 2, 1);

	//imshow("face_LBP", img);
	waitKey(0);
	return 0;
}
