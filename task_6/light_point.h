#pragma once
#include <QVector3D>

#include "basic_light.h"
class light_point :
	public basic_light
{
	QVector3D position_;
public:
	light_point() = default;
	light_point
	(
		const QVector3D& position,
		const QColor& color,
		float intensity
	);
	QVector3D position() const;
	void set_position(const QVector3D& position);
};

