#ifndef transpaper_H
#define transpaper_H

#include <QWidget>
#include "desktop_icon.h"
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
#include<QList>
#include <QMimeDatabase>
#include<QDir>
#include<QUrl>
#include<QMessageBox>
#include<disc_button.h>
#include<QMimeData>
#include<QColorDialog>
#include<textpaper.h>
class transpaper : public QWidget
{
    Q_OBJECT
public:
    explicit transpaper(QWidget *parent = nullptr);
    QFileInfoList getfile();
    Desktop_icon* dicon;
    void mousePressEvent(QMouseEvent *event);
    //void dropEvent(QDropEvent *event);
    //void dragEnterEvent(QDragEnterEvent *event);
    void createDeskicon(int,QFileInfo,int ,int  );
    QMenu *menu;
signals:
    void signal_close();
    void signal_change();
    void  signal_set();
public slots:
    void deletetotrash(int i);
    void paste();
     void disc_menu(int);
    void  right_button_slot(QList<QRgb> );
private:
    QList<Desktop_icon*> list_icon;
    QList<disc_button*> list_disc;
    disc_button *disc_but;

};

#endif // transpaper_H
