//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/objdetect.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//double ticks = getTickFrequency()*10e6;
//int64 t0;
//
//int main(int argc, char** argv){
//	// capture from web camera init
//	VideoCapture cap(0);
//	cap.open(0);
//
//	Mat img;
//
//	// Below mention YOUR cascade classifier instead of haarcascade_frontalface_alt2.xml file
//	CascadeClassifier face_cascade;
//
//	//face_cascade.load("Add the path from opencv sources/haarcascade_frontalface_alt2.xml");
//	face_cascade.load("xml/lbpcascade_frontalface.xml");
//
//
//	for (;;)
//	{
//
//		// Image from camera to Mat
//
//		cap >> img;
//
//		// obtain input image from source
//		cap.retrieve(img, CAP_OPENNI_BGR_IMAGE);
//		//CV_CAP_OPENNI_BGR_IMAGE 에러난다.
//		//Try cv2.CAP_OPENNI_BGR_IMAGE instead of cv2.CV_CAP_OPENNI_BGR_IMAGE
//
//		// Just resize input image if you want
//		resize(img, img, Size(1000, 640));
//
//		// Container of faces
//		vector<Rect> faces;
//
//		t0 = getTickCount();
//		// Detect faces
//		face_cascade.detectMultiScale(img, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(140, 140));
//		//You can use an alternative cv2.CASCADE_SCALE_IMAGE
//		t0 = getTickCount() - t0;
//		printf("Processing Time : %.3f sec\n", (double)t0 / ticks);
//
//		// To draw rectangles around detected faces
//		for (unsigned i = 0; i<faces.size(); i++)
//		rectangle(img,faces[i], Scalar(255, 0, 0), 2, 1);
//
//
//		imshow("face", img);
//		int key2 = waitKey(20);
//
//	}
//	return 0;
//}
//
//
//
//
