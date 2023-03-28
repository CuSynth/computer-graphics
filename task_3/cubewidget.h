#pragma once

#include "geometryengine.h"

#include <QBasicTimer>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QVector2D>
#include <chrono>

class GeometryEngine;

class CubeWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

  public:

    enum component {
        amb,
        diff,
        spec
    };

    enum lightning {
        dir,
        pt,
        spot
    };

    using QOpenGLWidget::QOpenGLWidget;
    void setFactor(size_t factor);

    void setLightColor(QColor color, lightning light);
    void setLightIntensity(float I, lightning light);
    void setLightPos(QVector3D pos, lightning light);
    void setCount(size_t count);
    void setSpotDir(QVector3D pos) {
        spot_dir = pos;
    }
    void setSpotPhi(float f) {
        spot_phi = f;
    }

    void setComponentColor(QColor color, component comp);
    void setComponentCoef(float coeff, component comp);

    ~CubeWidget();

  protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();

  private:

    QBasicTimer timer;
    QOpenGLShaderProgram program;
    QVector<std::shared_ptr<GeometryEngine>> m_objects;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;

    size_t factor = 0;

    float amb_st = 0.1;
    QVector3D amb_color{0.5, 0.5, 0.5};

    float spec_st = 1.0;
    QVector3D spec_color{0.5, 0.5, 0.5};

    float diff_st = 1.0;
    QVector3D diff_color{0.5, 0.5, 0.5};


    float dir_intensity = 1.0;
    QVector3D dir_pos{0.0, 0.0, -5.0};
    QVector3D dir_color{0.5, 0.0, 0.0};


    float pt_intensity = 1.0;
    QVector3D pt_pos{0.0, 0.0, -5.0};
    QVector3D pt_color{0.0, 0.5, 0.0};


    float spot_intensity = 1.0;
    QVector3D spot_pos{0.0, 0.0, -5.0};
    QVector3D spot_color{0.0, 0.0, 0.5};


    QVector3D spot_dir{0.0, 0.0, -5.0};
    float spot_phi = 0;

    bool needToReinit = false;

    std::chrono::high_resolution_clock::time_point lastTimePoint;

    float m_z;
    int frame_ = 0;
};

