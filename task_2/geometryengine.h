#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

struct VertexData {
  VertexData(QVector3D p, QVector3D n, QVector3D c)
      : position(p), normal(n), colour(c) {}
  QVector3D position;
  QVector3D normal;
  QVector3D colour;
};

class GeometryEngine : protected QOpenGLFunctions {
public:
    GeometryEngine(size_t _factor = 1);
    virtual ~GeometryEngine();

    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void initCubeGeometry(float width, unsigned int factor, bool colored=false);

private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

#endif // GEOMETRYENGINE_H
