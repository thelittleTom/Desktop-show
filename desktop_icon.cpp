#include "desktop_icon.h"
#include<QDebug>
#include<QDialog>
QString getdesktop(){
    QString res;
    QFile file("/home/kylin/.config/user-dirs.dirs");
    if(file.open(QFile::ReadWrite))
    {
        QTextStream stream(&file);
        if(!stream.atEnd())
        {
            QString x = stream.readAll();
            QString y = "XDG_DESKTOP_DIR=\"$HOME/";
            int iPos = x.indexOf(y);              // 返回0
            // 函数indexOf()会返回要查找的字符串在字符串中第一次出现的位置
            // 如果没有要查找的字符串，返回-1

            for(int i=iPos+y.length();i<x.length();i++){
                if(x[i]=='\"') break;
                res+=x[i];

            }
        }
    }
    file.close();
    return res;
}
QString Desktop_icon::stdPath= QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"//"+getdesktop();

bool Desktop_icon::than(int a,int b,int c){
    if(a<=b&&b<=c) return true;
    else return false;
}
Desktop_icon::Desktop_icon(int i,QString name,QString icon,QWidget *parent)
{
    //qDebug()<<stdPath;
    discishow=false;
    index=i;
    this->setParent(parent);
    filename=name;
    icon_path=":/text/resource/icons/"+icon+".png";
    //is exist
    QFileInfo file(icon_path);
    if(file.exists()==false) icon_path=":/text/resource/icons/unknown.png";

    this->setFlat(true);
    this->setMinimumSize(80,80);


    QLabel *testl=new QLabel();
    QLabel *testla=new QLabel();
    QHBoxLayout * hlayout=new QHBoxLayout ();
    testl->setFixedWidth(14);
    testla->setFixedWidth(14);

    QLabel* label4 = new QLabel();
    QPixmap *pixmap4 = new QPixmap(icon_path);//该处设置自己想要放的图片
    pixmap4->scaled((label4->size()), Qt::KeepAspectRatio);//设置图片大小
    label4->setPixmap(*pixmap4);
    label4->setScaledContents(true);//设置全填效果
    hlayout->addWidget(testl);
    hlayout->addWidget(label4);
    hlayout->addWidget(testla);

    label = new QLabel();
    label->setText(filename);
  label->setWordWrap(true);label->setAlignment(Qt::AlignTop);
    QVBoxLayout* myLayout2 = new QVBoxLayout();
    myLayout2->addItem(hlayout);
    myLayout2->addWidget(label);
    myLayout2->setStretchFactor(hlayout,6);
    myLayout2->setStretchFactor(label,1);
    this->setLayout(myLayout2);
    QFont font("times", 10);
    label->setFont(font);
//    label->setFixedHeight(20);
    this->show();

    QList<QString> names;

    names<<"复制"<<"打开"<<"删除"<<"重命名";
    QList<QRgb> cs;
    for(int i=0;i<4;i++){
        cs.append(qRgba(211,211,211,50));
    }
    discbtn=new disc_button(names,cs,parent);
    mouseright=false;
    discbtn->close();
    connect(discbtn,SIGNAL(signalButtonClicked(int)),this,SLOT(disc_menu(int)));
    connect(discbtn,SIGNAL(signalsetfocus()),this,SLOT(setFocus()));

    QFontMetrics fm(font);
    int pixelsWide = fm.horizontalAdvance(filename);
   if(pixelsWide<100) label->setAlignment(Qt::AlignCenter);

}
void Desktop_icon::rename(){
    discbtn->close();;
    lineedit =new mylineEdit(this);
    lineedit->setFixedSize(label->width(),label->height());
    lineedit->move(label->pos());

    lineedit->raise();
    QFont ttt=label->font();
    lineedit->setFont(ttt);
    lineedit->setText(label->text());
    lineedit->setFocus ();
    lineedit->show();
    connect(lineedit,&QLineEdit::returnPressed,this,[=](){
        QString textt=lineedit->text();
        if(textt==NULL) {
            lineedit->close();
            return;
        }
        else{

            QString ord="\""+stdPath+"//"+textt+"\"";
            QString order="mv \""+stdPath+"//"+filename+"\" "+ord;
            QProcess::execute(order);
            lineedit->close();
            label->setText(textt);
            label->setFont(ttt);
            filename=textt;
            QFont ft("times");
            ft.setPointSize(ttt.pointSize());
            QFontMetrics fm(ft);
            int pixelsWide = fm.horizontalAdvance(textt);
           if(pixelsWide<label->width()) label->setAlignment(Qt::AlignCenter);
           else {
            label->setWordWrap(true);label->setAlignment(Qt::AlignTop);
           }
        }
    });
}
void Desktop_icon::disc_menu(int index){
    if(index==0) copy();
    else if(index==1) open();
    else if(index==2) send_delete();
    else if(index==3) rename();

}

