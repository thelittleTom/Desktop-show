#include "setdialog.h"
#include "ui_setdialog.h"
#include<QDebug>
setDialog::setDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setDialog)
{
    ui->setupUi(this);
    second=10;
    ui->shuffle->setTristate(false);
}

setDialog::~setDialog()
{
    delete ui;
}
void setDialog::setsecond(){
    ui->timeEdit->setTime(QTime(0,0,second));
}
void setDialog::on_buttonBox_accepted()
{
    QTime time=ui->timeEdit->time();
    second=time.hour()*3600+time.minute()*60+time.second();

    int state=ui->shuffle->checkState();
    qDebug()<<state<<"dfaf";
    if (state == Qt::Checked) // "选中"
    {
        emit signal_shuffle(1);
    }
    else if(state==Qt::Unchecked)
    {
        emit signal_shuffle(0);
    }

    emit signal_ok();
}

