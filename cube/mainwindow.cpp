#include "mainwindow.h"

#include <QKeyEvent>
#include <QDebug>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), cube(std::make_unique<CubeWidget>(this)){

    ui.setupUi(this);

    cube->setMinimumWidth(300);
    cube->setMinimumHeight(300);

    ui.verticalLayout->addWidget(cube.get());
    ui.verticalSlider_red->setValue(0);
    ui.verticalSlider_green->setValue(0);
    ui.verticalSlider_blue->setValue(0);

    QObject::connect(ui.verticalSlider_red, &QSlider::valueChanged, this, &MainWindow::colorChangeSlider);
    QObject::connect(ui.verticalSlider_green, &QSlider::valueChanged, this, &MainWindow::colorChangeSlider);
    QObject::connect(ui.verticalSlider_blue, &QSlider::valueChanged, this, &MainWindow::colorChangeSlider);
}


void MainWindow::colorChangeSlider() {
    QObject *object = sender();
    QSlider *slider = nullptr;
    slider = dynamic_cast<QSlider *>(object);
    float valueFromSlider = (float)slider->value()/100;

    if (object == ui.verticalSlider_red) {
        currentColor[0] = valueFromSlider;
    } else if (object == ui.verticalSlider_green) {
        currentColor[1] = valueFromSlider;
    } else if (object == ui.verticalSlider_blue) {
        currentColor[2] = valueFromSlider;
    }

    cube->updateColor(currentColor);
}
