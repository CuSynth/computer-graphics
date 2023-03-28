#include "plane.h"

plane::plane(const QColor& color, const size_t count_x, const size_t count_y, const QVector3D& position, const QVector3D& rotation, float rotation_angle, const QVector3D& scale)
	: color_(color), position_(position), rotation_(rotation), rotation_angle_(rotation_angle), scale_(scale)
{
	set_subgrid_count(count_x, count_y);
}

void plane::render()
{
	//program_->setUniformValue(object_color, color_);

	glVertexAttribPointer(attr_pos_, 3, GL_FLOAT, GL_FALSE, 0, vertices_.data());
	glVertexAttribPointer(attr_normal_, 3, GL_FLOAT, GL_FALSE, 0, normals_.data());
	glVertexAttribPointer(attr_color_, 3, GL_FLOAT, GL_FALSE, 0, colors_.data());

	glEnableVertexAttribArray(attr_pos_);
	glEnableVertexAttribArray(attr_normal_);
	glEnableVertexAttribArray(attr_color_);
	
	glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_INT, indices_.data());

	glDisableVertexAttribArray(attr_pos_);
	glDisableVertexAttribArray(attr_normal_);
	glDisableVertexAttribArray(attr_color_);
}

void plane::set_subgrid_count(const size_t subgrid_count_x, const size_t subgrid_count_y)
{
	const auto clamped_subgrid_count_x = std::max(static_cast<size_t>(1), subgrid_count_x);
	const auto clamped_subgrid_count_y = std::max(static_cast<size_t>(1), subgrid_count_y);

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

	for (size_t y = 0; y <= clamped_subgrid_count_y; ++y)
	{
		for (size_t x = 0; x <= clamped_subgrid_count_x; ++x)
		{
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

void plane::set_color(const QColor& color)
{
	color_ = color;
	for (int i = 0; i < colors_.size(); i+=3)
	{
		colors_.at(i) = color_ .redF();
		colors_.at(i+1) = color.greenF();
		colors_.at(i+2) = color.blueF();
	}
}

void plane::initialize(QOpenGLShaderProgram* program)
{
	initializeOpenGLFunctions();
	program_ = program;

	//object_color = program_->uniformLocation("object_color");
	attr_pos_ = program_->attributeLocation("attr_pos");
	attr_normal_ = program_->attributeLocation("attr_normal");
	attr_color_ = program_->attributeLocation("attr_color");
}
