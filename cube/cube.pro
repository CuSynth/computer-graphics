QT += core gui widgets opengl openglwidgets
#QT += core gui openglwidgets


TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp

SOURCES += \
    cubewidget.cpp \
    geometryengine.cpp

HEADERS += \
    cubewidget.h \
    geometryengine.h \
    mainwindow.h

RESOURCES += \
    src/

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
#INSTALLS += target

DISTFILES += \
    MainwidgetForm.ui \
    src/shaders.frag \
    src/shaders.vert

#LIBS +=-lGLEW -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -lglfw -lOpenGL

FORMS += \
    mainwindow.ui
