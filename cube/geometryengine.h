#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

struct VertexData {
    QVector3D position;
    QVector3D color;
};

class GeometryEngine : protected QOpenGLFunctions {
public:
    GeometryEngine(QOpenGLShaderProgram *program);
    void drawCubeGeometry();

    void addColorToAll(QVector3D color);

private:
    void initCubeGeometry(QOpenGLShaderProgram *program);

    QOpenGLVertexArrayObject vao;
    GLuint vbo, ebo;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;

    VertexData default_vertices[8] = {
            {QVector3D(1.0,  1.0, 1.0), QVector3D(0, 1.0, 0)},	// Front Top Right          - Green
            {QVector3D(-1.0, 1.0, 1.0), QVector3D(1.0, 0, 0)},	// Front Top Left           - Red
            {QVector3D(1.0,  1.0,-1.0), QVector3D(1.0, 1.0, 0)},	// Back Top Right       - Yellow
            {QVector3D(-1.0, 1.0,-1.0), QVector3D(1.0, 0, 1.0)},	// Back Top Left        - Pink
            {QVector3D(1.0, -1.0, 1.0),QVector3D(0, 0, 1.0)},	// Front Bottom Right       - Blue
            {QVector3D(-1.0,-1.0, 1.0), QVector3D(0, 1.0, 1.0)},	// Front Bottom Left	- Cyan
            {QVector3D(-1.0,-1.0,-1.0), QVector3D(1.0, 1.0, 1.0)},	// Back Bottom Left		- Gray
            {QVector3D(1.0, -1.0,-1.0), QVector3D(0, 0, 0)}	// Back Bottom Right            - White
        };

    VertexData vertices[8];

    GLuint elements[14] {
        5, 4, 6, 7, 2, 4, 0, 5, 1, 6, 3, 2, 1, 0
    };
};

#endif // GEOMETRYENGINE_H
