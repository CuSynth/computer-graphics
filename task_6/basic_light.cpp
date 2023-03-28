#include "basic_light.h"

basic_light::basic_light(const QColor& color, const float intensity):
color_(color), intensity_(intensity){}

QColor basic_light::color() const
{
	return color_;
}

float basic_light::intensity() const
{
	return intensity_;
}

void basic_light::set_color(const QColor& color)
{
	color_ = color;
}

void basic_light::set_intensity(const float value)
{
	intensity_ = value;
}

