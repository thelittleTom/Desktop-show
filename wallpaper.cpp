#include "wallpaper.h"
#include<qdebug.h>
#include<frame_create.h>

wallpaper::wallpaper(QWidget *parent) : QMainWindow(parent)
{
    ifstart=true;
    ifmute=false;
    this->process = new QProcess;
    this->process->setProcessChannelMode(QProcess::MergedChannels);

    ifshuffle=false;
    sec=10;
    timer = new QTimer(this);

    timer->setTimerType(Qt::VeryCoarseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(next_wallpaper()));

    first=true;
    list_current=0;
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();
   this->setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnBottomHint );
    this->resize(desktop_width,desktop_height);


}
wallpaper::~wallpaper(){
  this->process->kill();
}
void wallpaper::showwallpaper(vipath path){
    vipw=path;
    if(path.videopath==NULL){
        this->process->kill();
        this->process=new QProcess;


        this->setAutoFillBackground(true);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window,QBrush(QPixmap(path.imagepath).scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
        this->setPalette(palette);// 给widget加上背景图
    }else{

        arg = "/usr/bin/mplayer";
        QStringList arg1;
        this->process->kill();
        this->process=new QProcess;
        filename=path.videopath;
        arg1 << filename;
        arg1 << "-slave";
        arg1 << "-quiet"; //尽可能的不打印播放信息
        arg1 << "-zoom"; //视频居中，四周黑条，全屏播放
        arg1<<"-loop";arg1<<"0";
        arg1 << "-vo";
        arg1<<"x11";
        arg1 << "-wid" << QString::number((unsigned int)(this->winId()));
        this->process->start(arg,arg1);   //开始播放进程
        if(ifmute)process->write("mute 1\n");
        else {process->write("mute 0\n");  }
    }
}
void wallpaper::slot_paint(QImage image){
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap::fromImage(image).scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
    this->setPalette(palette);
}
void wallpaper:: set_internal(long long int second){
    next_wallpaper();
    sec=second;
    list_current=0;

    timer->stop();

    timer->start(1000*second);
}
void wallpaper::next_wallpaper(){
    if(ifshuffle){
        QTime time=QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        int test =qrand()%list_vipath.size();
        list_current=(test+1)%list_vipath.size();
        qDebug()<<list_vipath.size()<<test<<":::++++++++++++++++::::";
        showwallpaper(list_vipath.at(test));
    }
    else{
        qDebug()<<list_current<<":::::::::::::::::::::";
        showwallpaper(list_vipath.at(list_current));
        list_current=(list_current+1)%list_vipath.size();
    }
}
void wallpaper:: set_lists(QList<QPair<int,vipath>> lists){
    list_vipath.clear();
    list_current=0;
    for(int i=0;i<lists.size();i++){
        int ttt=i,j=i+1;
        for(;j<lists.size();j++){
            if(lists.at(ttt).first>lists.at(j).first) ttt=j;
        }
        QPair<int,vipath> tpair(lists[i]);
        lists[i]=lists[ttt];
        lists[ttt]=tpair;
        list_vipath.append(lists[i].second);
    }
    set_internal(sec);
}
void wallpaper:: close_loop(){
    timer->stop();
}
void wallpaper::shuffle(int state){
    if(state) ifshuffle=true;
    else ifshuffle=false;
}
void wallpaper::mute_slot(int state){
    if(state) {
        ifmute=true;
        if(process)process->write("mute 1\n");
    }

    else {ifmute=false;if(process)process->write("mute 0\n");}
}
void wallpaper::change_start(){
    if(process) process->write("pause\n");
    ifstart=!ifstart;
}
