#include "road.h"

#include <QOpenGLTexture>
#include <fstream>

road::road(const QColor& color, const size_t count_x, const size_t count_y, const QVector3D& position, const QVector3D& rotation, float rotation_angle, const QVector3D& scale)
	: color_(color), position_(position), rotation_(rotation), rotation_angle_(rotation_angle), scale_(scale)
{
	set_subgrid_count(count_x, count_y);
}

void road::render()
{
	program_->setUniformValue("uniform_texture0", 0);
	program_->setUniformValue("uniform_texture1", 1);
	program_->setUniformValue("uniform_texture2", 2);
	program_->setUniformValue("uniform_texture3", 3);

	//program_->setUniformValue(object_color, color_);
	assert(program_);
	QMatrix4x4 transformation;
	transformation.translate(position_);
	transformation.rotate(90, rotation_);
	program_->setUniformValue(object_transformation, transformation);

	glVertexAttribPointer(attr_pos_, 3, GL_FLOAT, GL_FALSE, 0, vertices_.data());
	glVertexAttribPointer(attr_normal_, 3, GL_FLOAT, GL_FALSE, 0, normals_.data());
	glVertexAttribPointer(attr_color_, 3, GL_FLOAT, GL_FALSE, 0, colors_.data());
	glVertexAttribPointer(attr_texture_pos_, 2, GL_FLOAT, GL_FALSE, 0, texture_pos_.data());

	glEnableVertexAttribArray(attr_pos_);
	glEnableVertexAttribArray(attr_normal_);
	glEnableVertexAttribArray(attr_color_);
	glEnableVertexAttribArray(attr_texture_pos_);

	glActiveTexture(GL_TEXTURE0 + 0);
	texture_road0->bind();
	glActiveTexture(GL_TEXTURE0 + 1);
	texture_road1->bind();
	glActiveTexture(GL_TEXTURE0 + 2);
	texture_road2->bind();
	glActiveTexture(GL_TEXTURE0 + 3);
	texture_road3->bind();
	glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_INT, indices_.data());
	texture_road0->release();
	texture_road1->release();
	texture_road2->release();
	texture_road3->release();

	glDisableVertexAttribArray(attr_pos_);
	glDisableVertexAttribArray(attr_normal_);
	glDisableVertexAttribArray(attr_color_);
	glDisableVertexAttribArray(attr_texture_pos_);
}

