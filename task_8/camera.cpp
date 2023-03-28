#include "camera.h"
#include <glm/glm.hpp>

camera::camera(const QVector3D& position, const QVector3D& direction) :position_(position), direction_(direction) {}

QVector3D camera::pos()
{
	return position_;
}

void camera::calc() {
    QVector3D dir(cos(glm::radians(pitch_)) * cos(glm::radians(yaw_)),
                  sin(glm::radians(yaw_)),
                  sin(glm::radians(pitch_)) * cos(glm::radians(yaw_)));
    cameraFront = dir.normalized();
}

QVector3D camera::direction()
{
    calc();
    return cameraFront;
}

void camera::keyEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Up) {
        position_ += cameraFront* linear_speed;
    }

    if (event->key()==Qt::Key_Down) {
        position_ -= cameraFront * linear_speed;
    }

    if (event->key()==Qt::Key_Left) {
        position_ -= QVector3D::crossProduct(cameraFront, cameraUp).normalized() * linear_speed;
    }

    if (event->key()==Qt::Key_Right) {
        position_ += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * linear_speed;
    }


   if (event->key()==Qt::Key_A) {
       yaw_+=angular_speed;
       calc();
   }
   if (event->key()==Qt::Key_D) {
       yaw_-=angular_speed;
       calc();
   }


   if (event->key()==Qt::Key_W) {
       pitch_+=angular_speed;
       calc();
   }
   if (event->key()==Qt::Key_S) {
       pitch_-=angular_speed;
       calc();
   }
}
