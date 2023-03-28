#pragma once
#include <QVector3D>

#include "basic_light.h"

class light_directional :
	public basic_light
{
	QVector3D direction_;
public:
	light_directional() = default;
	light_directional
	(
		const QVector3D& direction,
		const QColor& color,
		float intensity
	);
	
	QVector3D direction() const;
	void set_direction(const QVector3D& direction);
};

