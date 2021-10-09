#include "mainwindow.h"
#include <QApplication>
#include<QDebug>
#include<QStandardPaths>
#include<QClipboard>
#include<string>
#include<wininfo.h>
#include<kwin.h>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusPendingCallWatcher>
#include <QtDBus/QDBusPendingReply>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
