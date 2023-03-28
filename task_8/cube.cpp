#include "cube.h"

cube::cube(const size_t subgrid_count, const QColor& color, const QVector3D& position, const QVector3D& rotation) : position_(position), rotation_(rotation)
{
    planes_.emplace_back(color, subgrid_count, QVector3D{ 0, 0, 0.5 }, QVector3D{ 0, 1, 0 }, 0); //front
    planes_.emplace_back(color, subgrid_count, QVector3D{0.5, 0, 0}, QVector3D{0, 1, 0}, 90); //right
    planes_.emplace_back(color, subgrid_count, QVector3D{0, 0, -0.5}, QVector3D{0, 1, 0}, 180); //back
    planes_.emplace_back(color, subgrid_count, QVector3D{-0.5, 0, 0}, QVector3D{0, -1, 0}, 90); //left
    planes_.emplace_back(color, subgrid_count, QVector3D{0, 0.5, 0}, QVector3D{-1,0,0}, 90);  //top
    planes_.emplace_back(color, subgrid_count, QVector3D{0, -0.5, 0}, QVector3D{1,0,0}, 90);  //bottom
}


void cube::initialize(QOpenGLShaderProgram* program)
{
    renderable::initialize(program_);

    program_ = program;
    object_transformation = program_->uniformLocation("object_transformation");

    for (auto& plane: planes_)
    {
        plane.initialize(program);
    }
}

void cube::render()
{
    assert(program_);
    QMatrix4x4 transformation;
    transformation.translate(position_);
	transformation.rotate(angle_, rotation_);

    program_->setUniformValue(object_transformation, transformation);
    for (auto plane: planes_)
    {
        plane.render();
    }
}

void cube::set_subgrid_count(size_t _count)
{
    count = _count;
    for (auto& plane : planes_)
    {
        plane.set_subgrid_count(count);
    }
}

void cube::set_color(const QColor& color)
{
    for (auto& plane : planes_)
    {
        plane.set_color(color);
    }
}

void cube::set_position(const QVector3D& position)
{
    position_ = position;
}

void cube::set_rotation(float angle, const QVector3D& rotation)
{
    angle_ = angle;
    rotation_ = rotation;
}
