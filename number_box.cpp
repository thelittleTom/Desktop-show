#include "number_box.h"
#include<QDebug>
number_box::number_box(int i,QWidget *parent) :QLabel(parent)
{
//    setFocus();
    index=i;
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QLabel{background:#FFF5EE;border:1px solid rgb(72,61,139);border-radius:2px}");
    setMouseTracking(true);
    number=0;
}
void number_box:: set_number(int i){
    number=i;
    if(number){setText(QString::number(number));}
    else setText("");
}
void number_box:: mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){emit signal_check(index);}
    else if (event->button() == Qt::RightButton){
        emit signal_nocheck(index);
    }
}
void number_box:: mouseMoveEvent(QMouseEvent *envet){
    setCursor(Qt::PointingHandCursor);
}
