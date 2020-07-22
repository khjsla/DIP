#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_firstQt.h"

//default for hj
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

class firstQt : public QMainWindow
{
    Q_OBJECT

public:
    firstQt(QWidget *parent = Q_NULLPTR);
    QImage firstQt::convertOpenCVMatToQtQImage(Mat mat);

private:
    Mat img;
    Ui::firstQtClass ui;

    //button�� .cpp���� ������ �ָ鿩�⼭ ���� ����� �ϴ� ��
private slots: //������ �Ͼ�� �Լ� ���� ���� ��� ���Ͽ��� ���ݴϴ�.
    void pushButton();
    void push_upload();
    void push_cvtgray();
    void push_cvthsv();
    void push_cvtycrcb();
};
