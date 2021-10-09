#include "add_paper_menu.h"

add_paper_menu::add_paper_menu(QWidget *parent) : QPushButton(parent)
{

    m_pSetButton  = new QPushButton("添加",this);
    m_pSetButton->setIcon(QIcon(":/text/resource/myicons/icons8-add.png"));
    m_pSetButton->setIconSize(QSize(20,20));
//    m_pSetButton->setStyleSheet(QString("QPushButton::menu-indicator{image:none;}"
//                                        "QPushButton{background-color:rgb(135,206,235);border: 1px;}"
//                                        "QPushButton:hover{background-color:lightgray; color: white;}"
//                                        "QPushButton:pressed{background-color:rgb(85, 170, 255);}"));
    m_pSetButton->setCursor(QCursor(Qt::PointingHandCursor));

    QMenu *add_menu = new QMenu();
    QAction *url_action = new QAction(add_menu);
    QAction *picture_action = new QAction(add_menu);
    QAction *video_action = new QAction(add_menu);

    url_action->setText(tr("从网络添加图片"));
    picture_action->setText(tr("从本地添加图片"));
    video_action->setText(tr("从本地添加视频"));
    add_menu->addAction(url_action);
    add_menu->addAction(picture_action);
    add_menu->addAction(video_action);

    add_menu->setWindowFlags(add_menu->windowFlags() | Qt::FramelessWindowHint);
    add_menu->setAttribute(Qt::WA_TranslucentBackground);
    add_menu->setStyleSheet(" QMenu {border-radius:5px;font-family:'Arial';font-size:16px;}"
                     " QMenu::item {height:35px; width:140px;padding-left:15px;border: 1px solid none;}"
                     "QMenu::item:selected {background-color:#06AD56;\
                      padding-left:25px;border: 1px solid rgb(65,173,255,60);}");
    m_pSetButton->setMenu(add_menu);
    m_pSetButton->show();

    //相关槽函数实现
    connect(url_action,&QAction::triggered, this,[=](){
        emit signal_url();
    });
    connect(picture_action,&QAction::triggered, this,[=](){
        emit signal_picture();
    });
    connect(video_action,&QAction::triggered, this,[=](){
        emit signal_video();
    });

}
 void add_paper_menu:: resizeEvent(QResizeEvent *event){
     m_pSetButton->resize(this->size());
}
