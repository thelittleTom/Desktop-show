#include "container.h"

container::container(QWidget *parent) : QWidget(parent)
{
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();
    this->setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnBottomHint );
    this->setFixedSize(desktop_width,desktop_height);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAcceptDrops(true);

    texpaper=new textpaper(this);
    paipaper=new paintpaper(this);
    trapaper=new transpaper(this);
}
