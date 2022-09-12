#include "mainwindow.h"

#include <QKeyEvent>
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), cube(std::make_unique<CubeWidget>(this)){
    ui.setupUi(this);
    setWindowTitle("Morphing cube");

    cube->setMinimumWidth(300);
    cube->setMinimumHeight(300);

    ui.verticalLayout->addWidget(cube.get());

    ui.morph_cbox->setChecked(true);
//    cube->setMorphing(ui.morph_cbox->isChecked());

    ui.rotation_cbox->setChecked(true);
//    cube->setRotating(ui.rotation_cbox->isChecked());

    ui.morphSldr_cbox->setChecked(false);
//    cube->setMorphBySlider(ui.morphSldr_cbox->isChecked());

    ui.factor_slider->setValue(5);
//    cube->setFactor(ui.factor_slider->value());
    ui.factor_num->setNum(ui.factor_slider->value());

    ui.morph_slider->setValue(45);
//    cube->setMorphCoeff((ui.morph_slider->value()));

    ui.color_cbox->setChecked(false);

    QObject::connect(ui.factor_slider,&QSlider::valueChanged, this, &MainWindow::slotSetFactor);
    QObject::connect(ui.morph_slider,&QSlider::valueChanged, this, &MainWindow::setMorphCoeff);
    QObject::connect(ui.morph_cbox, &QPushButton::clicked, this, &MainWindow::slotSetMorphing);
    QObject::connect(ui.rotation_cbox, &QPushButton::clicked, this, &MainWindow::slotSetRotating);
    QObject::connect(ui.morphSldr_cbox, &QPushButton::clicked, this, &MainWindow::slotSetUseMorphSlider);
    QObject::connect(ui.color_cbox, &QPushButton::clicked, this, &MainWindow::slotSetColored);
}

void MainWindow::slotSetFactor() {
    QSlider* slider = dynamic_cast<QSlider *>(sender());
    ui.factor_num->setNum(slider->value());
    cube->setFactor(slider->value());
}

void MainWindow::slotSetMorphing() {
    cube->setMorphing(ui.morph_cbox->isChecked());
}

void MainWindow::slotSetRotating() {
    cube->setRotating(ui.rotation_cbox->isChecked());
}

void MainWindow::slotSetUseMorphSlider() {
    cube->setMorphBySlider(ui.morphSldr_cbox->isChecked());
}

void MainWindow::setMorphCoeff() {
    cube->setMorphCoeff(ui.morph_slider->value());
}

void MainWindow::slotSetColored() {
    cube->setColored(ui.color_cbox->isChecked());
}
