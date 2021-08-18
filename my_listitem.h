#ifndef MY_LISTITEM_H
#define MY_LISTITEM_H
#include<frame_create.h>
#include <QWidget>
#include<QListWidgetItem>
#include<QMouseEvent>
#include<QLabel>
#include<QLayout>
#include<QFile>
#include<QCheckBox>
#include<QFileInfo>
#include<QLineEdit>
#include<number_box.h>
class my_listitem :public QFrame
{
    Q_OBJECT
public:
    explicit my_listitem(int ,vipath*,bool first);
    ~my_listitem();
    virtual void mousePressEvent(QMouseEvent *event)override;
    void setindex(int i);
    vipath *vip;
    number_box *numbox;
    void change_size();

private:
    QVBoxLayout myLayout ;
    QLabel label1;
    QLabel label2;
    QMenu * menu;
    int index;
private slots:
    void    change_image();
    void delete_it();
signals:
    void signal_itemClicked(int);
    void signal_delete(int);
};

#endif // MY_LISTITEM_H
