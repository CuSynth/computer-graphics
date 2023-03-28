#include "light_spotlight.h"

light_spotlight::light_spotlight
(
	const QVector3D& position,
	const QVector3D& direction,
	const float angle_min,
	const float angle_max,
	const QColor& color,
	const float intensity
)
	:basic_light(color, intensity),
	position_(position),
	direction_(direction),
	angle_min_(angle_min),
	angle_max_(angle_max)
	{}

QVector3D light_spotlight::position() const
{
	return position_;
}

QVector3D light_spotlight::direction() const
{
	return direction_;
}

float light_spotlight::angle_min() const
{
	return angle_min_;
}

float light_spotlight::angle_max() const
{
	return angle_max_;
}

void light_spotlight::set_position(const QVector3D& position)
{
	position_ = position;
}

void light_spotlight::set_direction(const QVector3D& direction)
{
	direction_ = direction;
}

void light_spotlight::set_angle_min(float angle)
{
	angle_min_ = angle;
}

void light_spotlight::set_angle_max(float angle)
{
	angle_max_ = angle;
}
