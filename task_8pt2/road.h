#pragma once

#include <QOpenGLTexture>
#include <vector>
#include <QWindow>
#include "renderable.h"

class road final: public renderable
{
    QColor color_;

    QVector3D position_;
    QVector3D rotation_;
    QVector3D scale_;
	
    std::vector<GLfloat> vertices_;
    std::vector<GLfloat> normals_;
    std::vector<GLfloat> colors_;
    std::vector<GLuint> indices_;
    std::vector<GLfloat> texture_pos_;
	
    GLint attr_pos_ = 0;
    GLint attr_normal_ = 0;
	GLint attr_color_ = 0;
    GLint attr_texture_pos_ = 0;

    GLint object_transformation = 0;

    float rotation_angle_ = 0.0f;
    GLint uniform_texture0 = 0;
    GLint uniform_texture1 = 0;
    GLint uniform_texture2 = 0;
    GLint uniform_texture3 = 0;

	QOpenGLTexture* texture_road0 = nullptr;
    QOpenGLTexture* texture_road1 = nullptr;
    QOpenGLTexture* texture_road2 = nullptr;
    QOpenGLTexture* texture_road3 = nullptr;

public:
    road(const QColor& color, size_t count_x = 1, size_t count_y = 1, const QVector3D& position = {0,0,0}, const QVector3D& rotation = {1,0,0}, float rotation_angle = 0, const QVector3D& scale = {1,1,1});
    void initialize(QOpenGLShaderProgram* program = nullptr) override;
    void set_position(const QVector3D& position);

    void render() override;
    void set_subgrid_count(size_t subgrid_count_x, size_t subgrid_count_y);
    void set_color(const QColor& color);

    void anti(float s);
    void enable_lin();
    void enable_balance();
    void enable_near();
};

