#pragma once

#include "renderable.h"
#include "plane.h"

class cube final: public renderable
{
    size_t count = 1;
    QVector3D position_;
    float angle_ = 0.0f;
    QVector3D rotation_;
    QVector3D scale_;

    std::vector<plane> planes_;
    GLint object_transformation = 0;

public:
    void initialize(QOpenGLShaderProgram* program = nullptr) override;
    void render() override;
	
    void set_subgrid_count(size_t count);
    void set_color(const QColor& color) override;

    void set_position(const QVector3D& position);
    void set_rotation(float angle, const QVector3D& direction);

    cube(size_t subgrid_count = 1, const QColor& color = {255,255,255}, const QVector3D& position = {}, const QVector3D& rotation = {});
    cube(const cube& other) = default;
    ~cube() = default;
};
