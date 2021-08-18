#ifndef DESKTOP_ICON_H
#define DESKTOP_ICON_H
#include<disc_button.h>
#include<QPushButton>
#include<QPoint>
#include <QMouseEvent>
#include<QLabel>
#include<QWidget>
#include<stdlib.h>
#include<QLayout>
#include<QMenu>
#include<QProcess>
#include<QWindow>
#include<QClipboard>
#include<QLineEdit>
#include<mylineedit.h>
#include<QApplication>
#include<QMimeData>
#include<QMainWindow>
#include<QFileInfo>
#include<QPlainTextEdit>
#include<QStandardPaths>
class Desktop_icon:public QPushButton
{
    Q_OBJECT
public:
    static QString stdPath;

 //   bool    eventFilter(QObject *obj, QEvent *event);
    QLabel*label;
    Desktop_icon(int i,QString name,QString ipath,QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *envet);
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool than(int a,int b,int c);
    void wheelEvent(QWheelEvent *event);
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);
     QMenu * menu;
     disc_button* discbtn;
     QString filename;
signals:
    void signal_mouseright(int);
    void signal_focusout(int);
    void signal_delete(int);
    void signal_copy();

private slots:
    void send_delete();
    void copy();
    void disc_menu(int);
private:
    void open();
    void rename();
    mylineEdit* lineedit;
    bool discishow;
    bool mouseright;
    QPoint move_point;
    QVBoxLayout* verti_layout;
    QProcess* process;
    QString icon_path;
    bool isedge;
    int index;


};

#endif // DESKTOP_ICON_H
