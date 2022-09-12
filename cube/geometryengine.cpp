/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>

GeometryEngine::GeometryEngine(QOpenGLShaderProgram *program) {
    initializeOpenGLFunctions();
    for(size_t i = 0; i < 8; ++i) {
        vertices[i] = default_vertices[i];
    }

    initCubeGeometry(program);
}

void GeometryEngine::addColorToAll(QVector3D color) {

    for(size_t i = 0; i < sizeof(vertices)/sizeof(VertexData); ++i) {       // For every vertex
        for(size_t j = 0; j < 3; ++j) {                                     // For every color component
            vertices[i].color[j] = default_vertices[i].color[j] + color[j]; // Just add new value to default component
            if(vertices[i].color[j] > 1)
                vertices[i].color[j] = 1;
            if(vertices[i].color[j] < 0)
                vertices[i].color[j] = 0;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void GeometryEngine::initCubeGeometry(QOpenGLShaderProgram *program) {
    m_posAttr = program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = program->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);

    // Set OpenGL up
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);

    // Initialize Vertex Array, Vertex Buffer and Element Buffer objects
    vao.create();
    vao.bind();

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glEnableVertexAttribArray(m_posAttr);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);

    glEnableVertexAttribArray(m_colAttr);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE,  sizeof(VertexData), (char*)offsetof(VertexData, color));

}

void GeometryEngine::drawCubeGeometry() {
    // Set background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawElements(GL_TRIANGLE_STRIP, sizeof(elements)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
}
