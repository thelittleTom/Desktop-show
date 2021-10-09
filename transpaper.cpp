#include "transpaper.h"

transpaper::transpaper(QWidget *parent) : QWidget(parent)
{
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnBottomHint );
    this->setFixedSize(desktop_width,desktop_height);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setAcceptDrops(true);
    //menu
    QList<QString> names;
    names<<"粘贴"<<"关闭"<<"设置"<<"切换";
    QList<QRgb> cs;
    for(int i=0;i<4;i++){
        cs.append(qRgb(135,206,235));
    }
    disc_but=new disc_button(names,cs,this);
    disc_but->close();
    connect(disc_but,SIGNAL(signalButtonClicked(int)),this,SLOT(disc_menu(int)));



    //read the file
    QFileInfoList files=getfile();
    for(int i = 0; i < files.size(); i++)
    {
        QFileInfo fileInfo = files.at(i);
        createDeskicon(i,fileInfo,100*((i*100)/(desktop_height-100)),(i*100)%(desktop_height-100));
        connect(list_icon.at(i), SIGNAL(signal_delete(int)), this, SLOT(deletetotrash(int)));
    }
    qDebug()<<Desktop_icon::stdPath;
}
void transpaper::disc_menu(int index){
    if(index==0) paste();
    else if(index==1) emit signal_close();
    else if(index==2) emit signal_set();
    else emit signal_change();
}
void transpaper::paste(){
    QClipboard *clip=QApplication::clipboard();
    const QMimeData *mimedata =clip->mimeData();
    if(mimedata->hasUrls()){
        QList<QUrl>urlList = mimedata->urls();
        if(urlList.isEmpty()){
            return ;
        }
        QString fileName = urlList.at(0).toLocalFile();
        if(fileName.isEmpty()){
            return ;
        }

        QFileInfo res(fileName);

        QFileInfoList files=getfile();
        for(int i = 0; i < files.size(); i++)
        {
            QFileInfo fileInfo = files.at(i);
            QString name=fileInfo.fileName();
            if(name==res.fileName()){
                //warning
                QMessageBox::warning(this, tr("warning"),
                                                 tr("A file with duplicate file name already exists"),
                                                 QMessageBox::Close);

                return;
            }
        }
        createDeskicon(list_icon.size(), res,100,100);
        connect(list_icon.at(list_icon.size()-1), SIGNAL(signal_delete(int)), this, SLOT(deletetotrash(int)));
        list_icon.at(list_icon.size()-1)->discbtn->set_color(cst);
        QString order="cp ";
        if(res.isDir()) order="cp -r ";
        order=order+"\""+fileName+"\" "+Desktop_icon::stdPath;
        QProcess::execute(order);
    }
}
void transpaper::createDeskicon(int i,QFileInfo fileInfo,int x,int y){
    QMimeDatabase db;
    QMimeType   mime= db.mimeTypeForFile(fileInfo.absoluteFilePath());  //根据前面定义的文件名（含后缀）
    QString fileMimeType = mime.name();  //使用name()将MimeType类型转为字符串类型
    fileMimeType.replace("/","-");

    qDebug()<<fileInfo.fileName()<<fileMimeType<<"`````````````````````";
    Desktop_icon * tmp=new Desktop_icon(i,fileInfo.fileName(),fileMimeType,this);
    list_icon.append(tmp);

    tmp->resize(100,100);
//    QPoint gl= tmp->mapToParent(QPoint(x,y));
    tmp->move(x,y);
}
void transpaper::deletetotrash(int i){
    QProcess::execute("rm -rf "+Desktop_icon::stdPath+"//"+list_icon.at(i)->filename);
     list_icon.at(i)->close();
}
QFileInfoList transpaper::getfile()
{
    QDir dir(Desktop_icon::stdPath);

    //获取filePath下所有文件夹和文件
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);//文件夹|文件|不包含./和../
    //获取文件夹下所有文件(文件夹+文件)
    QFileInfoList list = dir.entryInfoList();
    return list;
}
void transpaper::mousePressEvent(QMouseEvent *event){
    this->setFocus();
    //确保右键点击，然后跳出菜单.
    if (event->button() == Qt::RightButton)
    {
        int ra=65,arc=61;
        int mid=ra-arc/2;
        QList<QPoint> textp;
        textp.append(QPoint(-22,-mid));
        textp.append(QPoint(-10,mid+15));
        textp.append(QPoint(-20,mid+10));
        textp.append(QPoint(-10,-mid+5));
        disc_but->setValue(ra,arc,20,textp);
        disc_but->move(event->globalPos()-disc_but->center);
        disc_but->setFocus();
        disc_but->show();
    }
}
void transpaper::right_button_slot(QList<QRgb> cs){
    QList<QRgb> tmpcs;
    for(int i=4;i<8;i++) tmpcs.append(cs.at(i));
    disc_but->set_color(tmpcs);

    cst=cs;
    for(int i=0;i<list_icon.size();i++){
        list_icon.at(i)->discbtn->set_color(cs);
    }

}
/*void transpaper::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
    else{
        event->ignore();
    }
}

//当用户放下这个文件后，就会触发dropEvent事件
void transpaper::dropEvent(QDropEvent *event)
{
    const QMimeData *mimedata = event->mimeData();
    if(mimedata->hasUrls()){
        QList<QUrl>urlList = mimedata->urls();
        if(urlList.isEmpty()){
            return ;
        }
        QString fileName = urlList.at(0).toLocalFile();
        if(fileName.isEmpty()){
            return ;
        }
        QFileInfo tarfile(fileName);
        QFileInfoList files=getfile();
        for(int i = 0; i < files.size(); i++)
        {
            QFileInfo fileInfo = files.at(i);
            if(fileInfo.fileName()==tarfile.fileName())
        }
        QString order="mv \""+fileName+"\" "+"/home/kylin/Desktop";
        QProcess::execute(order);
        //qDebug()<<fileName;
        createDeskicon(list_icon.size(), QFileInfo(fileName),100,100);
        connect(list_icon.at(list_icon.size()-1), SIGNAL(signal_delete(int)), this, SLOT(deletetotrash(int)));


    }
}*/

