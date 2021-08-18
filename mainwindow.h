#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QScrollBar>
#include "desktop_icon.h"
#include <QMainWindow>
#include<wallpaper.h>
#include<transpaper.h>
#include<textpaper.h>
#include<paintpaper.h>
#include<provide_frame.h>
#include<QList>
#include<QListWidget>
#include<my_listitem.h>
#include<QPushButton>
#include<QSpinBox>
#include<QSlider>
#include<QColorDialog>
#include<QTime>
#include<setdialog.h>
#include<QInputDialog>
#include <QtNetwork>
#include<add_paper_menu.h>
#include<frame_create.h>
#include<QFileDialog>
#include<videoplayer.h>
#include<setall_dialog.h>
#include<container.h>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void closeEvent(QCloseEvent *event);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void add_wallpaper_item(vipath*);
    void startRequest(QUrl url);//请求链接
//    virtual void resizeEvent(QResizeEvent *event) override;
private slots:
    void httpFinished();//完成下载后的处理
    void httpReadyRead();//接收到数据时的处理
    void on_closebt_clicked();
    void on_change_color_clicked();

    void on_finish_button_clicked();

    void on_write_button_clicked();

    void on_paint_button_clicked();

    void on_paintfinish_clicked();

    void on_paint_color_clicked();

    void on_paint_slider_valueChanged(int value);
    void on_create_queue_clicked();

    void on_create_queue_set_clicked();

    void on_clear_all_clicked();

    void on_close_loop_clicked();

    void on_set_all_clicked();

    void on_pushButton_clicked();

public slots:
    void changestate();
    void showit();
    //void ProcessFrame(QVideoFrame );
    void playvideo(int);
    void changewallpaper();
    void addplaylist(int);
    void set_number(int);
    void decrease_number(int);
    void slot_url();
    void slot_picture();
    void slot_video();
    void delete_item(int);
private:
    setall_dialog* set_alldia;
    setDialog *setdialog;
    QList<my_listitem*> list_item;
    Ui::MainWindow *ui;
    bool isclose;
    wallpaper* wpaper;

    container * contain;


    bool iscreate_queue;
    int current_number;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;
    int current_show_paper;
    QString fullPath;
    QGridLayout *pLayout ;
signals:
    void clear_all();
};

#endif // MAINWINDOW_H
