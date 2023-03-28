#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class renderable : public QOpenGLFunctions
{
protected:
    QOpenGLShaderProgram* program_ = nullptr;
public:
    renderable() = default;
    virtual void initialize(QOpenGLShaderProgram* program = nullptr) { program_ = program; };
    virtual void set_color(const QColor&) {};
    virtual void render() = 0;
};
