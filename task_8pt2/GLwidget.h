#pragma once

#include <QColorDialog>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QPainter>
#include <queue>

#include "camera.h"
#include "light_ambient.h"
#include "light_directional.h"
#include "light_point.h"
#include "light_spotlight.h"
#include "renderable.h"
#include "road.h"

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
	GLint uniform_light_spotlight_direction = -1;
	GLint uniform_light_spotlight_angle_min = -1;
	GLint uniform_light_spotlight_angle_max = -1;

	GLint uniform_texture0_enabled = -1;
	GLint uniform_texture2_enabled = -1;
	GLint uniform_texture1_enabled = -1;
	GLint uniform_texture3_enabled = -1;
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


	
	bool is_wireframe_ = false;
	bool is_animation_enabled_ = true;
	bool ambient_enabled_ = false;
	bool point_enabled_ = false;
	bool directional_enabled_ = false;
	bool spotlight_enabled_ = false;

	std::vector<size_t> fps_avg_buffer_;

	QColor color = {0xff, 0xff, 0xff};
	size_t count_ = 1;
	
    const QString vertShaderLocation_ = ":/shaders/vertexShaderSourceEarth.vert";
    const QString fragShaderLocation_ = ":/shaders/fragmentShaderSourceEarth.frag";
    bool texture_asphalt_enabled_ = false;
    bool texture_lines_enabled_ = false;
    bool texture_sand_enabled_ = false;

	
	road my_road_{ {255,255,255},11, 1000,{}, QVector3D{0,0,1}, 180, {1,500,1}};
//    Mesh my_mesh_{{255,255,255}, {}, {1,0,0}, {}, {0.2f, 0.2f, 0.2f}};
	

public slots:
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

	void toggle_texture_asphalt(bool value);
	void toggle_texture_lines(bool value);
	void toggle_texture_sand(bool value);

	void anti(bool);
	void enable_lin();
	void enable_near();
	void enable_bal();

public:
	explicit GLWidget(QWidget* parent);
	~GLWidget();
	
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

	void update();
};

