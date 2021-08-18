#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include<textpaper.h>
#include<transpaper.h>
#include<paintpaper.h>
class container : public QWidget
{
    Q_OBJECT
public:
    explicit container(QWidget *parent = nullptr);
    textpaper * texpaper;
    paintpaper * paipaper;
    transpaper *trapaper;
signals:

};

#endif // CONTAINER_H
