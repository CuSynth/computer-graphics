#pragma once
#include <QColor>

class basic_light
{
protected:
	QColor color_ = { 255,255,255 };
	float intensity_ = 1.0f;
public:
	basic_light() = default;
	basic_light(const QColor& color, float intensity = 1.0f);
	QColor color() const;
	float intensity() const;
	
	void set_color(const QColor& color);
	void set_intensity(float value);
};

