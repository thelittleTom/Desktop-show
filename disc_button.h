#ifndef DISC_BUTTON_H
#define DISC_BUTTON_H

#include<QTimeLine>
#include <QWidget>
#include<cmath>
#include<QPainter>
#include<qrect.h>
#include<QPoint>
#include<QMouseEvent>
class disc_button : public QWidget
{
    Q_OBJECT
public:
    int radius, arcLength,boundary;
    explicit disc_button(QList<QString> name,QList<QRgb> colors, QWidget *parent = nullptr);
    void setValue(int radius,int arcLength,int boundary,QList<QPoint> textpos);
        QPoint  center;
     void set_color(QList<QRgb> co_list);
private:
    // 绘制按钮;
    void paintEvent(QPaintEvent *);
    // 添加圆弧;
    void addArc(qreal startAngle, qreal angleLength);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int mouseindex(double angel);

    void leaveEvent(QEvent *event);
    double mousedigree(QPoint);
    virtual void focusOutEvent(QFocusEvent *e);
    void enter_timeline();
    void lose_timeline();
signals:
    // 鼠标点击;
    void signalButtonClicked(int buttonId);
    // 鼠标松开;
    void signalButtonReleased(int buttonId);
    void signalsetfocus();
private:
    QPainterPath *movepath;
    QList<QPainterPath> arcPathList;
    QList<QString> textPathList;
    QList<QPoint> textpos;
    // 圆弧颜色;
    QList<QRgb> colorList;
    // 当前鼠标按钮/进入 按钮的索引;
    int pressIndex, enterIndex;
    int loseIndex;
    bool Mouselose;
    // 鼠标事件标志位;
    bool MousePressed;

    bool MouseEntered;


};

#endif // DISC_BUTTON_H
#pragma once

