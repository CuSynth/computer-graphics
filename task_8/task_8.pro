QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GLMainWindow.cpp \
    GLWidget.cpp \
    basic_light.cpp \
    camera.cpp \
    cube.cpp \
    cube_sphere.cpp \
    geo_sphere.cpp \
    light_ambient.cpp \
    light_directional.cpp \
    light_point.cpp \
    light_spotlight.cpp \
    main.cpp \
    plane.cpp \
    textured_plane.cpp

HEADERS += \
    GLMainWindow.h \
    GLWidget.h \
    RenderWindow.h \
    basic_light.h \
    camera.h \
    cube.h \
    cube_sphere.h \
    geo_sphere.h \
    light_ambient.h \
    light_directional.h \
    light_point.h \
    light_spotlight.h \
    plane.h \
    renderable.h \
    textured_plane.h

FORMS += \
    qtwidgetsapplication1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Shaders.qrc \
    materials.qrc

DISTFILES += \
    Materials/Earth1k.jpg \
    Materials/Earth8k.jpg \
    Materials/Earth8k_night.jpg \
    Materials/Earth8k_normal.jpg \
    Materials/Earth_Albedo.jpg \
    Materials/Earth_NormalMap.jpg \
    Materials/MeshCube.mtl \
    Materials/MeshHouse.mtl \
    Materials/MeshSphere.mtl \
    Materials/MoonColor.jpg \
    Materials/MoonDis.jpg \
    shaders/fragmentShaderSourceEarth.frag \
    shaders/vertexShaderSourceEarth.vert
