#include "mylineedit.h"
#include<QDebug>
mylineEdit::mylineEdit(QWidget *parent) : QLineEdit(parent)
{

}
void mylineEdit:: focusOutEvent(QFocusEvent *e){
    emit returnPressed();
}
void mylineEdit:: focusInEvent(QFocusEvent *e){
    QLineEdit::focusInEvent(e);

}
