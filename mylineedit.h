#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include<QProcess>
#include <QWidget>
#include<QLineEdit>
class mylineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit mylineEdit(QWidget *parent = nullptr);
    virtual void focusOutEvent(QFocusEvent *e);
    virtual void focusInEvent(QFocusEvent *e);
signals:

};

#endif // MYLINEEDIT_H
