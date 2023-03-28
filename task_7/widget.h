#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer> // таймер
#include <QKeyEvent> // для перехвата нажатий клавиш
#include "obj_loader.h" // загрузчик моделей в формате obj

class MyWidget : public QOpenGLWidget
{
Q_OBJECT
    QTimer *paintTimer; // таймер
    GLubyte model_count = 0; // номер текущей модели
    GLuint model[4]; // номер display list для вывода нужной модели
    GLfloat angle = 0; // угол вращения

    void initLight(); // включить свет
    int loadObject(const QString &filename);
    virtual void keyPressEvent(QKeyEvent *event);
public:
    MyWidget(QWidget *parent = nullptr);

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

};
#endif // WIDGET_H