void road::set_subgrid_count(const size_t subgrid_count_x, const size_t subgrid_count_y)
{
	const auto clamped_subgrid_count_x = std::max(static_cast<size_t>(1), subgrid_count_x);
	const auto clamped_subgrid_count_y = std::max(static_cast<size_t>(1), subgrid_count_y);

	const GLfloat dlx = 1.0f / clamped_subgrid_count_x;
	const GLfloat dly = 1.0f / clamped_subgrid_count_y;
	QMatrix4x4 matrix;

	vertices_.clear();
	colors_.clear();
	indices_.clear();
	texture_pos_.clear();

	matrix.translate(position_);
	matrix.rotate(rotation_angle_, rotation_);
	matrix.scale(scale_);

	QMatrix4x4 normal_matrix;
	normal_matrix.rotate(rotation_angle_, rotation_);
	QVector3D normal{ 0,0,1};
	normal = normal_matrix * normal;
	srand(static_cast <unsigned> (time(0)));
	for (size_t y = 0; y <= clamped_subgrid_count_y; ++y)
	{
		for (size_t x = 0; x <= clamped_subgrid_count_x; ++x)
		{

			//const float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			const float k = 0.01f;
			//float height = -k * r;
			float dx = k * (-1.0f + 2 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			float dy = k * (-1.0f + 2 * static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			QVector3D local_normal = normal + QVector3D{dx, dy, 0};
			local_normal.normalize();	
			/*
			if (y == 0 || x == 0 || y == clamped_subgrid_count_y || x == clamped_subgrid_count_x)
			{
				height = 0;
				dx = 0;
				dy = 0;
			}*/

			//const float height = 0.0f;
			//QVector4D vec{ -0.5f + x * dlx + dx, -0.5f + y * dly + dy, height, 1 };
			QVector4D vec{ -0.5f + x * dlx, -0.5f + y * dly, 0, 1 };
			vec = matrix * vec;

			vertices_.push_back(vec.x());
			vertices_.push_back(vec.y());
			vertices_.push_back(vec.z());

			normals_.push_back(local_normal.x());
			normals_.push_back(local_normal.y());
			normals_.push_back(local_normal.z());


			//normals_.push_back(normal.x());
			//normals_.push_back(normal.y());
			//normals_.push_back(normal.z());

			colors_.push_back(color_.redF());
			colors_.push_back(color_.greenF());
			colors_.push_back(color_.blueF());

			texture_pos_.push_back(x * dlx);
			texture_pos_.push_back(y);
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

void road::set_color(const QColor& color)
{
	color_ = color;
	for (int i = 0; i < colors_.size(); i += 3)
	{
		colors_.at(i) = color_.redF();
		colors_.at(i + 1) = color.greenF();
		colors_.at(i + 2) = color.blueF();
	}
}

void road::anti(float s)
{
	//	QOpenGLTexture::AnisotropicFiltering

	texture_road0->setMaximumAnisotropy(s);
	texture_road1->setMaximumAnisotropy(s);
	texture_road2->setMaximumAnisotropy(s);
	texture_road3->setMaximumAnisotropy(s);
}

void road::enable_lin()
{
	texture_road0->setAutoMipMapGenerationEnabled(true);
	texture_road1->setAutoMipMapGenerationEnabled(true);
	texture_road2->setAutoMipMapGenerationEnabled(true);
	texture_road3->setAutoMipMapGenerationEnabled(true);
	texture_road0->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::LinearMipMapLinear);
	texture_road1->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::LinearMipMapLinear);
	texture_road2->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::LinearMipMapLinear);
	texture_road3->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::LinearMipMapLinear);
}

void road::enable_balance()
{
	texture_road0->setAutoMipMapGenerationEnabled(true);
	texture_road1->setAutoMipMapGenerationEnabled(true);
	texture_road2->setAutoMipMapGenerationEnabled(true);
	texture_road3->setAutoMipMapGenerationEnabled(true);

    auto min = QOpenGLTexture::Nearest;
    auto mag = QOpenGLTexture::Linear;

    texture_road0->setMinMagFilters(min, mag);
    texture_road1->setMinMagFilters(min, mag);
    texture_road2->setMinMagFilters(min, mag);
    texture_road3->setMinMagFilters(min, mag);
}

void road::enable_near()
{
	texture_road0->setAutoMipMapGenerationEnabled(false);
	texture_road1->setAutoMipMapGenerationEnabled(false);
	texture_road2->setAutoMipMapGenerationEnabled(false);
	texture_road3->setAutoMipMapGenerationEnabled(false);

	texture_road0->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
	texture_road1->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
	texture_road2->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
	texture_road3->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
}

void road::initialize(QOpenGLShaderProgram* program)
{
	initializeOpenGLFunctions();
	program_ = program;

	//object_color = program_->uniformLocation("object_color");
	attr_pos_ = program_->attributeLocation("attr_pos");
	attr_normal_ = program_->attributeLocation("attr_normal");
	attr_color_ = program_->attributeLocation("attr_color");
	attr_texture_pos_ = program_->attributeLocation("attr_texture_pos");
	object_transformation = program_->uniformLocation("object_transformation");

	delete texture_road0;
    texture_road0 = new QOpenGLTexture{ QImage(":/Materials/road_1.jpg") };
	//std::ofstream{ "text.test" };
    //texture_road0 = new QOpenGLTexture{ QImage{":/Materials/road_1.jpg"} };
	texture_road0->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture_road0->setMagnificationFilter(QOpenGLTexture::Linear);
	texture_road0->setWrapMode(QOpenGLTexture::WrapMode::Repeat);
	
	delete texture_road1;
    texture_road1 = new QOpenGLTexture{ QImage(":/Materials/road_2.jpg") };
	texture_road1->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture_road1->setMagnificationFilter(QOpenGLTexture::Linear);
	texture_road1->setWrapMode(QOpenGLTexture::WrapMode::Repeat);
	
	delete texture_road2;
    texture_road2 = new QOpenGLTexture{ QImage(":/Materials/road_3.jpg") };
	texture_road2->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture_road2->setMagnificationFilter(QOpenGLTexture::Linear);
	texture_road2->setWrapMode(QOpenGLTexture::WrapMode::Repeat);
	
	delete texture_road3;
    texture_road3 = new QOpenGLTexture{ QImage(":/Materials/sand.jpg") };
	texture_road3->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture_road3->setMagnificationFilter(QOpenGLTexture::Linear);
	texture_road3->setWrapMode(QOpenGLTexture::WrapMode::Repeat);
	
	uniform_texture0 = program_->uniformLocation("uniform_texture0");
	uniform_texture1 = program_->uniformLocation("uniform_texture1");
	uniform_texture2 = program_->uniformLocation("uniform_texture2");
	uniform_texture3 = program_->uniformLocation("uniform_texture3");

}

void road::set_position(const QVector3D& position)
{
	position_ = position;
}
