#ifndef KWIN_H
#define KWIN_H

#include <QObject>
#include<QStringLiteral>
class Kwin : public QObject
{
    Q_OBJECT
public:
    Kwin(QObject *parent = nullptr);
    void selectWindow();
signals:

};

#endif // KWIN_H
