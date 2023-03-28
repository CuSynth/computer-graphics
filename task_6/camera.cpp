#include "camera.h"

camera::camera(const QVector3D& position, const QVector3D& direction) :position_(position), direction_(direction) {}

QVector3D camera::pos() const
{
	return position_;
}

QVector3D camera::direction() const
{
	return direction_;
}
