#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Window最大化で起動させる
    w.setWindowState(w.windowState() ^ Qt::WindowMaximized);

    w.show();

    return a.exec();
}
