#pragma once

#include <QColorDialog>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QPainter>
#include <queue>

#include "camera.h"
#include "cube.h"
#include "cube_sphere.h"
#include "geo_sphere.h"
#include "light_ambient.h"
#include "light_directional.h"
#include "light_point.h"
#include "light_spotlight.h"
#include "renderable.h"

class GLWidget : public QOpenGLWidget
{
	Q_OBJECT;

	//attribute locations
	GLint view_ = 0;
	GLint uniform_morph_value_ = 0;
	GLint uniform_cam_matrix_ = 0;

	GLint uniform_light_ambient_enabled = 0;
	GLint uniform_light_ambient_intensity = 0;
	GLint uniform_light_ambient_color = 0;
	//point light
	GLint uniform_light_point_enabled = 0;
	GLint uniform_light_point_intensity = 0;
	GLint uniform_light_point_color = 0;
	GLint uniform_light_point_position = 0;
	//directional light
	GLint uniform_light_directional_enabled = 0;
	GLint uniform_light_directional_intensity = 0;
	GLint uniform_light_directional_color = 0;
	GLint uniform_light_directional_direction = 0;

	//spotlight
	GLint uniform_light_spotlight_enabled = 0;
	GLint uniform_light_spotlight_intensity = 0;
	GLint uniform_light_spotlight_color = 0;
	GLint uniform_light_spotlight_position = 0;
	GLint uniform_light_spotlight_direction = 0;
	GLint uniform_light_spotlight_angle_min = 0;
	GLint uniform_light_spotlight_angle_max = 0;

	GLint uniform_texture_map_enabled = 0;
	GLint uniform_normal_map_enabled = 0;
	//miscellaneous
	size_t frame_index = 0;
	QOpenGLShaderProgram* program_ = nullptr;
	camera cam_{};

	light_ambient ambient_;
	light_point point_light_;
	light_spotlight spotlight_;
	light_directional directional_light_;

	//display parameters
	QTimer timer_;
	QColor background_color_ = { 110, 168, 224 };
	QColorDialog dialog_;
	QElapsedTimer frametimer_;
	
	//std::shared_ptr<cube> my_cube;
	float morph_value_ = 0.0f;
	bool is_wireframe_ = false;
	bool is_animation_enabled_ = true;
	bool ambient_enabled_ = false;
	bool point_enabled_ = false;
	bool directional_enabled_ = false;
	bool spotlight_enabled_ = false;
	size_t current_subdivision_x_ = 1;
	size_t current_subdivision_y_ = 1;

	std::vector<size_t> fps_avg_buffer_;

	QColor color = {0xff, 0xff, 0xff};
	size_t count_ = 1;
	
    const QString vertShaderLocation_ = ":/shaders/vertexShaderSourceEarth.vert";
    const QString fragShaderLocation_ = ":/shaders/fragmentShaderSourceEarth.frag";
//	cube my_cube_{ 10, QColor{255,0,0} };
	bool texture_map_enabled_ = true;
	bool night_map_enabled_ = true;
	bool normal_map_enabled_ = true;

	geo_sphere my_sphere_{};
//	cube_sphere my_cube_sphere_ {};
	GLint uniform_texture_night_map_enabled = -1;

public slots:
	void set_obj_count(int); //unused
	void set_morphing_value(float); //unused
	void set_subdivision_x(int size);
	void set_subdivision_y(int size);
	void toggle_wireframe(bool);
	void toggle_animation(bool);
	void set_color();
	void set_background_color();

	void set_cam_pos_x(float);
	void set_cam_pos_y(float);
	void set_cam_pos_z(float);

	void toggle_ambient(bool);
	void set_ambient_intensity(float value);
	void set_ambient_color();

	void toggle_point(bool);
	void set_point_intensity(float value);
	void set_point_color();
	void set_point_position_x(float value);
	void set_point_position_y(float value);
	void set_point_position_z(float value);

	void toggle_directional(bool);
	void set_directional_intensity(float value);
	void set_directional_color();
	void set_directional_direction_x(float value);
	void set_directional_direction_y(float value);
	void set_directional_direction_z(float value);

	void toggle_spotlight(bool);
	void set_spotlight_intensity(float value);
	void set_spotlight_color();
	void set_spotlight_position_x(float value);
	void set_spotlight_position_y(float value);
	void set_spotlight_position_z(float value);
	void set_spotlight_direction_x(float value);
	void set_spotlight_direction_y(float value);
	void set_spotlight_direction_z(float value);
	void set_spotlight_angle_min(float angle);
	void set_spotlight_angle_max(float angle);

	void toggle_texture_map(bool value);
	void toggle_texture_night_map(bool value);
	void toggle_normal_map(bool value);

public:
	explicit GLWidget(QWidget* parent);
	~GLWidget();
	
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

	void update();
};

