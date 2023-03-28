#include "mainwindow.h"

#include <QKeyEvent>
#include <QDebug>
#include <QPushButton>
#include <QColorDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), cube(std::make_unique<CubeWidget>(this)){

    ui.setupUi(this);

    cube->setMinimumWidth(300);
    cube->setMinimumHeight(300);

    ui.verticalLayout->addWidget(cube.get());


    ui.f_slider->setValue(9);
    cube->setFactor(ui.f_slider->value());
    ui.f_num->setNum(ui.f_slider->value());

    ui.amb_col_slider->setValue(50);
    cube->setComponentCoef(0.5, cube->amb);
    ui.diff_col_slider->setValue(99);
    cube->setComponentCoef(0.99, cube->diff);
    ui.spec_col_slider->setValue(99);
    cube->setComponentCoef(0.99, cube->spec);

    ui.dir_I->setValue(50);
    cube->setLightIntensity(0.5, cube->dir);
    ui.pt_I->setValue(50);
    cube->setLightIntensity(0.5, cube->pt);
    ui.sp_I->setValue(50);
    cube->setLightIntensity(0.5, cube->spot);

    ui.dir_pos_x->setValue(0);
    ui.dir_pos_y->setValue(0);
    ui.dir_pos_z->setValue(-5);

    ui.pt_pos_x->setValue(0);
    ui.pt_pos_y->setValue(0);
    ui.pt_pos_z->setValue(-5);

    ui.sp_pos_x->setValue(0);
    ui.sp_pos_y->setValue(0);
    ui.sp_pos_z->setValue(-5);

    QObject::connect(ui.f_slider, &QSlider::valueChanged, this, &MainWindow::slotSetFactor);

    QObject::connect(ui.dir_col_btn, &QPushButton::pressed, this, &MainWindow::slot_dps_col_btn);
    QObject::connect(ui.pt_col_btn, &QPushButton::pressed, this, &MainWindow::slot_dps_col_btn);
    QObject::connect(ui.spot_col_btn, &QPushButton::pressed, this, &MainWindow::slot_dps_col_btn);

    QObject::connect(ui.amb_col_btn, &QPushButton::pressed, this, &MainWindow::slot_dps_col_btn);
    QObject::connect(ui.diff_col_btn, &QPushButton::pressed, this, &MainWindow::slot_dps_col_btn);
    QObject::connect(ui.spec_col_btn, &QPushButton::pressed, this, &MainWindow::slot_dps_col_btn);

    QObject::connect(ui.amb_col_slider, &QSlider::valueChanged, this, &MainWindow::slot_ads_col_sld);
    QObject::connect(ui.diff_col_slider, &QSlider::valueChanged, this, &MainWindow::slot_ads_col_sld);
    QObject::connect(ui.spec_col_slider, &QSlider::valueChanged, this, &MainWindow::slot_ads_col_sld);

    QObject::connect(ui.dir_I, &QSpinBox::valueChanged, this, &MainWindow::slot_dps_I_sld);
    QObject::connect(ui.pt_I, &QSpinBox::valueChanged, this, &MainWindow::slot_dps_I_sld);
    QObject::connect(ui.sp_I, &QSpinBox::valueChanged, this, &MainWindow::slot_dps_I_sld);

    QObject::connect(ui.dir_pos_x, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.dir_pos_y, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.dir_pos_z, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);


    QObject::connect(ui.pt_pos_x, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.pt_pos_y, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.pt_pos_z, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);

    QObject::connect(ui.sp_pos_x, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.sp_pos_y, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.sp_pos_z, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);

    QObject::connect(ui.sp_dir_x, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.sp_dir_y, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.sp_dir_z, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);
    QObject::connect(ui.sp_phi, &QDoubleSpinBox::valueChanged, this, &MainWindow::slot_dps_pos_sld);

    QObject::connect(ui.spinBox, &QSpinBox::valueChanged, this, &MainWindow::count_changed);
}

void MainWindow::count_changed() {
    QSpinBox* box = dynamic_cast<QSpinBox*>(sender());
    cube->setCount(box->value());
}


void MainWindow::slotSetFactor() {
    QSlider* slider = dynamic_cast<QSlider *>(sender());
    ui.f_num->setNum(slider->value());
    cube->setFactor(slider->value());
}

