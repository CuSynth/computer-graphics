#include "cube_sphere.h"

#define _USE_MATH_DEFINES
#include <math.h>


void cube_sphere::initialize(QOpenGLShaderProgram* program)
{
	initializeOpenGLFunctions();
	renderable::initialize(program);
	program_ = program;
	object_transformation = program_->uniformLocation("object_transformation");
	attr_pos_ = program_->attributeLocation("attr_pos");
	attr_normal_ = program_->attributeLocation("attr_normal");
	attr_color_ = program_->attributeLocation("attr_color");
	attr_texture_pos_ = program_->attributeLocation("attr_texture_pos");

	delete texture_;
	//texture_ = new QOpenGLTexture{ QImage("Materials/Earth_Albedo.jpg") };
    texture_ = new QOpenGLTexture{ QImage(":/Materials/Earth8k.jpg") };
	delete texture_normal_;
	//texture_normal_ = new QOpenGLTexture{ QImage("Materials/Earth_NormalMap.jpg") };
    texture_normal_ = new QOpenGLTexture{ QImage(":/Materials/Earth8k_normal.jpg") };
	uniform_texture = program_->uniformLocation("uniform_texture");
	uniform_normal_texture = program_->uniformLocation("uniform_normal_texture");

	set_subgrid_count(subdivision_x_, subdivision_y_);
}

void cube_sphere::render()
{
	assert(program_);
	QMatrix4x4 transformation;
	transformation.translate(position_);
	transformation.rotate(angle_, rotation_);

	program_->setUniformValue(object_transformation, transformation);
	program_->setUniformValue("uniform_texture", 0);
	program_->setUniformValue("uniform_normal_texture", 1);

	glVertexAttribPointer(attr_pos_, 3, GL_FLOAT, GL_FALSE, 0, vertices_.data());
	glVertexAttribPointer(attr_normal_, 3, GL_FLOAT, GL_FALSE, 0, normals_.data());
	glVertexAttribPointer(attr_texture_pos_, 2, GL_FLOAT, GL_FALSE, 0, texture_pos_.data());
	glVertexAttribPointer(attr_color_, 3, GL_FLOAT, GL_FALSE, 0, colors_.data());

	glEnableVertexAttribArray(attr_pos_);
	glEnableVertexAttribArray(attr_normal_);
	glEnableVertexAttribArray(attr_texture_pos_);
	glEnableVertexAttribArray(attr_color_);

	glActiveTexture(GL_TEXTURE0 + 0);
	texture_->bind();
	glActiveTexture(GL_TEXTURE0 + 1);
	texture_normal_->bind();
	glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_INT, indices_.data());
	texture_->release();
	texture_normal_->release();
	glDisableVertexAttribArray(attr_pos_);
	glDisableVertexAttribArray(attr_normal_);
	glDisableVertexAttribArray(attr_texture_pos_);
	glDisableVertexAttribArray(attr_color_);
}

void cube_sphere::set_position(const QVector3D& position)
{
	position_ = position;
}

void cube_sphere::set_rotation(float angle, const QVector3D& direction)
{
	rotation_ = direction;
	angle_ = angle;
}

void cube_sphere::set_subgrid_count(size_t x, size_t y)
{
	subdivision_x_ = x;
	subdivision_y_ = y;
	const auto clamped_subgrid_count_x = std::clamp(subdivision_x_, static_cast<size_t>(1), static_cast<size_t>(1000));
	const auto clamped_subgrid_count_y = std::clamp(subdivision_y_, static_cast<size_t>(1), static_cast<size_t>(1000));

	const double r = 1.0f;

	vertices_.clear();
	normals_.clear();
	texture_pos_.clear();
	colors_.clear();
	indices_.clear();

	for (size_t y = 0; y <= clamped_subgrid_count_y; ++y)
	{
		for (size_t x = 0; x <= clamped_subgrid_count_x; ++x)
		{
			const double phi = x * 2 * M_PI / clamped_subgrid_count_x;
			const double theta = y * M_PI / clamped_subgrid_count_y;
			const QVector3D vec
			{
				static_cast<float>(r * sin(theta) * cos(phi)),
				static_cast<float>(r * sin(theta) * sin(phi)),
				static_cast<float>(r * cos(theta))
			};
			vertices_.push_back(vec.x());
			vertices_.push_back(vec.y());
			vertices_.push_back(vec.z());

			const QVector3D normal{ vec.normalized() };
			normals_.push_back(normal.x());
			normals_.push_back(normal.y());
			normals_.push_back(normal.z());


			const QVector2D texture_pos{ (static_cast<float>(x * 1.0 / clamped_subgrid_count_x)),
										(static_cast<float>(y * 1.0 / clamped_subgrid_count_y)) };

			texture_pos_.push_back(texture_pos.x());
			texture_pos_.push_back(texture_pos.y());

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

void cube_sphere::set_subgrid_count_x(size_t size)
{
	subdivision_x_ = size;
	set_subgrid_count(subdivision_x_, subdivision_y_);
}

void cube_sphere::set_subgrid_count_y(size_t size)
{
	subdivision_y_ = size;
	set_subgrid_count(subdivision_x_, subdivision_y_);
}

cube_sphere::cube_sphere(const size_t subgrid_count_x, const size_t subgrid_count_y, const QColor& color, const QVector3D& position,
	const QVector3D& rotation, float angle)
	: subdivision_x_(subgrid_count_x), subdivision_y_(subgrid_count_y), color_(color) {}
