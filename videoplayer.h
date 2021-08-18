#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include<QProcess>
#include<QWidget>
class videoplayer : public QMainWindow
{
    Q_OBJECT
public:
    explicit videoplayer(QWidget *parent = nullptr);

signals:
private:
    QProcess*process;
    QString arg;
    QString fileName;
};

#endif // VIDEOPLAYER_H
