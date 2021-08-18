#include "paintpaper.h"
#include<qdebug.h>
paintpaper::paintpaper(QWidget *parent) : QWidget(parent)
{
    pen=new QPen(QColor(qRgb(82,170,127)),1);
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnBottomHint );
//    this->raise();
    this->setFixedSize(desktop_width,desktop_height);
    this->setAttribute(Qt::WA_TranslucentBackground);
}
void paintpaper::mousePressEvent(QMouseEvent *event)
{

    if(event->button()==Qt::LeftButton){
        QVector<QPoint*> vec_point;
        drawpoints tmp;
        tmp.pen=*pen;
        tmp.vec_point=vec_point;
        QPoint *point =new QPoint(event->pos());
        vec_point.append(point);
        vec_vec_point.append(tmp);
    }else if(event->button()==Qt::RightButton){
        if(vec_vec_point.size()){
            vec_vec_point.removeLast();
            update();
        }
    }
 }

void paintpaper::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPoint *point =new QPoint(event->pos());
        vec_vec_point.last().vec_point.append(point);
        update();
    }

}
void paintpaper::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton){
        QPoint *point =new QPoint(ev->pos());
        vec_vec_point.last().vec_point.append(point);
        update();
    }
}
void paintpaper::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter. setRenderHint(QPainter::Antialiasing, true);
    for(int i=0;i<vec_vec_point.size();i++){
        painter.setPen(vec_vec_point[i].pen);
        QVector<QPoint*> vec_point=vec_vec_point[i].vec_point;
        for(int j=0;j<vec_point.size()-1;j++)
        {
            painter.drawLine(*vec_point[j],*vec_point[j+1]);
        }
    }
}
void paintpaper:: clear_all(){
    vec_vec_point.clear();
    update();
}

