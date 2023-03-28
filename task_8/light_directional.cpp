#include "light_directional.h"

light_directional::light_directional
(
	const QVector3D& direction,
	const QColor& color,
	const float intensity
)
	:basic_light(color, intensity), direction_(direction) {}

QVector3D light_directional::direction() const
{
	return direction_;
}

void light_directional::set_direction(const QVector3D& direction)
{
	direction_ = direction;
}
