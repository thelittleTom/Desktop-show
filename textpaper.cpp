#include "textpaper.h"

textpaper::textpaper(QWidget *parent) : QWidget(parent)
{
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnBottomHint );
    this->setFixedSize(desktop_width,desktop_height);
    this->setAttribute(Qt::WA_TranslucentBackground);

    textedit=new QTextEdit(this);
    textedit->setFixedSize(desktop_width,desktop_height);
    textedit->setStyleSheet("border: none;");
    //set transparent
    textedit->setWindowFlags(Qt::FramelessWindowHint | textedit->windowFlags());
    textedit->setAttribute(Qt::WA_TranslucentBackground);
    QWidget *v = textedit->viewport();
    v->setWindowFlags(Qt::FramelessWindowHint | v->windowFlags());
    v->setAttribute(Qt::WA_TranslucentBackground);
    readtext();
    textedit->setReadOnly(true);
}
void textpaper:: wheelEvent(QWheelEvent *event){
    QPoint numDegrees;                                     // 定义指针类型参数numDegrees用于获取滚轮转角
    numDegrees = event->angleDelta();                      // 获取滚轮转角
    int step = 0;                                          // 设置中间参数step用于将获取的数值转换成整数型
    if (!numDegrees.isNull())                              // 判断滚轮是否转动
    {
        step = numDegrees.y();                             // 将滚轮转动数值传给中间参数step
    }
    event->accept();                                       // 获取事件
    int cursize=textedit->fontPointSize();
    QTextCharFormat fmt;
    fmt.setFontPointSize(step*0.1+cursize);
    //textedit->mergeCurrentCharFormat(fmt);

    QTextCursor cursor = textedit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(fmt);
}
void textpaper::changedFont(QFont font){
    QTextCharFormat fmt;
    fmt.setFont(font);
    fmt.setFontPointSize(textedit->fontPointSize());
    QColor color=textedit->textColor();

    QTextCursor cursor = textedit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    //cursor.mergeCharFormat(fmt);
    cursor.setCharFormat(fmt);
    textedit->setTextColor(color);
}
void textpaper::simulate_press(){
    QTextCursor cursor = textedit->textCursor();
               cursor.movePosition(QTextCursor::End);
               textedit->setTextCursor(cursor);
}
void textpaper::readtext(){
    QFile file("./resource/text");
    if(file.open(QFile::ReadWrite))
    {
        textedit->clear();
        QTextStream stream(&file);
        if(!stream.atEnd())
        {
            textedit->setText(stream.readAll());
        }
    }
    file.close();
}
