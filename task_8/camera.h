#pragma once
#include <QVector3D>
#include <QKeyEvent>

class camera
{
	QVector3D position_;
	QVector3D direction_;

    QVector3D cameraFront{1.0f, 0.0f, 0.0f};
    QVector3D cameraUp{0.0f, 0.0f,  1.0f};

    float cam_pos_x = 0.0;
    float cam_pos_y = 0.0;

    float yaw_ = 0.0;
    float pitch_ = 0.0;

    float linear_speed = 0.1;
    float angular_speed = 1.0;

public:
	camera(const QVector3D& position = {}, const QVector3D& direction = {});

    QVector3D pos();
    QVector3D direction();
    QVector3D up() { return cameraUp; }
    void calc();

    void keyEvent(QKeyEvent *event);
};

