#include "GLMainWindow.h"


GLMainWindow::GLMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.cb_anti, &QCheckBox::toggled, ui.widget, &GLWidget::anti);
    connect(ui.rb_lin, &QCheckBox::toggled, ui.widget, &GLWidget::enable_lin);
    connect(ui.rb_near, &QCheckBox::toggled, ui.widget, &GLWidget::enable_near);
    connect(ui.rb_bal, &QCheckBox::toggled, ui.widget, &GLWidget::enable_bal);

    connect(ui.bt_start_stop, &QPushButton::clicked, ui.widget, &GLWidget::toggle_animation);
    connect(ui.cam_pos_x, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_cam_pos_x);
    connect(ui.cam_pos_y, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_cam_pos_y);
    connect(ui.cam_pos_z, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_cam_pos_z);

    ui.widget->set_cam_pos_x(ui.cam_pos_x->value());
    ui.widget->set_cam_pos_y(ui.cam_pos_y->value());
    ui.widget->set_cam_pos_z(ui.cam_pos_z->value());

    connect(ui.cb_wireframe, &QCheckBox::toggled, ui.widget, &GLWidget::toggle_wireframe);
    connect(ui.bt_background_color, &QPushButton::clicked, ui.widget, &GLWidget::set_background_color);

    //ambient
    connect(ui.cb_ambient_enabled, &QCheckBox::toggled, ui.widget, &GLWidget::toggle_ambient);
    connect(ui.sb_ambient_intensity, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_ambient_intensity);
    connect(ui.bt_ambient_color, &QPushButton::clicked, ui.widget, &GLWidget::set_ambient_color);

    ui.cb_ambient_enabled->setChecked(true);
    ui.widget->toggle_ambient(true);
    ui.sb_ambient_intensity->setValue(3);
    ui.widget->set_ambient_intensity(3);

	//point
	connect(ui.cb_point_enabled, &QCheckBox::toggled, ui.widget, &GLWidget::toggle_point);
    connect(ui.sb_point_intensity, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_point_intensity);
    connect(ui.bt_point_color, &QPushButton::clicked, ui.widget, &GLWidget::set_point_color);
	connect(ui.sb_point_pos_x, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_point_position_x);
    connect(ui.sb_point_pos_y, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_point_position_y);
    connect(ui.sb_point_pos_z, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_point_position_z);
    

	//directional
    connect(ui.cb_directional_enabled, &QCheckBox::toggled, ui.widget, &GLWidget::toggle_directional);
    connect(ui.sb_directional_intensity, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_directional_intensity);
    connect(ui.sb_directional_dir_x, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_directional_direction_x);
    connect(ui.sb_directional_dir_y, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_directional_direction_y);
    connect(ui.sb_directional_dir_z, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_directional_direction_z);
	connect(ui.bt_directional_color, &QPushButton::clicked, ui.widget, &GLWidget::set_directional_color);

	//spotlight
    connect(ui.cb_spotlight_enabled, &QCheckBox::toggled, ui.widget, &GLWidget::toggle_spotlight);
    connect(ui.sb_spotlight_intensity, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_intensity);
    connect(ui.sb_spotlight_pos_x, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_position_x);
    connect(ui.sb_spotlight_pos_y, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_position_y);
    connect(ui.sb_spotlight_pos_z, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_position_z);	
	connect(ui.sb_spotlight_dir_x, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_direction_x);
    connect(ui.sb_spotlight_dir_y, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_direction_y);
    connect(ui.sb_spotlight_dir_z, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_direction_z);
    connect(ui.sb_spotlight_min_angle, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_angle_min);
    connect(ui.sb_spotlight_max_angle, &QDoubleSpinBox::valueChanged, ui.widget, &GLWidget::set_spotlight_angle_max);
	connect(ui.bt_spotlight_color, &QPushButton::clicked, ui.widget, &GLWidget::set_spotlight_color);

    
    ui.widget->set_point_intensity(ui.sb_point_intensity->value());
    ui.widget->set_point_position_x(ui.sb_point_pos_x->value());
    ui.widget->set_point_position_y(ui.sb_point_pos_y->value());
    ui.widget->set_point_position_z(ui.sb_point_pos_z->value());

    ui.widget->setFocusPolicy(Qt::StrongFocus);

}
