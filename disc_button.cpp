#include "disc_button.h"
#include<qdebug.h>
#include<QPushButton>
#include <unistd.h>
disc_button::disc_button(QList<QString>name,QList<QRgb> colors,  QWidget *parent) : QWidget(parent)
{
//    this->setStyleSheet("QPushButton{background:rgba(0,0,0,0);border:0px}");
//    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_NoSystemBackground);
//    setAttribute(Qt::WA_TranslucentBackground);
//    setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);
    loseIndex=-1;
    Mouselose=false;
    pressIndex=-1;
    enterIndex=-1;
    MouseEntered=false;
    MousePressed=false; 
    radius = 90;
    arcLength = 40;
    boundary=20;
    textPathList=name;
    colorList=colors;
}
void disc_button:: setValue(int r,int arc,int b,QList<QPoint> textp){
    radius=r;
    arcLength=arc;
    boundary=b;
    resize(radius*2+boundary,radius*2+boundary);
    center=QPoint(width()/2,height()/2);
    arcPathList.clear();
    textpos=textp;
    for(int i=0;i<4;i++){
            addArc(45+i*90,90);
    }

}
void disc_button:: addArc(qreal startAngle, qreal angleLength)
{
    QRectF rect(-radius, -radius, radius << 1, radius << 1);
    QPainterPath path;
    path.arcTo(rect, startAngle, angleLength);

    QPainterPath subPath;
    subPath.addRect(rect.adjusted(arcLength, arcLength, -arcLength, -arcLength));
    path -= subPath;
    arcPathList.append(path);
}
void disc_button:: paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(center);
    for(int i=0;i<4;i++){
        QBrush brush(colorList.at(i));
        painter.setBrush(brush);
        painter.setPen(Qt::white);
        painter.drawPath(arcPathList.at(i));
    }

    if(Mouselose){
        QBrush newbrush(QColor(96,139,139));
        painter.setBrush(newbrush);
        painter.setPen(Qt::gray);
        painter.drawPath(*movepath);
    }
    if(MouseEntered){
        QBrush newbrush(QColor(96,139,139));
        painter.setBrush(newbrush);
        painter.setPen(Qt::gray);
        painter.drawPath(*movepath);
    }
    if(MousePressed){
            QBrush newbrush(QColor(70, 92, 216));
            painter.setBrush(newbrush);
            painter.setPen(Qt::gray);
            painter.drawPath(*movepath);
    }
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(16);
    painter.setPen(Qt::black);
    painter.setFont(font);
    painter.drawText(textpos.at(2),textPathList.at(2));
    painter.drawText(textpos.at(0),textPathList.at(0));
    painter.save();
    painter.rotate(90);
    painter.drawText(textpos.at(3),textPathList.at(3));

    painter.drawText(textpos.at(1),textPathList.at(1));
    painter.restore();
}
double disc_button:: mousedigree(QPoint eventpos){
    double dis= sqrt(double((center.x() - eventpos.x())*(center.x() - eventpos.x()) +
                         (center.y() - eventpos.y())*(center.y() - eventpos.y())));
    if(dis>radius+1) return 361;

    QRect tm(0,0,radius*2,radius*2);
    tm.adjust(arcLength, arcLength, -arcLength, -arcLength);
    if(tm.contains(eventpos)) {return -361;}

    double angel;
    double dx=eventpos.x()-center.y();
    double dy=-((eventpos.y())-center.y());
    if(dx>=0&&dy>=0){
        angel=asin(dy/dis)*180/M_PI;
    }else if(dx<=0&&dy>=0) {angel=acos(dx/dis)*180/M_PI;}
    else if(dx<=0&&dy<=0) angel=180+asin(-dy*1.0/dis)*180/M_PI;
    else angel=asin(dy*1.0/dis)*180/M_PI+360;
    return  angel;

}
int disc_button:: mouseindex(double angel){
   for(int i=0;i<3;i++){
       if(angel>=45+i*90&&angel<=135+90*i) return i;
   }
   return 3;
}
void disc_button:: enter_timeline(){
    QTimeLine *timeLine = new QTimeLine(100, this);
    timeLine->setFrameRange(0, 15);
    connect(timeLine,&QTimeLine::frameChanged,this,[=](int frame){
        if(enterIndex!=-1){
            double factor=(boundary*1.0)/100;
            int tmpradius=radius+factor*frame;
            int tmparclength=arcLength+factor*frame;
            movepath=new QPainterPath;
            QRectF rect(-tmpradius, -tmpradius, tmpradius << 1, tmpradius << 1);
            movepath->arcTo(rect, enterIndex*90+46, 88);
            QPainterPath subPath;
            subPath.addRect(rect.adjusted(tmparclength, tmparclength, -tmparclength, -tmparclength));
            *movepath -= subPath;
            update();
        }
    });
     timeLine->start();
}
void disc_button::lose_timeline(){
    QTimeLine *timeLine = new QTimeLine(100, this);
    timeLine->setFrameRange(0, 15);
    connect(timeLine,&QTimeLine::frameChanged,this,[=](int frame){
        if(loseIndex!=-1){
            double factor=(boundary*1.0)/100;
            int tmpradius=radius+15*factor-factor*frame;
            int tmparclength=arcLength+15*factor-factor*frame;
            movepath=new QPainterPath;
            QRectF rect(-tmpradius, -tmpradius, tmpradius << 1, tmpradius << 1);
            movepath->arcTo(rect, loseIndex*90+46, 88);
            QPainterPath subPath;

            subPath.addRect(rect.adjusted(tmparclength, tmparclength, -tmparclength, -tmparclength));
            *movepath -= subPath;
            update();
        }
    });
    connect(timeLine,&QTimeLine::finished,this,[=](){
        loseIndex=-1;
        Mouselose=false;
    });
     timeLine->start();
}
void disc_button::mouseMoveEvent(QMouseEvent *event){
    double angel=mousedigree(event->pos());
    if(angel==361||angel==-361) {
        if(MouseEntered){
            Mouselose=true;
            loseIndex=enterIndex;
             lose_timeline();
             MouseEntered=false;
        }
         enterIndex=-1;return;
    }
    else{
       int tmpindex=mouseindex(angel);
       if(tmpindex==enterIndex) return;
       enterIndex=tmpindex;
       MouseEntered=true;
        enter_timeline();
    }
}
void disc_button:: mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
           double angel=mousedigree(event->pos());
           if(angel==361) {MousePressed=false; return;}
           else if(angel==-361){
               emit signalsetfocus();
               this->close();
               return;
           }
           else{
              pressIndex=mouseindex(angel);
              MousePressed=true;
              emit signalButtonClicked(pressIndex);
              update();
           }

     }
}
void disc_button:: mouseReleaseEvent(QMouseEvent *event){
    MousePressed=false;
    update();
}

// 鼠标离开事件;
void disc_button::  leaveEvent(QEvent *event){
    MousePressed=false;
    MouseEntered=false;
    MouseEntered=false;
}
void disc_button::focusOutEvent(QFocusEvent *e){
    emit signalsetfocus();
    this->close();
}
void disc_button::set_color(QList<QRgb> co_list){
    colorList=co_list;
}
