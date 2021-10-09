#ifndef FRAME_CREATE_H
#define FRAME_CREATE_H
#include<QThread>
#include<QFile>
#include<QDateTime>
#include <QWidget>
#include<wallpaper.h>

class frame_create :public QThread
{
    Q_OBJECT
public:
    vipath *vip;
    frame_create(vipath *,QWidget *parent = nullptr);
signals:
    void signal_frame();

protected:
    void run();
private:
};

#endif // FRAME_CREATE_H
