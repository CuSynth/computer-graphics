#pragma once
#include <QVector3D>

class camera
{
	QVector3D position_;
	QVector3D direction_;
public:
	camera(const QVector3D& position = {}, const QVector3D& direction = {});

	[[nodiscard]] QVector3D pos() const;
	[[nodiscard]] QVector3D direction() const;
};