void Desktop_icon::send_delete(){
    emit signal_delete(index);
    discbtn->close();
}
void Desktop_icon::open(){
    QString stdd=Desktop_icon::stdPath;
    QString order="xdg-open \""+stdd+"//"+filename+"\"";
    QProcess::startDetached(order);
}
void Desktop_icon::copy(){

    QList<QUrl> copyfile;
    QUrl url=QUrl::fromLocalFile(stdPath+"//"+filename);    //待复制的文件
    if(url.isValid()){
        copyfile.push_back(url);
    }else{
        return;
    }
    QMimeData *data=new QMimeData;
    data->setUrls(copyfile);

    QClipboard *clip=QApplication::clipboard();
    clip->setMimeData(data);

}
void Desktop_icon::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        int arc=(height()-100)/5+40;
            int mid=arc+height()/2-(arc/2)-(arc/4);
        QList<QPoint> textp;
        textp.append(QPoint(-18,-mid));
        textp.append(QPoint(-10,mid+16));
        textp.append(QPoint(-18,mid+19));
        textp.append(QPoint(-20,-mid));
        discbtn->setValue(arc+height()/2,arc,20+(height()-100)/10,textp);
        mouseright=true;
        discbtn->setFocus();
        discbtn->update();
        discbtn->move((this->pos()-QPoint(discbtn->arcLength+discbtn->boundary/2,
                                          discbtn->arcLength+discbtn->boundary/2)));
        discbtn->show();
    }
    else if(event->button()==Qt::LeftButton){

        move_point=this->pos()-event->globalPos();
    }
    //要继续保留QListWidget原有的点击事件.
}

void Desktop_icon::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()+ move_point);
}
void Desktop_icon::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        open();
    }
}
void Desktop_icon::wheelEvent(QWheelEvent *event)
{

    QPoint numDegrees;                                     // 定义指针类型参数numDegrees用于获取滚轮转角
    numDegrees = event->angleDelta();                      // 获取滚轮转角
    int step = 0;                                          // 设置中间参数step用于将获取的数值转换成整数型
    if (!numDegrees.isNull())                              // 判断滚轮是否转动
    {
        step = numDegrees.y();                             // 将滚轮转动数值传给中间参数step
    }

    event->accept();                                       // 获取事件
    int currentWidth = this->width();                  // 获取当前图像的宽
    int currentHeight = this->height();                // 获取当前图像的高
    currentWidth += step*0.3;                                  // 对当前图像的高累加
    currentHeight += step*0.3;                                 // 对当前图像的宽累加
    this->resize(currentWidth, currentHeight);          // 通过更新图像显示控件的大小来更新图像大小


    int font=currentWidth/10;
    QFont ft("times");
    ft.setPointSize(font);

    QFontMetrics fm(ft);
    int pixelsWide = fm.horizontalAdvance(filename);
   if(pixelsWide<label->width()) label->setAlignment(Qt::AlignCenter);
 else {
    label->setWordWrap(true);label->setAlignment(Qt::AlignTop);
   }
    this->label->setFont(ft);
}

void Desktop_icon::focusInEvent(QFocusEvent *e){
    if(e->type()==Qt::OtherFocusReason){
        clearFocus();
    }
    //qDebug()<<index<<e;
    this->setStyleSheet("QPushButton{background:rgba(211,211,211,50%);border:1px solid rgba(0,0,0,0);}");
}
void Desktop_icon::focusOutEvent(QFocusEvent *e){
    this->setStyleSheet("QPushButton{background:rgba(0,0,0,0);"
                        "border:1px solid rgba(0,0,0,0);}");
    if(mouseright) {
        this->setStyleSheet("QPushButton{background:rgba(211,211,211,50%);"
                            "border:1px solid rgba(0,0,0,0);}");
        mouseright=false;
    }
}
