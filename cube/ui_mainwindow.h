/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_openGLScreen;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_classicalWidgets;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QSlider *verticalSlider_red;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QSlider *verticalSlider_green;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QSlider *verticalSlider_blue;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(974, 690);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_openGLScreen = new QGroupBox(centralwidget);
        groupBox_openGLScreen->setObjectName(QString::fromUtf8("groupBox_openGLScreen"));
        gridLayout_3 = new QGridLayout(groupBox_openGLScreen);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_openGLScreen, 0, 0, 1, 1);

        groupBox_classicalWidgets = new QGroupBox(centralwidget);
        groupBox_classicalWidgets->setObjectName(QString::fromUtf8("groupBox_classicalWidgets"));
        groupBox_classicalWidgets->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_2 = new QGridLayout(groupBox_classicalWidgets);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(groupBox_classicalWidgets);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        verticalSlider_red = new QSlider(groupBox);
        verticalSlider_red->setObjectName(QString::fromUtf8("verticalSlider_red"));
        verticalSlider_red->setMinimum(-100);
        verticalSlider_red->setMaximum(100);
        verticalSlider_red->setSingleStep(1);
        verticalSlider_red->setPageStep(10);
        verticalSlider_red->setSliderPosition(0);
        verticalSlider_red->setOrientation(Qt::Vertical);

        verticalLayout_3->addWidget(verticalSlider_red);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_4->addWidget(label_2);

        verticalSlider_green = new QSlider(groupBox);
        verticalSlider_green->setObjectName(QString::fromUtf8("verticalSlider_green"));
        verticalSlider_green->setMinimum(-100);
        verticalSlider_green->setMaximum(100);
        verticalSlider_green->setPageStep(10);
        verticalSlider_green->setOrientation(Qt::Vertical);

        verticalLayout_4->addWidget(verticalSlider_green);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(5, 5, 5, 5);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_5->addWidget(label_3);

        verticalSlider_blue = new QSlider(groupBox);
        verticalSlider_blue->setObjectName(QString::fromUtf8("verticalSlider_blue"));
        verticalSlider_blue->setMinimum(-100);
        verticalSlider_blue->setMaximum(100);
        verticalSlider_blue->setPageStep(10);
        verticalSlider_blue->setTracking(true);
        verticalSlider_blue->setOrientation(Qt::Vertical);

        verticalLayout_5->addWidget(verticalSlider_blue);


        horizontalLayout_2->addLayout(verticalLayout_5);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_classicalWidgets, 0, 1, 1, 1);

        gridLayout_4->setColumnStretch(0, 5);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_openGLScreen->setTitle(QCoreApplication::translate("MainWindow", "OpenGLWidget", nullptr));
        groupBox_classicalWidgets->setTitle(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Color", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Red", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Green", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Blue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
