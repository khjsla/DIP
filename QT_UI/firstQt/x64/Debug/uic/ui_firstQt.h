/********************************************************************************
** Form generated from reading UI file 'firstQt.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTQT_H
#define UI_FIRSTQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_firstQtClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *btn_upload;
    QPushButton *btn_cvtgray;
    QPushButton *btn_cvthsv;
    QPushButton *btn_cvtycrcb;
    QLabel *img_input;
    QLabel *img_gray;
    QLabel *img_hsv;
    QLabel *img_ycrcb;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *firstQtClass)
    {
        if (firstQtClass->objectName().isEmpty())
            firstQtClass->setObjectName(QString::fromUtf8("firstQtClass"));
        firstQtClass->setEnabled(true);
        firstQtClass->resize(600, 400);
        centralWidget = new QWidget(firstQtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 101, 16));
        btn_upload = new QPushButton(centralWidget);
        btn_upload->setObjectName(QString::fromUtf8("btn_upload"));
        btn_upload->setGeometry(QRect(40, 70, 75, 23));
        btn_cvtgray = new QPushButton(centralWidget);
        btn_cvtgray->setObjectName(QString::fromUtf8("btn_cvtgray"));
        btn_cvtgray->setGeometry(QRect(260, 60, 75, 23));
        btn_cvthsv = new QPushButton(centralWidget);
        btn_cvthsv->setObjectName(QString::fromUtf8("btn_cvthsv"));
        btn_cvthsv->setGeometry(QRect(260, 150, 75, 23));
        btn_cvtycrcb = new QPushButton(centralWidget);
        btn_cvtycrcb->setObjectName(QString::fromUtf8("btn_cvtycrcb"));
        btn_cvtycrcb->setGeometry(QRect(260, 240, 75, 23));
        img_input = new QLabel(centralWidget);
        img_input->setObjectName(QString::fromUtf8("img_input"));
        img_input->setGeometry(QRect(40, 140, 161, 151));
        img_gray = new QLabel(centralWidget);
        img_gray->setObjectName(QString::fromUtf8("img_gray"));
        img_gray->setGeometry(QRect(370, 0, 111, 101));
        img_hsv = new QLabel(centralWidget);
        img_hsv->setObjectName(QString::fromUtf8("img_hsv"));
        img_hsv->setGeometry(QRect(370, 110, 111, 101));
        img_ycrcb = new QLabel(centralWidget);
        img_ycrcb->setObjectName(QString::fromUtf8("img_ycrcb"));
        img_ycrcb->setGeometry(QRect(380, 230, 111, 101));
        firstQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(firstQtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        firstQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(firstQtClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        firstQtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(firstQtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        firstQtClass->setStatusBar(statusBar);

        retranslateUi(firstQtClass);
        QObject::connect(btn_upload, SIGNAL(clicked()), firstQtClass, SLOT(push_upload()));

        QMetaObject::connectSlotsByName(firstQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *firstQtClass)
    {
        firstQtClass->setWindowTitle(QCoreApplication::translate("firstQtClass", "firstQt", nullptr));
        label->setText(QCoreApplication::translate("firstQtClass", "12163291 \352\260\225\355\230\204\354\247\200", nullptr));
        btn_upload->setText(QCoreApplication::translate("firstQtClass", "upload", nullptr));
        btn_cvtgray->setText(QCoreApplication::translate("firstQtClass", "gray", nullptr));
        btn_cvthsv->setText(QCoreApplication::translate("firstQtClass", "hsv", nullptr));
        btn_cvtycrcb->setText(QCoreApplication::translate("firstQtClass", "ycrcb", nullptr));
        img_input->setText(QCoreApplication::translate("firstQtClass", "input", nullptr));
        img_gray->setText(QCoreApplication::translate("firstQtClass", "TextLabel", nullptr));
        img_hsv->setText(QCoreApplication::translate("firstQtClass", "TextLabel", nullptr));
        img_ycrcb->setText(QCoreApplication::translate("firstQtClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class firstQtClass: public Ui_firstQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTQT_H
