#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QBitmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->scrollArea->setAutoFillBackground(false);
//    ui->gridLayout_2 = new QGridLayout();//网格布局
//    ui->scrollArea->widget()->setLayout(ui->gridLayout_2);

    ui->scrollArea->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical{width:8px;background:rgba(0,139,139,0%);margin:0px,0px,0px,0px;padding-top:9px;padding-bottom:9px;}"//留9px给上下箭头
                "QScrollBar::handle:vertical{width:8px;background:rgba(0,139,139,45%);border-radius:4px;min-height:20;}"//上下设置为椭圆
                "QScrollBar::handle:vertical:hover{width:8px;background:rgba(0,139,139,70%);border-radius:4px;min-height:20;}"//鼠标悬浮颜色变深
                "QScrollBar::add-line:vertical{height:9px;width:8px;border-image:url(:/images/bottom.png);subcontrol-position:bottom;}"//下箭头
                "QScrollBar::sub-line:vertical{height:9px;width:8px;border-image:url(:/images/top.png);subcontrol-position:top;}"//上箭头
                "QScrollBar::add-line:vertical:hover{height:7px;width:6px;border-image:url(:/images/bottom.png);border:1px;subcontrol-position:bottom;}"//鼠标悬浮下箭头
                "QScrollBar::sub-line:vertical:hover{height:7px;width:6px;border-image:url(:/images/top.png);border:1px;subcontrol-position:top;}"//鼠标悬浮上箭头
                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgba(0,139,139,10%);border-radius:4px;}");//滚动时部分

    ui->gridLayout_2->setColumnStretch(0, 1);
    ui->gridLayout_2->setColumnStretch(1, 1);
    ui->gridLayout_2->setColumnStretch(2, 1);
    ui->gridLayout_2->setColumnStretch(3, 1);
    fullPath="./resource";
    QDir dir(fullPath);
    fullPath=dir.absolutePath();
    if(dir.exists())
    {
        qDebug()<<"exist"<<fullPath;
    }
    else
    {
       bool ok = dir.mkdir(fullPath);//只创建一级子目录，即必须保证上级目录存在
       qDebug()<<ok;
    }



    manager = new QNetworkAccessManager();
    iscreate_queue=true;
    current_number=1;

    wpaper=new wallpaper;
    wpaper->show();
    contain=new container();
    contain->show();

    ui->paintfinish->setEnabled(false);
    ui->finish_button->setEnabled(false);
    ui->paintfinish->setCursor(QCursor(Qt::ArrowCursor));
    ui->finish_button->setCursor(QCursor(Qt::ArrowCursor));
    isclose=false;

    connect(this,SIGNAL(clear_all()),contain->paipaper,SLOT(clear_all()));
    connect(ui->fontComboBox,SIGNAL(currentFontChanged(QFont)),contain->texpaper,SLOT(changedFont(QFont)));

    int nSingleStep = 10;
    // 微调框
    int nMin=1;
    int nMax=100;
    ui->spinBox->setMinimum(nMin);  // 最小值
    ui->spinBox->setMaximum(nMax);  // 最大值
    ui->spinBox->setSingleStep(nSingleStep);  // 步长
    ui->paint_slider->setOrientation(Qt::Horizontal);  // 水平方向
    ui->paint_slider->setMinimum(nMin);  // 最小值
    ui->paint_slider->setMaximum(nMax);  // 最大值
    ui->paint_slider->setSingleStep(nSingleStep);  // 步长
    connect(ui->spinBox,SIGNAL(valueChanged(int)),ui->paint_slider,SLOT(setValue(int)));
    connect(ui->paint_slider,SIGNAL(valueChanged(int)),ui->spinBox,SLOT(setValue(int)));
    ui->spinBox->setValue(35);

    QFile file(fullPath+"/path.date");
    if(!file.open(QIODevice::ReadWrite)){
        qDebug()<<"open false";
    }
    QDataStream in(&file);
    int tmpcui=0;
    if(file.size()!=0)  in >> tmpcui;
    qDebug()<<tmpcui;
    for(int i=0;i<tmpcui;i++){
        QString vtmppath;
        QString itmppath;
        in>>vtmppath>>itmppath;
        qDebug()<<vtmppath<<itmppath;
        vipath * path1=new vipath (vtmppath,itmppath);
        add_wallpaper_item(path1);
    }

    if(list_item.length()!=0){
        wpaper->showwallpaper(*list_item.at(0)->vip);

    }
    connect(contain->trapaper,SIGNAL(signal_close()),this,SLOT(on_closebt_clicked()));
    connect(contain->trapaper,SIGNAL(signal_change()),this,SLOT(changewallpaper()));
     connect(contain->trapaper,SIGNAL(signal_set()),this,SLOT(showit()));

     setdialog=new setDialog ();
     connect(setdialog,SIGNAL(signal_ok()),this,SLOT(changestate()));
     connect(setdialog,SIGNAL(signal_shuffle(int)),wpaper,SLOT(shuffle(int )));
     set_alldia=new setall_dialog();
     connect(set_alldia,SIGNAL(signal_mute(int)),wpaper,SLOT(mute_slot(int )));
    connect(set_alldia,SIGNAL(signal_right_button(QList<QRgb>)),contain->trapaper,SLOT(right_button_slot(QList<QRgb> )));

     ui->create_queue_set->setEnabled(false);
     ui->create_queue_set->setCursor(QCursor(Qt::ArrowCursor));

     connect(ui->add_menu,SIGNAL(signal_url()),this,SLOT(slot_url()));
     connect(ui->add_menu,SIGNAL(signal_picture()),this,SLOT(slot_picture()));
     connect(ui->add_menu,SIGNAL(signal_video()),this,SLOT(slot_video()));

     this->resize(1090,590);
