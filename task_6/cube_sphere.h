#pragma once
#include "renderable.h"
#include <QColor>
#include <QOpenGLTexture>

class cube_sphere :
    public renderable
{
    std::vector<GLfloat> vertices_;
    std::vector<GLfloat> normals_;
    std::vector<GLfloat> texture_pos_;
    std::vector<GLfloat> colors_;
    std::vector<GLuint> indices_;

    size_t subdivision_x_;
    size_t subdivision_y_;
    QVector3D position_;
    QVector3D rotation_;
    float angle_ = 0.0f;
    QVector3D scale_;

    GLint object_transformation = 0;
    GLint attr_pos_ = 0;
    GLint attr_normal_ = 0;
    GLint attr_texture_pos_ = 0;
    GLint attr_color_ = 0;
    GLint uniform_texture = 0;
    GLint uniform_normal_texture = 0;
    QColor color_;

    QOpenGLTexture* texture_ = nullptr;
    QOpenGLTexture* texture_normal_ = nullptr;



public:
    void initialize(QOpenGLShaderProgram* program = nullptr) override;
    void render() override;

    void set_position(const QVector3D& position);
    void set_rotation(float angle, const QVector3D& direction);
    void set_subgrid_count(size_t x, size_t y);
    void set_subgrid_count_x(size_t size);
    void set_subgrid_count_y(size_t size);

    cube_sphere(size_t subgrid_count_x = 10, size_t subgrid_count_y = 10, const QColor& color = { 255,255,255 }, const QVector3D& position = {}, const QVector3D& rotation = {}, float angle = 0.0f);
    cube_sphere(const cube_sphere& other) = default;
    virtual ~cube_sphere() = default;
};

