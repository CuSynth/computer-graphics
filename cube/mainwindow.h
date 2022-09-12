#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector3D>
#include <memory>

#include "cubewidget.h"
#include "ui_mainwindow.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

protected slots:
    void colorChangeSlider();

private:
    Ui::MainWindow ui;
    QVector3D currentColor{0, 0, 0};

    std::unique_ptr<CubeWidget> cube;
};


#endif // MAINWINDOW_H