//     this->setWindowFlag(Qt::WindowStaysOnTopHint);
}

void MainWindow::slot_picture(){
   QString str = QFileDialog::getOpenFileName(this,"open file","/","picture file(*.png *.jpeg *.jpg);;All file(*.*)");
   QString str_utf8 =str.toUtf8();
   if(str_utf8.isEmpty())
   {
       return;
   }
   vipath* vip=new vipath("",str_utf8);
   wpaper->showwallpaper(*vip);
   add_wallpaper_item(vip);
}
void MainWindow::slot_video(){
    QString str = QFileDialog::getOpenFileName(this,"open file","/","video file(*.mp4 *.avi *.gif);;All file(*.*)");
   QString str_utf8 =str.toUtf8();
   if(str_utf8.isEmpty())
   {
       return;
   }

   vipath* vip=new vipath(str_utf8,":/text/resource/129.jpg");
   qDebug()<<vip->videopath;
   wpaper->showwallpaper(*vip);
   add_wallpaper_item(vip);
}
void MainWindow::slot_url(){
    bool isOK;
    QString te= QInputDialog::getText(NULL, "Input url",
                                      "Please input your url",
                                      QLineEdit::Normal,
                                      "http://",
                                      &isOK);
    if(isOK){
        QUrl   url =te;//从lineEdit中获取信息
        QFileInfo info(url.path());//从url中获取path信息
        QString fileName(info.fileName());//从url中获取filename
        if (fileName.isEmpty()) fileName = "index.html";//判断文件名是否存在，如果为空将filename设置为默认页
        file =new QFile("./resource/"+fileName);
        if(!file->open(QIODevice::WriteOnly))
        {
            qDebug() << "file open error";
            delete file;
            file = 0;
            return;
        }
        startRequest(url);//开始请求url
    }

}
void MainWindow::startRequest(QUrl url)
{
       reply = manager->get(QNetworkRequest(url));//发起请求
       qDebug()<<"url"<<url;
       connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
       connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}
