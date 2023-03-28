#include "GLwidget.h"

#include <QScreen>
#include <iostream>
#include <fstream>
#include <QColorDialog>
#include <queue>


GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
	connect(&timer_, &QTimer::timeout, this, &GLWidget::update);
	ambient_ = {};
	point_light_ = {};
	spotlight_ = { };
	directional_light_ = {};
	frametimer_.start();
}

void GLWidget::initializeGL()
{
	delete program_;
	program_ = new QOpenGLShaderProgram(this);
	program_->addShaderFromSourceFile(QOpenGLShader::Vertex, vertShaderLocation_);
	program_->addShaderFromSourceFile(QOpenGLShader::Fragment, fragShaderLocation_);
	program_->link();
	view_ = program_->uniformLocation("view");
	uniform_cam_matrix_ = program_->uniformLocation("uniform_cam_matrix");
	uniform_morph_value_ = program_->uniformLocation("morph_value");

	//ambient
	uniform_light_ambient_enabled = program_->uniformLocation("uniform_light_ambient_enabled");
	uniform_light_ambient_intensity = program_->uniformLocation("uniform_light_ambient_intensity");
	uniform_light_ambient_color = program_->uniformLocation("uniform_light_ambient_color");

	//lighting point
	uniform_light_point_enabled = program_->uniformLocation("uniform_light_point_enabled");
	uniform_light_point_intensity = program_->uniformLocation("uniform_light_point_intensity");
	uniform_light_point_color = program_->uniformLocation("uniform_light_point_color");
	uniform_light_point_position = program_->uniformLocation("uniform_light_point_position");

	//lighting directional
	uniform_light_directional_enabled = program_->uniformLocation("uniform_light_directional_enabled");
	uniform_light_directional_intensity = program_->uniformLocation("uniform_light_directional_intensity");
	uniform_light_directional_color = program_->uniformLocation("uniform_light_directional_color");
	uniform_light_directional_direction = program_->uniformLocation("uniform_light_directional_direction");

	//lighting spotlight
	uniform_light_spotlight_enabled = program_->uniformLocation("uniform_light_spotlight_enabled");
	uniform_light_spotlight_intensity = program_->uniformLocation("uniform_light_spotlight_intensity");
	uniform_light_spotlight_color = program_->uniformLocation("uniform_light_spotlight_color");
	uniform_light_spotlight_position = program_->uniformLocation("uniform_light_spotlight_position");
	uniform_light_spotlight_direction = program_->uniformLocation("uniform_light_spotlight_direction");
	uniform_light_spotlight_angle_min = program_->uniformLocation("uniform_light_spotlight_angle_min");
	uniform_light_spotlight_angle_max = program_->uniformLocation("uniform_light_spotlight_angle_max");

	uniform_texture0_enabled = program_->uniformLocation("uniform_texture0_enabled");
	uniform_texture1_enabled = program_->uniformLocation("uniform_texture1_enabled");
	uniform_texture2_enabled = program_->uniformLocation("uniform_texture2_enabled");
	uniform_texture3_enabled = program_->uniformLocation("uniform_texture3_enabled");

	my_road_.initialize(program_);
//    my_mesh_.initialize(program_);
}

