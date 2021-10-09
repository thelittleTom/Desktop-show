#include "my_listitem.h"
#include<QtDebug>
my_listitem::my_listitem(int i,vipath *vi,bool first)
{
    setCursor(QCursor(Qt::PointingHandCursor));
   index=i;
   vip=vi;
   if(first){
       frame_create * fc=new frame_create(vip);
       connect(fc,SIGNAL(signal_frame()),this,SLOT(change_image()));
   }
    setStyleSheet(".my_listitem{border:1px solid qRgba(70,130,180,80%);border-radius:5px}"
                );
    QPixmap pixmap2 (vip->imagepath);//该处设置自己想要放的图片
   pixmap2.scaled(label2.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小
   label2.setScaledContents(true);//设置全填效果
   label2.setPixmap(pixmap2);
   label2.setMargin(0);
   QFileInfo fileinfo(vip->imagepath);
   label1.setText(fileinfo.baseName());

   myLayout.addWidget(&label2);
  myLayout.addWidget(&label1);
   this->setLayout(&myLayout);
//    myLayout.setMargin(0);

   QSizePolicy sizePolicy = this->sizePolicy();
   sizePolicy.setHorizontalPolicy(QSizePolicy::Maximum);
     sizePolicy.setVerticalStretch(1);
     sizePolicy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
   this->setSizePolicy(sizePolicy);
   setMinimumWidth(150);
   setMinimumHeight(200);
   setMaximumHeight(300);
    numbox=new number_box (index,this);
    numbox->setFixedSize(20,20);
    numbox->move(0,0);
    numbox->raise();
    numbox->close();
   this->show();

    //Menu
    menu=new QMenu(this);
    QAction* delAction = new QAction("删除",this);
   menu->addAction(delAction);
    connect(delAction, SIGNAL(triggered()), this, SLOT(delete_it()));
    menu->setStyleSheet(" QMenu {border-radius:5px;font-family:'Arial';font-size:16px;}"
                         " QMenu::item {height:25px; width:60px;padding-left:5px;border: 1px solid none;}"
                         "QMenu::item:selected {background-color:#06AD56;\
                          padding-left:15px;border: 1px solid rgba(65,173,255,60);}");
    if(vip->videopath==NULL){
        QAction* setusedAction = new QAction("设图片为原桌面壁纸",this);
       menu->addAction(setusedAction);

        connect(setusedAction, SIGNAL(triggered()), this, SLOT(set_used()));

        QAction* setnewAction = new QAction("设图片为新桌面壁纸",this);
       menu->addAction(setnewAction);
        connect(setnewAction, SIGNAL(triggered()), this, SLOT(set_new()));
        menu->setStyleSheet(" QMenu {border-radius:5px;font-family:'Arial';font-size:16px;}"
                             " QMenu::item {height:25px; width:150px;padding-left:5px;border: 1px solid none;}"
                             "QMenu::item:selected {background-color:#06AD56;\
                              padding-left:10px;border: 1px solid rgba(65,173,255,60);}");
    }

}
my_listitem::~my_listitem(){
    qDebug()<<"deleteing";

}
void my_listitem::delete_it(){
    setVisible(false);
    emit signal_delete(index);

}
void my_listitem::set_used(){

    QString order="gsettings set org.mate.background picture-filename "+vip->imagepath;
    QProcess::execute(order);
    emit signal_set_used();
}
void my_listitem::set_new(){
    emit this->signal_itemClicked(index);
}
void my_listitem::setindex(int i){
    index=i;
    numbox->index=i;
}
void my_listitem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit this->signal_itemClicked(index);
    }
    else if (event->button() == Qt::RightButton)
    {
       menu->exec(event->globalPos());
    }
}
void my_listitem::change_image(){
    qDebug()<<"........."<<vip->imagepath;
     QPixmap pixmap2 (vip->imagepath);//该处设置自己想要放的图片
    pixmap2.scaled(label2.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小
    label2.setScaledContents(true);//设置全填效果
    label2.setPixmap(pixmap2);
}
void my_listitem::change_size(){
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap(vip->imagepath).scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
    this->setPalette(palette);// 给widget加上背景图
}