void MainWindow::httpFinished()
{
    QString ipath=file->fileName();
    QDir dir(ipath);
    ipath=dir.absolutePath();
    vipath* vip=new vipath("",ipath);
    wpaper->showwallpaper(*vip);
    add_wallpaper_item(vip);
    file->flush();//刷新数据缓冲区
    file->close();//关闭文件描述符
    reply->deleteLater();//释放relay对象
    reply = 0;
    delete file;
    file = 0;
}
void MainWindow::httpReadyRead()
{
    if (file) file->write(reply->readAll());
}
MainWindow::~MainWindow()
{
    QString fullPath="./resource";
    QDir dir(fullPath);
    fullPath=dir.absolutePath();
    qDebug()<<fullPath;
    QFile file(fullPath+"/path.date");

    if(!file.open(QIODevice::WriteOnly)){ qDebug()<<"open false ";return;}
    QDataStream out(&file);
    out <<list_item.size();
    for(int i=0;i<list_item.size();i++){
        if(list_item.at(i)){
            out<<list_item.at(i)->vip->videopath<<list_item.at(i)->vip->imagepath;
        }
    }
    file.close();
    delete ui;
}
void MainWindow::showit(){
    this->setWindowState((this->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}
void MainWindow::changewallpaper(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int test =qrand()%list_item.size();
    while(!list_item.at(test)){
        test =qrand()%list_item.size();
    }
    playvideo(test);
}
void MainWindow::add_wallpaper_item(vipath* vip){
    int i=list_item.size();
    bool ai=false;
    if(vip->imagepath==(":/text/resource/129.jpg")) ai=true;
    my_listitem * item=new my_listitem(list_item.size(),vip,ai);
    connect(item,SIGNAL(signal_itemClicked(int)),this,SLOT(playvideo(int)));
    connect(item,SIGNAL(signal_delete(int)),this,SLOT(delete_item(int)));

    connect(item->numbox,SIGNAL(signal_check(int)),this,SLOT(set_number(int)));
    connect(item->numbox,SIGNAL(signal_nocheck(int)),this,SLOT(decrease_number(int)));
    list_item.append(item);
    ui->gridLayout_2->addWidget(item, i/4, i%4);//把按钮添加到布局的第i行第1列
}
void MainWindow::delete_item(int ind){
    if((wpaper->vipw.imagepath==list_item.at(ind)->vip->imagepath)&&(wpaper->vipw.videopath==list_item.at(ind)->vip->videopath)){
        wpaper->showwallpaper(vipath("",(":/text/resource/129.jpg")));
    }else if((wpaper->vipw.videopath!=NULL)&&(wpaper->vipw.videopath==list_item.at(ind)->vip->videopath)){
        wpaper->showwallpaper(vipath("",(":/text/resource/129.jpg")));
    }
    auto w=list_item.at(ind);
    list_item.removeAt(ind);
    w->deleteLater();
    w=NULL;
    for(int i=ind;i<list_item.size();i++){
        list_item.at(i)->setindex(i);

        ui->gridLayout_2->addWidget(list_item.at(i), i/4, i%4);
    }
}
void MainWindow::decrease_number(int in){
    int decrease=list_item.at(in)->numbox->number;
    if(decrease==0) return;
    for (int i=0;i<list_item.size() ;i++ ) {
        if(list_item.at(i))
        {
            int tmp=list_item.at(i)->numbox->number;
            if(tmp){
                if(tmp>decrease) list_item.at(i)->numbox->set_number(--tmp);
                else if(tmp==decrease) list_item.at(i)->numbox->set_number(0);
            }
        }
    }
    current_number--;
}
void MainWindow::set_number(int i){
    if(list_item.at(i)->numbox->number>0) return;
    list_item.at(i)->numbox->set_number(current_number);
    current_number++;
}
void MainWindow::addplaylist(int i){
    wpaper->playlist->addMedia(QUrl::fromLocalFile(list_item.at(i)->vip->videopath));
}
void MainWindow::playvideo(int index){
    if(isclose){
        wpaper->show();
        contain->show();
//        wpaper->setWindowFlags(wpaper->windowFlags()|Qt::Tool);
//        contain->setWindowFlags(contain->windowFlags()|Qt::Tool);
//        contain->setWindowFlags(Qt::WindowStaysOnBottomHint );
        isclose=false;
        this->setWindowFlag(Qt::WindowStaysOnTopHint);
       this->show();
        qDebug()<<windowFlags();
        this->setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);
        this->show();
        qDebug()<<windowFlags();
    }

    wpaper->showwallpaper(*list_item.at(index)->vip);
}

void MainWindow::on_closebt_clicked()
{
    QFile file("./resource/text");

    if(file.open(QFile::WriteOnly |QFile::Truncate))
    {
        QTextStream stream(&file);
            stream<<contain->texpaper->textedit->toHtml().toUtf8();
    }

    file.close();

    wpaper->close();
    wpaper->process->kill();
    wpaper->close_loop();
    contain->close();
    isclose=true;
}

void MainWindow::on_change_color_clicked()
{

    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        contain->texpaper->textedit->setTextColor(color);
    }


}
void MainWindow::on_write_button_clicked()
{
    ui->write_button->setEnabled(false);
    ui->paint_button->setEnabled(false);
    ui->finish_button->setEnabled(true);
    ui->finish_button->setCursor(QCursor(Qt::PointingHandCursor));
    ui->write_button->setCursor(QCursor(Qt::ArrowCursor));
    ui->paint_button->setCursor(QCursor(Qt::ArrowCursor));
    contain->texpaper->textedit->setReadOnly(false);
     contain->texpaper->raise();
}
void MainWindow::on_finish_button_clicked()
{
    ui->paint_button->setEnabled(true);
    ui->write_button->setEnabled(true);
    ui->finish_button->setEnabled(false);
    ui->paint_button->setCursor(QCursor(Qt::PointingHandCursor));
    ui->write_button->setCursor(QCursor(Qt::PointingHandCursor));
    ui->finish_button->setCursor(QCursor(Qt::ArrowCursor));
    contain->texpaper->simulate_press();
    contain->trapaper->raise();
    contain->texpaper->textedit->setReadOnly(true);
}