void GLWidget::paintGL()
{
	const auto frame_time = frametimer_.elapsed();
	const auto fps = 1000.0f / frame_time;
	static auto current_time = 0.0f;

	fps_avg_buffer_.push_back(fps);
	static size_t fps_avg = 0;
	if (fps_avg_buffer_.size() >= 10)
	{
		fps_avg = std::reduce(fps_avg_buffer_.begin(), fps_avg_buffer_.end())*1.0 / fps_avg_buffer_.size();
		fps_avg_buffer_.clear();
	}

	if (is_animation_enabled_)
	{
		current_time += frame_time;
	}
	frametimer_.start();

	glClearColor(background_color_.redF(), background_color_.greenF(), background_color_.blueF(), background_color_.alphaF());
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (is_wireframe_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	QMatrix4x4 view;
	const float ratio = width() * 1.0 / height();
	view.perspective(60, ratio, 0.1f, 10000.0f);
    view.lookAt(cam_.pos(), cam_.pos() + QVector3D{-1,0,0} , { 0,0,1 });

	QMatrix4x4 uniform_cam_matrix;
	uniform_cam_matrix.translate(cam_.pos());

	program_->bind();
	program_->setUniformValue(view_, view);
	program_->setUniformValue(uniform_cam_matrix_, uniform_cam_matrix);

    //ambient light
	program_->setUniformValue(uniform_light_ambient_enabled, ambient_enabled_);
	program_->setUniformValue(uniform_light_ambient_intensity, ambient_.intensity());
	program_->setUniformValue(uniform_light_ambient_color, ambient_.color());
	//point light
	program_->setUniformValue(uniform_light_point_enabled, point_enabled_);
	program_->setUniformValue(uniform_light_point_intensity, point_light_.intensity());
	program_->setUniformValue(uniform_light_point_color, point_light_.color());
	program_->setUniformValue(uniform_light_point_position, QVector4D(point_light_.position(), 1.0f));

	//directional
	program_->setUniformValue(uniform_light_directional_enabled, directional_enabled_);
	program_->setUniformValue(uniform_light_directional_intensity, directional_light_.intensity());
	program_->setUniformValue(uniform_light_directional_color, directional_light_.color());
	program_->setUniformValue(uniform_light_directional_direction, QVector4D(directional_light_.direction(), 1.0f));

	//spotlight
	program_->setUniformValue(uniform_light_spotlight_enabled, spotlight_enabled_);
	program_->setUniformValue(uniform_light_spotlight_intensity, spotlight_.intensity());
	program_->setUniformValue(uniform_light_spotlight_color, spotlight_.color());
	program_->setUniformValue(uniform_light_spotlight_position, QVector4D(spotlight_.position(), 1.0f));
	program_->setUniformValue(uniform_light_spotlight_direction, QVector4D(spotlight_.direction(), 1.0f));
	program_->setUniformValue(uniform_light_spotlight_angle_min, spotlight_.angle_min());
	program_->setUniformValue(uniform_light_spotlight_angle_max, spotlight_.angle_max());
	
	program_->setUniformValue(uniform_texture0_enabled, texture_lines_enabled_);
	program_->setUniformValue(uniform_texture1_enabled, texture_asphalt_enabled_);
	program_->setUniformValue(uniform_texture2_enabled, texture_sand_enabled_);

	program_->setUniformValue(uniform_texture0_enabled, false);
	program_->setUniformValue(uniform_texture1_enabled, false);
	program_->setUniformValue(uniform_texture2_enabled, false);



	static float xpos = -50.0f;
	if (is_animation_enabled_) { xpos -= 0.001f; }
	if (xpos<0.0f)
	{
		xpos = 50.0f;
	}

	auto prev_pos = cam_.pos();
	prev_pos.setX(xpos);
	cam_.set_pos(prev_pos);
	auto prev_spot_pos = spotlight_.position();
	prev_spot_pos.setX(xpos);
	spotlight_.set_position(prev_spot_pos);


	my_road_.render();

    const int count = 20;
    for (int i = -count; i < count; ++i)
    {
//        my_mesh_.set_position({-10*i*1.0f,0.5f,1});
//		my_mesh_.render();
    }



	program_->release();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	QPainter painter{ this };
	painter.setPen(Qt::red);
	painter.setFont(QFont("Arial", 16));
	painter.drawText(rect(), Qt::AlignLeft, "FPS: " + QString::number(std::round(fps_avg)));
	update();
}

void GLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void GLWidget::update()
{
	QOpenGLWidget::update();
}

void GLWidget::toggle_wireframe(const bool val)
{
	is_wireframe_ = val;
}

void GLWidget::toggle_animation(bool value)
{
	is_animation_enabled_ = !is_animation_enabled_;
}

void GLWidget::set_color()
{
	if (dialog_.exec() == QColorDialog::Accepted)
	{
		color = dialog_.currentColor();
	}
}

void GLWidget::set_background_color()
{
	if (dialog_.exec() == QColorDialog::Accepted)
	{
		background_color_ = dialog_.currentColor();
	}
}

void GLWidget::set_cam_pos_x(float value)
{
    const auto prev_cam = cam_;
    auto new_pos = prev_cam.pos();
    new_pos.setX(value);
    cam_ = { new_pos , prev_cam.direction()};
}

void GLWidget::set_cam_pos_y(float value)
{
    const auto prev_cam = cam_;
    auto new_pos = prev_cam.pos();
    new_pos.setY(value);
    cam_ = { new_pos , prev_cam.direction() };
}

void GLWidget::set_cam_pos_z(float value)
{
    const auto prev_cam = cam_;
    auto new_pos = prev_cam.pos();
    new_pos.setZ(value);
    cam_ = { new_pos , prev_cam.direction() };
}

void GLWidget::toggle_ambient(const bool value)
{
	ambient_enabled_ = value;
}

void GLWidget::set_ambient_intensity(float value)
{
	ambient_.set_intensity(value);
}

void GLWidget::set_ambient_color()
{
	if (dialog_.exec() == QColorDialog::Accepted)
	{
		ambient_.set_color(dialog_.currentColor());
	}
}

void GLWidget::toggle_point(const bool value)
{
	point_enabled_ = value;
}

void GLWidget::toggle_directional(const bool value)
{
	directional_enabled_ = value;
}

void GLWidget::toggle_spotlight(const bool value)
{
	spotlight_enabled_ = value;
}

void GLWidget::set_point_intensity(const float value)
{
	point_light_.set_intensity(value);
}

void GLWidget::set_point_position_x(const float value)
{
	auto new_pos{ point_light_.position() };
	new_pos.setX(value);
	point_light_.set_position(new_pos);
}

void GLWidget::set_point_position_y(const float value)
{
	auto new_pos{ point_light_.position() };
	new_pos.setY(value);
	point_light_.set_position(new_pos);
}

void GLWidget::set_point_position_z(const float value)
{
	auto new_pos{ point_light_.position() };
	new_pos.setZ(value);
	point_light_.set_position(new_pos);
}

void GLWidget::set_directional_intensity(const float value)
{
	directional_light_.set_intensity(value);
}

void GLWidget::set_directional_direction_x(float value)
{
	auto new_dir{ directional_light_.direction() };
	new_dir.setX(value);
	directional_light_.set_direction(new_dir);
}

void GLWidget::set_directional_direction_y(float value)
{
	auto new_dir{ directional_light_.direction() };
	new_dir.setY(value);
	directional_light_.set_direction(new_dir);
}

void GLWidget::set_directional_direction_z(float value)
{
	auto new_dir{ directional_light_.direction() };
	new_dir.setZ(value);
	directional_light_.set_direction(new_dir);
}

void GLWidget::set_spotlight_intensity(const float value)
{
	spotlight_.set_intensity(value);
}

void GLWidget::set_spotlight_position_x(float value)
{
	auto new_pos{ spotlight_.position() };
	new_pos.setX(value);
	spotlight_.set_position(new_pos);
}

void GLWidget::set_spotlight_position_y(float value)
{
	auto new_pos{ spotlight_.position() };
	new_pos.setY(value);
	spotlight_.set_position(new_pos);
}

void GLWidget::set_spotlight_position_z(float value)
{
	auto new_pos{ spotlight_.position() };
	new_pos.setZ(value);
	spotlight_.set_position(new_pos);
}

void GLWidget::set_spotlight_direction_x(float value)
{
	auto new_dir{ spotlight_.direction() };
	new_dir.setX(value);
	spotlight_.set_direction(new_dir);
}

void GLWidget::set_spotlight_direction_y(float value)
{
	auto new_dir{ spotlight_.direction() };
	new_dir.setY(value);
	spotlight_.set_direction(new_dir);
}

void GLWidget::set_spotlight_direction_z(float value)
{
	auto new_dir{ spotlight_.direction() };
	new_dir.setZ(value);
	spotlight_.set_direction(new_dir);
}

void GLWidget::set_spotlight_angle_min(float angle)
{
	spotlight_.set_angle_min(angle);
}

void GLWidget::set_spotlight_angle_max(float angle)
{
	spotlight_.set_angle_max(angle);
}

void GLWidget::toggle_texture_asphalt(const bool value)
{
	texture_asphalt_enabled_ = value;
}

void GLWidget::toggle_texture_lines(bool value)
{
	texture_lines_enabled_ = value;
}

void GLWidget::toggle_texture_sand(const bool value)
{
	texture_sand_enabled_ = value;
}

void GLWidget::anti(bool on)
{
	if (on)
	{
        my_road_.anti(32.0f);
	}
	else
	{
		my_road_.anti(0.0f);
	}
	
}

void GLWidget::enable_lin()
{
	my_road_.enable_lin();
}

void GLWidget::enable_near()
{
	my_road_.enable_near();
}

void GLWidget::enable_bal()
{
	my_road_.enable_balance();
}

void GLWidget::set_point_color()
{
	if (dialog_.exec() == QColorDialog::Accepted)
	{
		point_light_.set_color(dialog_.currentColor());
	}
}

void GLWidget::set_directional_color()
{
	if (dialog_.exec() == QColorDialog::Accepted)
	{
		directional_light_.set_color(dialog_.currentColor());
	}
}

void GLWidget::set_spotlight_color()
{
	if (dialog_.exec() == QColorDialog::Accepted)
	{
		spotlight_.set_color(dialog_.currentColor());
	}
}

GLWidget::~GLWidget()
{
	delete program_;
}

