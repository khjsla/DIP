//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace cv;
//
//using std::cout;
//using std::endl;
//
///* COLOR BASED DETECTION */
//bool R1(int R, int G, int B) {
//	bool e1 = (R > 80) && (G > 25) && (B > 5) && ((max(R, max(G, B)) - min(R, min(G, B))) > 15) && (abs(R - G) > 15) && (R > G) && (R > B);
//	bool e2 = (R > 220) && (G > 210) && (B > 170) && (abs(R - G) <= 15) && (R > B) && (G > B);
//	return (e1 || e2);
//}
//
//bool R2(float Y, float Cr, float Cb) {
//	bool e3 = Cr <= 1.5862*Cb + 20;
//	bool e4 = Cr >= 0.3448*Cb + 76.2069;
//	bool e5 = Cr >= -4.5652*Cb + 234.5652;
//	bool e6 = Cr <= -1.15*Cb + 301.75;
//	bool e7 = Cr <= -2.2857*Cb + 432.85;
//	return e3 && e4 && e5 && e6 && e7;
//}
//
//bool R3(float H, float S, float V) {
//	return (H < 30) || (H > 225);
//}
//
//Mat GetSkin(Mat const &src) {
//	Mat dst = src.clone();
//
//	Vec3b cwhite = Vec3b::all(255);
//	Vec3b cblack = Vec3b::all(0);
//
//	Mat src_ycrcb, src_hsv;
//	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
//	src.convertTo(src_hsv, CV_32FC3);
//	cvtColor(src_hsv, src_hsv, COLOR_BGR2HSV);
//	// Now scale the values between [0,255]:
//	normalize(src_hsv, src_hsv, 0.0, 255.0, NORM_MINMAX, CV_32FC3);
//
//	for (int i = 0; i < src.rows; i++) {
//		for (int j = 0; j < src.cols; j++) {
//
//			Vec3b pix_bgr = src.ptr<Vec3b>(i)[j];
//			int B = pix_bgr.val[0];
//			int G = pix_bgr.val[1];
//			int R = pix_bgr.val[2];
//			// apply rgb rule
//			bool a = R1(R, G, B);
//
//			Vec3b pix_ycrcb = src_ycrcb.ptr<Vec3b>(i)[j];
//			int Y = pix_ycrcb.val[0];
//			int Cr = pix_ycrcb.val[1];
//			int Cb = pix_ycrcb.val[2];
//			// apply ycrcb rule
//			bool b = R2(Y, Cr, Cb);
//
//			Vec3f pix_hsv = src_hsv.ptr<Vec3f>(i)[j];
//			float H = pix_hsv.val[0];
//			float S = pix_hsv.val[1];
//			float V = pix_hsv.val[2];
//			// apply hsv rule
//			bool c = R3(H, S, V);
//
//			if (!(a&&b&&c))
//				dst.ptr<Vec3b>(i)[j] = cblack; 
//			//탐색결과, 얼굴이 아니면 black으로 
//			else
//				dst.ptr<Vec3b>(i)[j] = cwhite;
//			//얼굴이면, white로
//		}
//	}
//	return dst;
//}
//
//int main() {
//	/* MY WEB CAM */
//	VideoCapture cap(0);
//	cap.open(0);
//
//	Mat img;
//
//	for (;;)	{
//		// Image from camera to Mat
//		cap >> img;
//
//		// obtain input image from source
//		cap.retrieve(img, CAP_OPENNI_BGR_IMAGE);
//
//		// Just resize input image if you want
//		resize(img, img, Size(1000, 640));
//
//		Mat skin = GetSkin(img);
//		dilate(skin, skin, Mat(Size(7, 7), CV_32F), Point(-1, -1), 6); 
//		//맨뒤 값 3해도 오케
//
//		erode(skin, skin, Mat(Size(7, 7), CV_32F), Point(-1, -1), 3);
//		//openning (erode 후 dilate) 는 너무 많이 bluring되어 피부색이 잘 탐지되지 않았습니다.
//		//closing (위의 반대) 방법으로 하니 피부가 잘 탐지되었습니다. (위의 경우보다)
//		//따라서 closing 선택 - 전반적 이미지 깨끗
//		//+ 오프닝은 작은 노이즈를 없애는데 주로 사용됩니다.
//
//		imshow("face", skin);
//		int key2 = waitKey(10);
//	}
//	return 0;
//}
