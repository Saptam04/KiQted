#include <QApplication>
#include <QDebug>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setFixedSize(window.sizeHint());
//    window.resize(640, 256);
//    window.adjustSize();
    window.show();
    return app.exec();
}
