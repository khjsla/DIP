#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

int main(int argc, char** argv)
{
	namedWindow("Original", CV_WINDOW_AUTOSIZE);

	// Load the source image
	Mat src = imread("Original.png", 1);

	// Create a destination Mat object
	Mat dst, dst1;
	//for laplace
	Mat laplace;
	//for bilateralfilter
	Mat bilateral;

	// display the source image
	imshow("Original", src);

	for (int i = 1; i<21; i = i + 2) //51 -> 21
	{
		// smooth the image in the "src" and save it to "dst"
		// blur(src, dst, Size(i,i));

		// Gaussian smoothing
		GaussianBlur( src, dst, Size( i, i ), 0, 0 ); //0,0 height and width maybe?
		// �� edge �� �����ϰ� �Ѵ�.

		//#1
		//laplacian sharpening
		//how can we know the API's
		Laplacian(dst, laplace, CV_16S, i); //ddepth���� ����?

		//#2
		//mean smoothing
		//bilateral
		//to tweak (use diff para and see the diff result) the 4 and 5th parameters --> sigma color and sigma space
		bilateralFilter(src, bilateral, i, i*2, i/2);
		//�̰� ����� ����� ����� ������ ������ ������ ���� �����ؾ���

		// Median smoothing
		//medianBlur(src, dst1, i);
		// �� noise ����

		// show the blurred image with the text
		imshow("Gaussian filter", dst);
		//imshow("Median filter", dst1);
		imshow("laplace sharpening", laplace);
		imshow("bilateral filter", bilateral);

		// wait for 5 seconds
		waitKey(5000);
		//5�ʸ��� i(kernel size = filter ����)�� �ٲ�鼭, ������� ���� �޶���.
	}
}


//original ����
//gaussian ��ó��
//median ��äȭ ���� ����

//1. ó���� �׳� �״��
//2. i �� 51���� 21�� �ٲٰ�
//3. laplacian
//4. bilateral smooth 