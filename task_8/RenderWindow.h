#pragma once

#include "plane.h"
#include <QOpenGLShaderProgram>

class RenderWindow final
{
    QOpenGLShaderProgram *program_ = nullptr;

    std::vector<std::shared_ptr<renderable>> renderables_;
    GLint matrixUniform_ = 0;
    size_t frame_index = 0;
public:

    void addRenderable(std::shared_ptr<renderable> ptr);
    RenderWindow() = default;
    ~RenderWindow() = default;
    void render();
    void initialize();
};
