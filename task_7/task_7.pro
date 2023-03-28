QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui opengl openglwidgets

CONFIG += c++11
LIBS += -lglut -lGLU
#QMAKE_CXXFLAGS += -lglut -lGLU -lGL

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    obj_loader.cpp \
    widget.cpp

HEADERS += \
    obj_loader.h \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    materials.qrc \
    materials.qrc