void MainWindow::slot_dps_col_btn() {
    if (sender()->objectName() == "dir_col_btn") {
        cube->setLightColor(QColorDialog::getColor(Qt::white, this, "Color", QColorDialog::DontUseNativeDialog), cube->dir);
    }
    else if (sender()->objectName() == "pt_col_btn") {
        cube->setLightColor(QColorDialog::getColor(Qt::white, this, "Color", QColorDialog::DontUseNativeDialog), cube->pt);
    }
    else if (sender()->objectName() == "spot_col_btn") {
        cube->setLightColor(QColorDialog::getColor(Qt::white, this, "Color", QColorDialog::DontUseNativeDialog), cube->spot);
    }
    else if (sender()->objectName() == "amb_col_btn") {
        cube->setComponentColor(QColorDialog::getColor(Qt::white, this, "Color", QColorDialog::DontUseNativeDialog), cube->amb);
    }
    else if (sender()->objectName() == "diff_col_btn") {
        cube->setComponentColor(QColorDialog::getColor(Qt::white, this, "Color", QColorDialog::DontUseNativeDialog), cube->diff);
    }
    else if (sender()->objectName() == "spec_col_btn") {
        cube->setComponentColor(QColorDialog::getColor(Qt::white, this, "Color", QColorDialog::DontUseNativeDialog), cube->spec);
    }
}

void MainWindow::slot_ads_col_sld() {
    QSlider* slider = dynamic_cast<QSlider *>(sender());

    if (sender()->objectName() == "amb_col_slider") {
        cube->setComponentCoef(float(slider->value())/100, cube->amb);
    }
    else if (sender()->objectName() == "diff_col_slider") {
        cube->setComponentCoef(float(slider->value())/100, cube->diff);
    }
    else if (sender()->objectName() == "spec_col_slider") {
        cube->setComponentCoef(float(slider->value())/100, cube->spec);
    }
}

void MainWindow::slot_dps_I_sld() {
    QSpinBox* slider = dynamic_cast<QSpinBox *>(sender());

    if (sender()->objectName() == "dir_I") {
        cube->setLightIntensity(float(slider->value())/100, cube->dir);
    }
    else if (sender()->objectName() == "pt_I") {
        cube->setLightIntensity(float(slider->value())/100, cube->pt);
    }
    else if (sender()->objectName() == "sp_I") {
        cube->setLightIntensity(float(slider->value())/100, cube->spot);
    }
}

void MainWindow::slot_dps_pos_sld() {

    if (sender()->objectName() == "dir_pos_x"
        || sender()->objectName() == "dir_pos_y"
        || sender()->objectName() == "dir_pos_z")
    {
//        std::cout << "dir_pos";
        cube->setLightPos({float(ui.dir_pos_x->value()),
                          float(ui.dir_pos_y->value()),
                          float(ui.dir_pos_z->value())},
                          cube->dir);
    }
    else if (sender()->objectName() == "pt_pos_x"
             || sender()->objectName() == "pt_pos_y"
             || sender()->objectName() == "pt_pos_z")
    {
//        std::cout << "pt_pos";
        cube->setLightPos({float(ui.pt_pos_x->value()),
                          float(ui.pt_pos_y->value()),
                          float(ui.pt_pos_z->value())},
                          cube->pt);    }
    else if (sender()->objectName() == "sp_pos_x"
             || sender()->objectName() == "sp_pos_y"
             || sender()->objectName() == "sp_pos_z")
    {
//        std::cout << "sp_pos";
        cube->setLightPos({float(ui.sp_pos_x->value()),
                          float(ui.sp_pos_y->value()),
                          float(ui.sp_pos_z->value())},
                          cube->spot);
    }
    else if (sender()->objectName() == "sp_dir_x"
             || sender()->objectName() == "sp_dir_y"
             || sender()->objectName() == "sp_dir_z"
             || sender()->objectName() == "sp_phi")
    {
        cube->setSpotDir({float(ui.sp_dir_x->value()),
                          float(ui.sp_dir_y->value()),
                          float(ui.sp_dir_z->value())});
        cube->setSpotPhi(ui.sp_phi->value());
    }
}
