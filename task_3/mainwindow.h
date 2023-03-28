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
    void slotSetFactor();

    void slot_dps_col_btn();
    void slot_dps_I_sld();
    void slot_dps_pos_sld();

    void slot_ads_col_sld();

    void count_changed();

private:
//    QColorDialog qd;

    Ui::MainWindow ui;
    QVector3D current{0, 0, 0};

    std::unique_ptr<CubeWidget> cube;
};


#endif // MAINWINDOW_H
