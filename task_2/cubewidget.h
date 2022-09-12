#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

#include "geometryengine.h"

#include <memory>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QDebug>

class GeometryEngine;

class CubeWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    void setRotating(bool state);
    void setMorphing(bool state);
    void setFactor(size_t factor);
    void setMorphBySlider(bool state);
    void setMorphCoeff(float value);
    void setColored(bool state);

    ~CubeWidget();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


private:
    void initShaders();

    QBasicTimer timer;
    QOpenGLShaderProgram program;
    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;

    bool rotating = true;
    int frame_ = 0;

    bool morphing = true;
    bool morph_by_slider = false;
    float morph_coef = 45.0;

    bool colored = false;
    bool redraw = false;

    size_t factor = 5;
    std::unique_ptr<GeometryEngine> geometries;
};



#endif // CUBEWIDGET_H
