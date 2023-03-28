#pragma once
#include <QVector3D>

#include "basic_light.h"
class light_spotlight :
    public basic_light
{
	QVector3D position_;
	QVector3D direction_;
	float angle_min_;
	float angle_max_;
public:
	light_spotlight() = default;
	light_spotlight
	(
		const QVector3D& position,
		const QVector3D& direction,
		float angle_min,
		float angle_max,
		const QColor& color,
		float intensity
	);
	QVector3D position() const;
	QVector3D direction() const;
	float angle_min() const;
	float angle_max() const;
	
	void set_position(const QVector3D& position);
	void set_direction(const QVector3D& direction);
	void set_angle_min(float angle);
	void set_angle_max(float angle);
};

