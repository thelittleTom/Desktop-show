#include "videoplayer.h"

videoplayer::videoplayer(QWidget *parent) : QMainWindow(parent)
{
    this->process = new QProcess;
        this->process->setProcessChannelMode(QProcess::MergedChannels);
    //    arg = "F:/mypler-vedio/MPlayer/mplayer.exe";
        arg = "/usr/bin/mplayer";

        QStringList arg1;
        this->process->kill();
        this->process=new QProcess;

        fileName="/home/kylin/poke.mp4";
        arg1 << fileName;
        arg1 << "-slave";//默认情况下，mplayer接受键盘的命令，而"-slave"使其不再接受键盘事件，而是作为后台程序运行，
                         //接受以“\n”结束的命令控制，这样我们可以在进程中给他发送命令，而不需要操作键盘了.
        arg1 << "-quiet"; //尽可能的不打印播放信息
        arg1 << "-zoom"; //视频居中，四周黑条，全屏播放
       arg1 << "-wid" << QString::number((unsigned int)(this->winId()));
                 // "-wid <窗口标识>" 是指让MPlayer依附于那个窗口，
                 //ui->widget->winId() 这个指令就是用来获取widget的标识码 ,
                 //这样视频播放的时候，就在这个部件里播放，相当于给他固定起来。
            this->process->write("vo_fullscreen\n");
    //    connect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(dataReceive()));
        this->process->start(arg,arg1);   //开始播放进程
        this->process->write("loop -1\n");

        this->setWindowTitle(fileName);//设置当前播放的视频的标题名称
}
