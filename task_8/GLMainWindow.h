#pragma once

#include <QMainWindow>
#include "ui_qtwidgetsapplication1.h"

class GLMainWindow : public QMainWindow
{

    Ui::QtWidgetsApplication1Class ui;
    bool subgrid_locked_ = true;

    Q_OBJECT;

public:
    GLMainWindow(QWidget *parent = Q_NULLPTR);
    
private slots:
    void set_subgrid_size(int value);
    void toggle_subgrid_lock(bool);
};
