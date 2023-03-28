#include "cubewidget.h"

#include <QMouseEvent>
#include <cmath>
#include <QPainter>
#include <iostream>

CubeWidget::~CubeWidget() {
    makeCurrent();
    doneCurrent();
}

void CubeWidget::setFactor(size_t _factor) {
    factor = _factor;
    needToReinit = true;
}

void CubeWidget::setLightColor(QColor color, lightning light) {
    switch (light) {
    case dir:
        dir_color = QVector3D{color.redF(), color.greenF(), color.blueF()}; break;
    case pt:
        pt_color = QVector3D{color.redF(), color.greenF(), color.blueF()}; break;
    case spot:
        spot_color = QVector3D{color.redF(), color.greenF(), color.blueF()}; break;
    }
}

void CubeWidget::setLightIntensity(float I, lightning light) {
    switch (light) {
    case dir:
        dir_intensity = I; break;
    case pt:
        pt_intensity = I; break;
    case spot:
        spot_intensity = I; break;
    }
}

void CubeWidget::setLightPos(QVector3D pos, lightning light) {
    switch (light) {
    case dir:
//        std::cout << pos.x() << " " << pos.y() << " " << pos.y() << "\n";
        dir_pos= pos; break;
    case pt:
//        std::cout << pos.x() << " " << pos.y() << " " << pos.y() << "\n";
        pt_pos = pos; break;
    case spot:
//        std::cout << pos.x() << " " << pos.y() << " " << pos.y() << "\n";
        spot_pos = pos; break;
    }
}

void CubeWidget::setComponentColor(QColor color, component comp) {
    switch (comp) {
        case amb:
        amb_color = QVector3D{color.redF(), color.greenF(), color.blueF()}; break;
    case diff:
        diff_color = QVector3D{color.redF(), color.greenF(), color.blueF()}; break;
    case spec:
        spec_color = QVector3D{color.redF(), color.greenF(), color.blueF()}; break;
    }
}

void CubeWidget::setComponentCoef(float coeff, component comp) {
    switch (comp) {
    case amb:
        amb_st = coeff; break;
    case diff:
        diff_st = coeff; break;
    case spec:
        spec_st = coeff; break;
    }
}

void CubeWidget::setCount(size_t count) {
    m_objects.clear();

    int cnt = count;
    for (auto x = -6*cnt/2; x < 6*cnt/2; x += 6) {
        for (auto z =  -6*cnt/2; z < 6*cnt/2; z += 6) {
                m_objects.append(std::make_shared<GeometryEngine>(3.0));
                m_objects[m_objects.size() - 1]->translate(QVector3D(x, -10, z));
                m_objects[m_objects.size() - 1]->initCubeGeometry(3.0f, factor);
        }
    }
    needToReinit = true;
}


void CubeWidget::mousePressEvent(QMouseEvent *e) {
    mousePressPosition = QVector2D(e->position());
}

void CubeWidget::mouseReleaseEvent(QMouseEvent *e) {
    QVector2D diff = QVector2D(e->position()) - mousePressPosition;
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
    qreal acc = diff.length() / 100.0;
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
    angularSpeed += acc;
}

void CubeWidget::timerEvent(QTimerEvent *) {
    angularSpeed *= 0.99;
    if (angularSpeed < 0.01 /*|| !rotating*/) {
        angularSpeed = 0.0;
    } else {
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    }
    update();

    for (auto &m_object : m_objects) {
//        m_object->rotate(QQuaternion::fromAxisAndAngle(QVector3D(0.0, 1.0, 0.0).normalized(), 0.1));
    }

}
void CubeWidget::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    m_z += 0.25;
  } else if (event->angleDelta().y() < 0) {
    m_z -= 0.25;
  }
  update();
}
void CubeWidget::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(1.0f, 1.0f, 1.0f, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    initShaders();
    m_z = -8.0f;


    m_objects.append(std::make_shared<GeometryEngine>(3.0));
    m_objects[m_objects.size() - 1]->translate(QVector3D(0, 0, 0));

//    factor = 9;
//    int cnt = 180;

//    int cnt = 1;
//    for (auto x = -6*cnt/2; x < 6*cnt/2; x += 6) {
//        for (auto z =  -6*cnt; z < 0; z += 6) {
//                m_objects.append(std::make_shared<GeometryEngine>(3.0));
//                m_objects[m_objects.size() - 1]->translate(QVector3D(x, 0, z));
//                m_objects[m_objects.size() - 1]->initCubeGeometry(3.0f, factor);
//        }
//    }

    timer.start(12, this);
}




void CubeWidget::initShaders() {

    program.removeAllShaders();

    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/Shaders/phong_vshader.glsl"))
      close();
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/Shaders/phong_fshader.glsl"))
      close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}


void CubeWidget::resizeGL(int w, int h) {
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 2.0, zFar = 200.0, fov = 60.0;
    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}

void CubeWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    if(needToReinit){
        for (auto &m_object : m_objects) {
            m_object->initCubeGeometry(3.0f, factor);
        }
        needToReinit = false;
    }


    program.bind();

    // Calculate model view transformation
    QMatrix4x4 matrixView;
    matrixView.translate(0.0f, 0.0f, m_z);
    matrixView.rotate(QQuaternion::fromAxisAndAngle(QVector3D(1.0, 0.0, 0.0).normalized(), 30));
    matrixView.rotate(rotation);

    program.setUniformValue("projection_matrix", projection);
    program.setUniformValue("view_matrix", matrixView);

    program.setUniformValue("ambientColor", amb_color);
    program.setUniformValue("diffuseColor", diff_color);
    program.setUniformValue("specularColor", spec_color);

    program.setUniformValue("ambientStrength", amb_st);
    program.setUniformValue("specularStrength", spec_st);
    program.setUniformValue("diffuseStrength", diff_st);

    program.setUniformValue("point_col", pt_color);
    program.setUniformValue("point_I", pt_intensity);
    program.setUniformValue("point_pos", pt_pos);

    program.setUniformValue("dir_col", dir_color);
    program.setUniformValue("dir_I", dir_intensity);
    program.setUniformValue("dir_pos", dir_pos);

    program.setUniformValue("spot_col", spot_color);
    program.setUniformValue("spot_I", spot_intensity);
    program.setUniformValue("spot_pos", spot_pos);


    program.setUniformValue("specularFactor", 16.0f);
    program.setUniformValue("P", 0.7f);
    program.setUniformValue("d", 1.0f);
    program.setUniformValue("K", 0.5f);

    program.setUniformValue("spot_dir", spot_dir);
    program.setUniformValue("spot_phi", spot_phi);

    program.setUniformValue("spot_k", 0.5F);

    program.setUniformValue("f_phong", frag);

    for (auto &m_object : m_objects) {
      m_object->drawCubeGeometry(&program, context()->functions());
    }


    auto currentTimePoint = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(currentTimePoint - lastTimePoint);
    double mcs = elapsed_ms.count();

    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(0, 0, width(), height(), Qt::AlignLeft, std::to_string(1000000.0/mcs).data());
    painter.end();
    lastTimePoint = currentTimePoint;


    program.release();

}
