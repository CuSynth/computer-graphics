#include "widget.h"
#include <GL/glut.h>
#include <iostream>


MyWidget::MyWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    resize(800,600); // задаем размеры окна
    paintTimer = new QTimer(this); // создаю таймер
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    paintTimer->start();
}

void MyWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key()==Qt::Key_M) {
        ++model_count%=3;
    }
}

void MyWidget::initLight()
{
    GLfloat light_ambient[] = { 0, 0, 0, 0.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 2.0, 1.0 };

    /* устанавливаем параметры источника света */
    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    /* включаем освещение и источник света */
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void MyWidget::initializeGL()
{
    glEnable(GL_MULTISAMPLE); // сглаживание MSAA вкл
    glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры
    glClearColor(1,1,1,1); // заливаем белым цветом
    glClearDepth(1.0); // Разрешить очистку буфера глубины
    glEnable(GL_DEPTH_TEST); // Разрешить тест глубины
    glDepthFunc(GL_LESS); // Тип теста глубины
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Улучшение в вычислении перспективы
    initLight(); // включаем свет
    model[0] = objloader::Instance().load(":/Materials/MeshHouse.obj");
    model[1] = objloader::Instance().load(":/Materials/MeshCube.obj");
    model[2] = objloader::Instance().load(":/Materials/MeshSphere.obj");
}

void MyWidget::resizeGL(int nWidth, int nHeight)
{
    // установка точки обзора
    glViewport(0, 0, nWidth, nHeight);
    qreal aspectratio = qreal(nWidth) / qreal(nHeight);

    // инициализация матрицы проекций
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // сброс матрицы проекции
    gluPerspective( 90.0, aspectratio, 0.1, 100.0 );

    // инициализация матрицы вида модели
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // сброс матрицы вида модели
}

void MyWidget::paintGL() // рисование
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана и буфера глубины
    glLoadIdentity();           // сбросить текущую матрицу
    if(model_count == 0) {
        glTranslatef(0, 0, -10.5);
    }
    else{
        glTranslatef(0, 0, -2.5);
    }
    glRotatef(angle,0.0f,1.0f,0.0f);
    glCallList(model[model_count]);
    angle += 0.3f;
}
