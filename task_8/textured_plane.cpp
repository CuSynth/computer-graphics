#include "textured_plane.h"

textured_plane::textured_plane(const QColor& color, const size_t count, const QVector3D& position, const QVector3D& rotation, float rotation_angle, const QVector3D& scale, bool _raw)
    : color_(color), position_(position), rotation_(rotation), rotation_angle_(rotation_angle), scale_(scale), raw(_raw)
{
    set_subgrid_count(count);
}

void textured_plane::initialize(QOpenGLShaderProgram* program)
{
    initializeOpenGLFunctions();
    program_ = program;

    object_transformation = program_->uniformLocation("object_transformation");
    attr_pos_ = program_->attributeLocation("attr_pos");
    attr_normal_ = program_->attributeLocation("attr_normal");
    attr_color_ = program_->attributeLocation("attr_color");
    attr_texture_pos_ = program_->attributeLocation("attr_texture_pos");

    delete texture_;
    texture_ = new QOpenGLTexture{ QImage(":/Materials/road_2.jpg") };

    uniform_texture = program_->uniformLocation("uniform_texture");

}

void textured_plane::render()
{
    if(raw) {
            QMatrix4x4 transformation;
            transformation.translate(position_);
            transformation.rotate(angle_, rotation_);

            program_->setUniformValue(object_transformation, transformation);
    }

    program_->setUniformValue("uniform_texture", 0);


    glVertexAttribPointer(attr_pos_, 3, GL_FLOAT, GL_FALSE, 0, vertices_.data());
    glVertexAttribPointer(attr_normal_, 3, GL_FLOAT, GL_FALSE, 0, normals_.data());
    glVertexAttribPointer(attr_texture_pos_, 2, GL_FLOAT, GL_FALSE, 0, texture_pos_.data());
    glVertexAttribPointer(attr_color_, 3, GL_FLOAT, GL_FALSE, 0, colors_.data());

    glEnableVertexAttribArray(attr_pos_);
    glEnableVertexAttribArray(attr_normal_);
    glEnableVertexAttribArray(attr_texture_pos_);
    glEnableVertexAttribArray(attr_color_);

    glActiveTexture(GL_TEXTURE0);
    texture_->bind();

    glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_INT, indices_.data());

    texture_->release();

    glDisableVertexAttribArray(attr_pos_);
    glDisableVertexAttribArray(attr_normal_);
    glDisableVertexAttribArray(attr_texture_pos_);
    glDisableVertexAttribArray(attr_color_);
}

void textured_plane::set_subgrid_count(const size_t subgrid_count)
{
    const auto clamped_subgrid_count_x = std::max(static_cast<size_t>(1), subgrid_count);
    const auto clamped_subgrid_count_y = std::max(static_cast<size_t>(1), subgrid_count);

    const GLfloat dlx = 1.0f / clamped_subgrid_count_x;
    const GLfloat dly = 1.0f / clamped_subgrid_count_y;
    QMatrix4x4 matrix;

    vertices_.clear();
    colors_.clear();
    indices_.clear();

    matrix.translate(position_);
    matrix.rotate(rotation_angle_, rotation_);
    matrix.scale(scale_);

    QMatrix4x4 normal_matrix;
    normal_matrix.rotate(rotation_angle_, rotation_);
    QVector4D normal{ 0,0,1,1 };
    normal = normal_matrix * normal;
    texture_pos_.clear();

    for (size_t y = 0; y <= clamped_subgrid_count_y; ++y)
    {
        for (size_t x = 0; x <= clamped_subgrid_count_x; ++x)
        {


            const QVector2D texture_pos{(static_cast<float>(y * 1.0 / clamped_subgrid_count_y)),
                                        (static_cast<float>(x * 1.0 / clamped_subgrid_count_x))};

            texture_pos_.push_back(texture_pos.x());
            texture_pos_.push_back(texture_pos.y());


            QVector4D vec{ -0.5f + x * dlx, -0.5f + y * dly, 0, 1 };
            vec = matrix * vec;

            vertices_.push_back(vec.x());
            vertices_.push_back(vec.y());
            vertices_.push_back(vec.z());

            normals_.push_back(normal.x());
            normals_.push_back(normal.y());
            normals_.push_back(normal.z());

            colors_.push_back(color_.redF());
            colors_.push_back(color_.greenF());
            colors_.push_back(color_.blueF());
        }
    }

    const size_t rows = clamped_subgrid_count_y + 1;
    const size_t columns = clamped_subgrid_count_x + 1;

    for (size_t row = 0; row < rows - 1; ++row)
    {
        indices_.push_back(row * columns);
        for (size_t col = 0; col < columns; ++col)
        {
            indices_.push_back(row * columns + col);
            indices_.push_back((row + 1) * columns + col);
        }
        indices_.push_back((row + 1) * columns + (columns - 1));
    }
}

void textured_plane::set_color(const QColor& color)
{
    color_ = color;
    for (size_t i = 0; i < colors_.size(); i+=3)
    {
        colors_.at(i) = color_ .redF();
        colors_.at(i+1) = color.greenF();
        colors_.at(i+2) = color.blueF();
    }
}



void textured_plane::set_rotation(float angle, const QVector3D& rotation)
{
    angle_ = angle;
    rotation_ = rotation;
}

