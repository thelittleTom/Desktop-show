#ifndef PAINTPAPER_H
#define PAINTPAPER_H

#include <QWidget>
#include<QPainter>
#include<QPoint>
#include<QMouseEvent>
#include<QVector>
#include <QApplication>
#include<QScreen>
#include<QRect>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QObject>
struct drawpoints{
    QPen pen;
    QVector<QPoint*> vec_point;
};
class paintpaper : public QWidget
{
    Q_OBJECT
public:
    explicit paintpaper(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void  mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *ev);
     QPen* pen;
signals:

private:
    QVector<drawpoints> vec_vec_point;
public slots:
    void clear_all();

};

#endif // PAINTPAPER_H
