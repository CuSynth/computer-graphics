#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QVector3D>
#include <memory>
#include <QColorDialog>

#include "cubewidget.h"
#include "ui_mainwindow.h"

//class QExposeEvent;

class MainWindow : public QMainWindow {
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);


protected slots:
    void slotSetRotating();
    void slotSetMorphing();
    void slotSetFactor();
    void slotSetUseMorphSlider();
    void setMorphCoeff();
    void slotSetColored();

private:
//    QColorDialog qd;

    Ui::MainWindow ui;
    QVector3D current{0, 0, 0};

    std::unique_ptr<CubeWidget> cube;
};


#endif // MAINWINDOW_H
