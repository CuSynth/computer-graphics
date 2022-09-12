#include "geometryengine.h"

#include <QColor>

GeometryEngine::GeometryEngine(size_t _factor)
    : arrayBuf(QOpenGLBuffer::VertexBuffer),
      indexBuf(QOpenGLBuffer::IndexBuffer) {

  initializeOpenGLFunctions();

  arrayBuf.create();
  indexBuf.create();

  initCubeGeometry(1.0f, _factor);
}

GeometryEngine::~GeometryEngine() {
  arrayBuf.destroy();
  indexBuf.destroy();
}

void GeometryEngine::initCubeGeometry(float width, unsigned int factor, bool colored) {

    if (arrayBuf.isCreated())
      arrayBuf.destroy();
    arrayBuf.create();

    if (indexBuf.isCreated())
      indexBuf.destroy();
    indexBuf.create();

    // Create a vector of vertices
    // Each edge will consist of (factor) edges (i.e. (factor+1) vertices on each edge).
    auto half_width = width / 2.0f;
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    for (auto face = 0U; face < 6; ++face) {
        // constCoord describes the plain where current face is placed.
        const auto constCoord = face % 3;
        const auto coord1 = (face + 1) % 3;
        const auto coord2 = (face + 2) % 3;

        for (auto y = 0U; y < factor + 1; ++y) {
            for (auto x = 0U; x < factor + 1; ++x) {

                auto position = QVector3D{0, 0, 0};
                auto normal = QVector3D{0, 0, 0};

                // normal[constCoord] will be (-1) for faces number 0, 1, 2 and (+1) for 3, 4, 5.
                normal[constCoord] = int(face / 3 * 2) - 1;
                // So, each face will have its own normal.

                position[constCoord] = normal[constCoord] * half_width;
                // Now we have to fit (factor-1) vertices into one edge,
                // between cube corners.
                position[coord1] = (x * 2.0F / factor - 1.0F) * half_width;
                position[coord2] =
                (y * 2.0F / factor - 1.0F) * half_width * normal[constCoord];

                auto color = QColor{};
                if(colored) {
                    color.setRedF((x + y + face) % 4 / 3.0F);
                    color.setGreenF((x + y + face + 3) % 4 / 3.0F);
                    color.setBlueF((x + y + face + 6) % 4 / 3.0F);
                }
                else {
                    color.setRedF(0.3);
                    color.setGreenF(0.7);
                    color.setBlueF(0.9);
                }

                vertexes.append(
                VertexData(QVector3D(position.x(), position.y(), position.z()),
                    QVector3D(normal.x(), normal.y(), normal.z()),
                    QVector3D(color.redF(), color.greenF(), color.blueF())));
            }
        }

        const auto faceIndexOffset = face * (factor + 1) * (factor + 1);
        for (auto y = 0U; y < factor; ++y) {
            const auto rowIndexOffset = (factor + 1) * y;

            indexes.append(faceIndexOffset + rowIndexOffset);
            for (auto x = 0U; x < factor + 1; ++x) {
                indexes.append(faceIndexOffset + rowIndexOffset + x);
                indexes.append(faceIndexOffset + rowIndexOffset + x + (factor + 1));
            }
            indexes.append(faceIndexOffset + rowIndexOffset + factor + (factor + 1));
        }
    }

    arrayBuf.bind();
    arrayBuf.allocate(vertexes.constData(), vertexes.size()*sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(indexes.constData(), indexes.size()*sizeof(GLuint));

}

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program) {
    arrayBuf.bind();
    indexBuf.bind();

    program->setUniformValue("offset_from_face", 0.0f);
    program->setUniformValue("frag_color_factor", 0.0f);

    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("vertex_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                                sizeof(VertexData));

    offset += sizeof(QVector3D);

    int vertexNormal = program->attributeLocation("vertex_normal");
    program->enableAttributeArray(vertexNormal);
    program->setAttributeBuffer(vertexNormal, GL_FLOAT, offset, 3,
                                sizeof(VertexData));

    offset += sizeof(QVector3D);

    int vertexColor = program->attributeLocation("vertex_color");
    program->enableAttributeArray(vertexColor);
    program->setAttributeBuffer(vertexColor, GL_FLOAT, offset, 3,
                                sizeof(VertexData));

    glDrawElements(GL_QUAD_STRIP, indexBuf.size(), GL_UNSIGNED_INT, nullptr);

    arrayBuf.bind();
    indexBuf.bind();

    program->setUniformValue("offset_from_face", 1.0e-3f);
    program->setUniformValue("frag_color_factor", 1.0f);

    glDrawElements(GL_LINE_STRIP, indexBuf.size(), GL_UNSIGNED_INT, nullptr);

    program->disableAttributeArray("vertex_position");
    program->disableAttributeArray("vertex_normal");
    program->disableAttributeArray("vertex_color");

    arrayBuf.release();
    indexBuf.release();
}
