#ifndef WALLPAPER_H
#define WALLPAPER_H
#include "desktop_icon.h"
#include <QWidget>
#include <QApplication>
#include<QScreen>
#include<QRect>
#include<qmediaplaylist.h>
#include<QMediaPlayer>
#include<QVideoWidget>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QObject>
#include<QTimer>
#include<QTime>

struct vipath{
  QString videopath;
  QString imagepath;
  vipath(QString a="",QString b=""){videopath=a,imagepath=b;}
};
class wallpaper : public QMainWindow
{
    Q_OBJECT
public:
    vipath vipw;
    bool ifstart;
    QString filename;
    explicit wallpaper(QWidget *parent = nullptr);
    ~wallpaper();
    QMediaPlayer *player;
    QMediaPlaylist* playlist;
    QVideoWidget *videoWidget;
    Desktop_icon * dicon;
    void showwallpaper(vipath path);
    void set_lists(QList<QPair<int,vipath>> list);
    QList<vipath> list_vipath;
    QTimer *timer;
    QTimer *timer2;
    QTimer *timerloop;
    bool first;
    void playvideo();
    void loopplay(vipath*);
    void close_loop();
    QProcess *process;
    void change_start();
signals:

private:

    QString arg;
    bool ifshuffle;
    bool ifmute;
    long long int sec;

    int list_current;

    QWidget *widg;
public slots:
    void shuffle(int );
    void mute_slot(int );
    void slot_paint(QImage);
    void set_internal(long long int);
    void next_wallpaper();

};

#endif // WALLPAPER_H
