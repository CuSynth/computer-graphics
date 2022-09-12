#include "cubewidget.h"

#include <QMouseEvent>
#include <cmath>
#include <QColorDialog>


CubeWidget::~CubeWidget() {
    makeCurrent();
    doneCurrent();
}

void CubeWidget::setRotating(bool state) {
    rotating = state;
    qDebug() << "Rotation:" << rotating;
}

void CubeWidget::setMorphing(bool state) {
    morphing = state;
    qDebug() << "Morphing:" << morphing;
}

void CubeWidget::setFactor(size_t newFactor) {
    factor = newFactor;
    redraw = true;
    qDebug() << "New factor set:" << newFactor;
}

void CubeWidget::setMorphBySlider(bool state) {
    morph_by_slider = state;
    qDebug() << "Morph by slider:" << state;
}

void CubeWidget::setMorphCoeff(float value) {
    morph_coef = value;
    qDebug() << "Morph coeff:" << value;
}

void CubeWidget::setColored(bool state) {
    colored = state;
    redraw = true;
    qDebug() << "Colored:" << state;
}

void CubeWidget::mousePressEvent(QMouseEvent *e) {
    mousePressPosition = QVector2D(e->position());
//    qDebug() << e;
}

void CubeWidget::mouseReleaseEvent(QMouseEvent *e) {
    QVector2D diff = QVector2D(e->position()) - mousePressPosition;
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
    qreal acc = diff.length() / 100.0;
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
    angularSpeed += acc;

    //    qDebug() << e;
}

void CubeWidget::timerEvent(QTimerEvent *) {
    angularSpeed *= 0.99;
    if (angularSpeed < 0.01 || !rotating) {
        angularSpeed = 0.0;
    } else {
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    }
    update();
}

void CubeWidget::initializeGL() {
    qDebug() << "Initializing glwidget..";

    initializeOpenGLFunctions();

    // Set bg color
//    glClearColor(0.7, 0.3, 0.5, 1);
    glClearColor(0, 0, 0, 1);

    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    geometries = std::make_unique<GeometryEngine>(factor);
    timer.start(12, this);

    qDebug() << "Widget initialized!";
}

void CubeWidget::initShaders() {
    qDebug() << "Initializing shaders..";

    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/src/vshader.glsl"))
        close();
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/src/fshader.glsl"))
        close();
    if (!program.link())
        close();
    if (!program.bind())
      close();

    qDebug() << "Shaders initialized!";
}

void CubeWidget::resizeGL(int w, int h) {
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}

void CubeWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(redraw) {
        geometries->initCubeGeometry(1.0f, factor, colored);
        redraw = false;
    }

    program.bind();

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0f);
    matrix.rotate(rotation);

    program.setUniformValue("mvp_matrix", projection * matrix);

    if(morph_by_slider)
        program.setUniformValue("t", morph_coef);
    else
        program.setUniformValue("t", static_cast<GLfloat>(frame_));


    geometries->drawCubeGeometry(&program);

    program.release();

    if(morphing)
        ++frame_;
}
