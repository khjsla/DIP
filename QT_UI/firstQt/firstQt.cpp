#include "firstQt.h"

//default for hj
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//Qt 디자이너에 넣을 요소들
#include <QPushButton>
#include <qmessagebox.h> 
#include <qlistwidget.h> //*
#include <qfiledialog.h>
//먼저 만들어야함

//default for hj
using namespace std;
using namespace cv;

firstQt::firstQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void firstQt::pushButton() {
    QMessageBox::information(this, "Hello", "Good"); //Hello라는 이름에 Good이라는 내용의 메세지 박스가 뜨게됩니다.
}

QImage firstQt::convertOpenCVMatToQtQImage(cv::Mat mat) {
	if (mat.channels() == 1) {                  // if grayscale image
		return QImage((uchar*)mat.data, (int)mat.cols, (int)mat.rows, (int)mat.step, QImage::Format_Indexed8);     // declare and return a QImage
	}
	else if (mat.channels() == 3) {             // if 3 channel color image
		cv::cvtColor(mat, mat, COLOR_BGR2RGB);     // invert BGR to RGB
		return QImage((uchar*)mat.data, (int)mat.cols, (int)mat.rows, (int)mat.step, QImage::Format_RGB888);       // declare and return a QImage
	}

	return QImage();  // return a blank QImage if the above did not work
}

void firstQt::push_upload() {
	QString file_path = QFileDialog::getOpenFileName();

	img = imread(file_path.toStdString());
	if (!img.data)  // Check for invalid input
	{
		ui.img_input->setText("There is no image!");
		return;
	}

	QImage qimgOutput = convertOpenCVMatToQtQImage(img);

	// Display output
	ui.img_input->setPixmap(QPixmap::fromImage(qimgOutput));
}

void firstQt::push_cvtgray() {
	Mat dst;
	cvtColor(img, dst, COLOR_BGR2GRAY);

	QImage qimgOutput = convertOpenCVMatToQtQImage(dst);

	// Display output
	ui.img_gray->setPixmap(QPixmap::fromImage(qimgOutput));
}

void firstQt::push_cvthsv() {
	Mat dst;
	cvtColor(img, dst, COLOR_BGR2HSV);

	QImage qimgOutput = convertOpenCVMatToQtQImage(dst);

	// Display output
	ui.img_hsv->setPixmap(QPixmap::fromImage(qimgOutput));
}

void firstQt::push_cvtycrcb() {
	Mat dst;
	cvtColor(img, dst, COLOR_BGR2YCrCb);

	QImage qimgOutput = convertOpenCVMatToQtQImage(dst);

	// Display output
	ui.img_ycrcb->setPixmap(QPixmap::fromImage(qimgOutput));
}