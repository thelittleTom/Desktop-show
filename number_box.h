#ifndef NUM_BOX_H
#define NUM_BOX_H

#include <QWidget>
#include<QLineEdit>
#include<QMouseEvent>
#include<QLabel>
class number_box : public QLabel
{
    Q_OBJECT
public:
    explicit number_box(int i,QWidget *parent = nullptr);
    void set_number(int);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *envet);
    int number;
    int index;
signals:
    void signal_check(int);
    void signal_nocheck(int);
};

#endif // NUM_BOX_H
