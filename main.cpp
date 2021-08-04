#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QProgressBar>
#include <QSlider>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow  window;

    window.show();

    return a.exec();
}
