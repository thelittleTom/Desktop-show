#include "mainwindow.h"
#include <QApplication>
#include<QDebug>
#include<QStandardPaths>
#include<QClipboard>
#include<string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
