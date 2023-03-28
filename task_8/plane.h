#pragma once

#include <vector>
#include <QWindow>
#include "renderable.h"

class plane final: public renderable
{

    float size_x;
    float size_y;

    float angle_ = 0.0f;
    GLint object_transformation = 0;
    bool raw = false;

    QColor color_;

    QVector3D position_;
    QVector3D rotation_;
    QVector3D scale_;
	
    std::vector<GLfloat> vertices_;
    std::vector<GLfloat> normals_;
    std::vector<GLfloat> colors_;
    std::vector<GLuint> indices_;
	
    GLint attr_pos_ = 0;
    GLint attr_normal_ = 0;

	GLint attr_color_ = 0;
    float rotation_angle_ = 0.0f;
    
public:
    plane(const QColor& color = {255,255,255 }, size_t count = 1, const QVector3D& position = {0,0,0}, const QVector3D& rotation = {1,0,0}, float rotation_angle = 0,
          const QVector3D& scale = {1,1,1}, bool _raw = false);
    void initialize(QOpenGLShaderProgram* program = nullptr) override;
    
    void render() override;
    void set_subgrid_count(size_t subgrid_count);
    void set_rotation(float angle, const QVector3D& direction);

    void set_color(const QColor& color);
};

