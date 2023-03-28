#pragma once
#include <QVector3D>
#include <QKeyEvent>

class camera
{
	QVector3D position_;
	QVector3D direction_;

public:
	camera(const QVector3D& position = {}, const QVector3D& direction = {});
	void set_pos(const QVector3D& position);
	void set_direction(const QVector3D& direction);

    [[nodiscard]] QVector3D pos() const;
    [[nodiscard]] QVector3D direction() const;

};