void MainWindow::on_paint_button_clicked()
{
//    trapaper->setWindowFlags(trapaper->windowFlags()| Qt::WindowStaysOnBottomHint );
    ui->write_button->setEnabled(false);
    ui->paint_button->setEnabled(false);
    ui->paintfinish->setEnabled(true);
    ui->write_button->setCursor(QCursor(Qt::ArrowCursor));
    ui->paint_button->setCursor(QCursor(Qt::ArrowCursor));
    ui->paintfinish->setCursor(QCursor(Qt::PointingHandCursor));
    contain->paipaper->raise();
}

void MainWindow::on_paintfinish_clicked()
{
    ui->paint_button->setEnabled(true);
    ui->write_button->setEnabled(true);
    ui->paintfinish->setEnabled(false);
    ui->paint_button->setCursor(QCursor(Qt::PointingHandCursor));
    ui->write_button->setCursor(QCursor(Qt::PointingHandCursor));
    ui->paintfinish->setCursor(QCursor(Qt::ArrowCursor));
    contain->trapaper->raise();
}

void MainWindow::on_paint_color_clicked()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        contain->paipaper->pen->setColor(color);
    }
}



void MainWindow::on_paint_slider_valueChanged(int value)
{
    contain->paipaper->pen->setWidth(value);
}

void MainWindow::on_create_queue_clicked()
{
    if(iscreate_queue){
        for(int i=0;i<list_item.size();i++){
           if(list_item.at(i)) list_item.at(i)->numbox->show();
        }
        iscreate_queue=false;
        ui->create_queue->setText("finish");
    }else{
        if(isclose){
            wpaper->show();
            contain->show();
            isclose=false;
        }
        ui->create_queue->setText("create a queue");
        iscreate_queue=true;
        QList<QPair<int,vipath> > lists;

        for(int i=0;i<list_item.size();i++){
            if(list_item.at(i))
            {
                int tmp=list_item.at(i)->numbox->number;
                list_item.at(i)->numbox->close();
                if(tmp){
                    lists.append(QPair<int,vipath>(tmp,*list_item.at(i)->vip));
                }
            }
        }
        if(lists.size()==0){
            return;
        }
        else if(lists.size()==1) {ui->create_queue_set->setEnabled(false);
            ui->create_queue_set->setCursor(QCursor(Qt::ArrowCursor));
             wpaper->showwallpaper(lists.at(0).second); return;
        }
        else if(lists.size()>1){
            ui->create_queue_set->setEnabled(true);
            ui->create_queue_set->setCursor(QCursor(Qt::PointingHandCursor));
            wpaper->set_lists(lists);
        }
    }
}

void MainWindow::on_create_queue_set_clicked()
{
    setdialog->setsecond();
    setdialog->exec();
}
void MainWindow::changestate(){
    wpaper->set_internal(setdialog->second);
}

void MainWindow::on_clear_all_clicked()
{
    emit clear_all();
}
//void MainWindow:: resizeEvent(QResizeEvent *event){
//    int window_width=width();
//    int window_height=height();
//    for(int i=0;i<list_item.size();i++){
//        list_item.at(i)->resize(window_width*0.2,window_height*0.2);
//        list_item.at(i)->change_size();
//    }
//}

void MainWindow::on_close_loop_clicked()
{
    wpaper->close_loop();
}
void MainWindow::closeEvent(QCloseEvent *event) //根据不同的需求进行添加，比如：{
{
    delete this;
}

void MainWindow::on_set_all_clicked()
{
    set_alldia->exec();
}

void MainWindow::on_pushButton_clicked()
{
    wpaper->change_start();
    if(!wpaper->ifstart){
        ui->pushButton->setIcon(QIcon(":/text/resource/myicons/icons8-start.png"));
    }else{
        ui->pushButton->setIcon(QIcon(":/text/resource/myicons/icons8-pause.png"));
    }
}
