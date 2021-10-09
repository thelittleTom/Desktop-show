#include "setall_dialog.h"
#include "ui_setall_dialog.h"
#include<QDebug>
setall_dialog::setall_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setall_dialog)
{

    ui->setupUi(this);
    connect(ui->right_color,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_right(int)));
    cdisc=new color_disc();
    setWindowTitle("设置");
}

setall_dialog::~setall_dialog()
{
    delete ui;
}

void setall_dialog::on_buttonBox_accepted()
{
    int state=ui->mute->checkState();
    if (state == Qt::Checked) // "选中"
    {
        emit signal_mute(1);
    }
    else if(state==Qt::Unchecked)
    {
        emit signal_mute(0);
    }

    int ste=ui->mute_2->checkState();
    if (ste == Qt::Checked) // "选中"
    {
        emit signal_maxsize_stop(1);
    }
    else if(ste==Qt::Unchecked)
    {
        emit signal_maxsize_stop(0);
    }

    int index=ui->right_color->currentIndex();
    if(index==0){
        QList<QRgb> cs;
        for(int i=0;i<4;i++){
            cs.append(qRgba(211,211,211,50));
        }
        for(int i=4;i<8;i++){
            cs.append(qRgb(135,206,235));

        }
        emit signal_right_button(cs);
    }
    else emit signal_right_button(cdisc->list_color);
    qDebug()<<cdisc->list_color.size();
}
void setall_dialog::slot_right(int index){
//    emit signal_right_button(index);
    if(index==0){
        ui->gridLayout->addWidget(ui->right_btn,0,1);
        ui->gridLayout->addWidget(ui->mute_2,1,1);
        ui->gridLayout->addWidget(ui->mute,2,1);
        ui->gridLayout->addWidget(ui->buttonBox,3,1);
        cdisc->close();
    }else if(index==1){
        cdisc->show();
        ui->gridLayout->addWidget(ui->right_btn,0,1);
        ui->gridLayout->addWidget(cdisc,1,1);
        ui->gridLayout->addWidget(ui->mute_2,2,1);
        ui->gridLayout->addWidget(ui->mute,3,1);
        ui->gridLayout->addWidget(ui->buttonBox,4,1);
    }
}
