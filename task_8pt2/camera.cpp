#include "camera.h"
#include <glm/glm.hpp>

camera::camera(const QVector3D& position, const QVector3D& direction) :position_(position), direction_(direction) {}

void camera::set_pos(const QVector3D& position)
{
	position_ = position;
}



void camera::set_direction(const QVector3D& direction)
{
    direction_ = direction;
}

QVector3D camera::pos() const
{
	return position_;
}

QVector3D camera::direction() const
{
    return direction_;
}
