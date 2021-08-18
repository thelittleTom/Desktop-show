#ifndef TEXTPAPER_H
#define TEXTPAPER_H
#include<QTextEdit>
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
#include<QMimeData>
class textpaper : public QWidget
{
    Q_OBJECT
public:
    explicit textpaper(QWidget *parent = nullptr);
    QTextEdit* textedit;
    void wheelEvent(QWheelEvent *event);
    void simulate_press();
private:
    void readtext();
signals:
public slots:
    void changedFont(QFont);
};

#endif // TEXTPAPER_H
