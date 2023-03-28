#pragma once
#include "basic_light.h"
class light_ambient :
    public basic_light
{
public:
	light_ambient() = default;
	light_ambient
	(
		const QColor & color,
		float intensity
	);
};

