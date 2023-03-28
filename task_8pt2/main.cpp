#include "GLMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLMainWindow w;

    w.setAnimated(true);
	w.show();
    return a.exec();
}
