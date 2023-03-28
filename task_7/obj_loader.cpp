#include "obj_loader.h"
#include <iostream>
#include <fstream>
//#include <glm/glm.hpp>

using std::vector;
using std::string;

struct VertRef
{
    VertRef( int v, int vt, int vn ) : v(v), vt(vt), vn(vn) { }
    int v, vt, vn;
};

GLuint objloader::load(const QString &filename)
{
    vector<string>().swap(coord);

    vector<QVector3D>().swap(vertex);
    vector<QVector2D>().swap(uvs);
    vector<QVector3D>().swap(normals);
    vector<face>().swap(faces);

    QFile in(filename);

    if(!in.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Не удалось открыть файл с моделью!";
    }

    QTextStream iqfs(&in);


    std::string lineStr;
    while(!iqfs.atEnd())
    {
        lineStr = iqfs.readLine().toStdString();
        std::istringstream lineSS( lineStr );
        std::string lineType;
        lineSS >> lineType;

        // vertex
        if( lineType == "v" )
        {
            float x = 0, y = 0, z = 0, w = 1;
            lineSS >> x >> y >> z;
            vertex.push_back( QVector3D( x, y, z ) );
        }

        if( lineType == "vt" )
        {
            float u = 0, v = 0;
            lineSS >> u >> v;
            uvs.push_back( QVector2D( u, v ) );
        }

        // normal
        if( lineType == "vn" )
        {
            float i = 0, j = 0, k = 0;
            lineSS >> i >> j >> k;
            normals.push_back( QVector3D( i, j, k ) );
        }


        if( lineType == "f" )
        {
            std::vector< QVector3D > refs;
            std::string refStr;
            while( lineSS >> refStr )
            {
                std::istringstream ref( refStr );
                std::string vStr, vtStr, vnStr;
                std::getline( ref, vStr, '/' );
                std::getline( ref, vtStr, '/' );
                std::getline( ref, vnStr, '/' );
                int v = atoi( vStr.c_str() );
                int vt = atoi( vtStr.c_str() );
                int vn = atoi( vnStr.c_str() );
                v  = (  v >= 0 ?  v : vertex.size() +  v );
                vt = ( vt >= 0 ? vt : uvs.size() + vt );
                vn = ( vn >= 0 ? vn : normals.size()   + vn );
                refs.push_back( QVector3D( v, vt, vn ) );
            }

            face::vertex v1(refs[0].x(),refs[0].y(),refs[0].z());
            face::vertex v2(refs[1].x(),refs[1].y(),refs[1].z());
            face::vertex v3(refs[2].x(),refs[2].y(),refs[2].z());

            faces.push_back(face(v1,v2,v3));     // записываю грань в массив
        }
    }


    GLuint num = draw();

    return num;
}

GLuint objloader::draw(GLfloat offset)
{
    GLuint num = glGenLists(1);
    glNewList(num,GL_COMPILE);
    size_t N_faces = faces.size();
    for(size_t i=0; i < N_faces; ++i)
    {
        face f = faces[i];

        glBegin(GL_TRIANGLES);




        QVector3D normal = normals[f.v[0].vn_i - 1];
        glNormal3f(normal.x(), normal.y(), normal.z());
        //glTexCoord2f(0.5f*(normal.x()+1), 0.5f*(normal.y()+1)); // построение текстурной вершины по вершине нормали, дает другое наложение текстуры на модель
        glTexCoord2f(uvs[f.v[0].vt_i - 1].x()+offset, uvs[f.v[0].vt_i - 1].y()+offset);
        glVertex3f(vertex[f.v[0].v_i - 1].x(),vertex[f.v[0].v_i - 1].y(),vertex[f.v[0].v_i - 1].z()); // читаем текстурную вершину из файла

        normal = normals[f.v[1].vn_i - 1];
        glNormal3f(normal.x(), normal.y(), normal.z());
        //glTexCoord2f(0.5f*(normal.x()+1), 0.5f*(normal.y()+1));
        glTexCoord2f(uvs[f.v[1].vt_i - 1].x()+offset, uvs[f.v[1].vt_i - 1].y()+offset);
        glVertex3f(vertex[f.v[1].v_i - 1].x(),vertex[f.v[1].v_i - 1].y(),vertex[f.v[1].v_i - 1].z());

        normal = normals[f.v[2].vn_i - 1];
        glNormal3f(normal.x(), normal.y(), normal.z());
        //glTexCoord2f(0.5f*(normal.x()+1), 0.5f*(normal.y()+1));
        glTexCoord2f(uvs[f.v[2].vt_i - 1].x()+offset, uvs[f.v[2].vt_i - 1].y()+offset);
        glVertex3f(vertex[f.v[2].v_i - 1].x(),vertex[f.v[2].v_i - 1].y(),vertex[f.v[2].v_i - 1].z());

        glEnd();
    }
    glEndList();
    return num;     // возвращаем номер дисплей листа
}


