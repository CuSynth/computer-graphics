#include "light_point.h"

light_point::light_point
(const QVector3D& position, const QColor& color, const float intensity)
	: basic_light(color, intensity), position_(position) {}

QVector3D light_point::position() const
{
	return position_;
}

void light_point::set_position(const QVector3D& position)
{
	position_ = position;
}
