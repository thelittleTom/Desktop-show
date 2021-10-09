#include "color_disc.h"
#include "ui_color_disc.h"

color_disc::color_disc(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::color_disc)
{
    ui->setupUi(this);

    for(int i=0;i<4;i++){
        list_color.append(qRgba(211,211,211,50));

    }
    for(int i=4;i<8;i++){
        list_color.append(qRgb(135,206,235));

    }
    ui->tran1->setStyleSheet("*{background:rgb(135,206,235);}");
    ui->tran2->setStyleSheet("*{background:rgb(135,206,235);}");
    ui->tran3->setStyleSheet("*{background:rgb(135,206,235);}");
    ui->tran4->setStyleSheet("*{background:rgb(135,206,235);}");
    ui->desk1->setStyleSheet("*{background:rgba(211,211,211,50);}");
    ui->desk2->setStyleSheet("*{background:rgba(211,211,211,50);}");
    ui->desk3->setStyleSheet("*{background:rgba(211,211,211,50);}");
    ui->desk4->setStyleSheet("*{background:rgba(211,211,211,50);}");
}

color_disc::~color_disc()
{
    delete ui;
}
QString makeColorString(const QColor &color){
            return QString("rgba(%1, %2, %3, %4)")
                    .arg(color.red())
                    .arg(color.green())
                    .arg(color.blue())
                    .arg(color.alpha());


}
void color_disc::on_desk1_clicked()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        QString strrgb=makeColorString(color);

        ui->desk1->setStyleSheet("*{background:"+strrgb+";}");
        list_color[0]=color.rgba();
    }
}

void color_disc::on_desk2_clicked()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        QString strrgb=makeColorString(color);
        ui->desk2->setStyleSheet("*{background:"+strrgb+";}");
        list_color[1]=color.rgba();
    }
}

void color_disc::on_desk3_clicked()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        QString strrgb=makeColorString(color);
        ui->desk3->setStyleSheet("*{background:"+strrgb+";}");
        list_color[2]=color.rgba();
    }
}

void color_disc::on_desk4_clicked()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        QString strrgb=makeColorString(color);
        ui->desk4->setStyleSheet("*{background:"+strrgb+";}");
        list_color[3]=color.rgba();
    }
}

void color_disc::on_tran1_clicked()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        QString strrgb=makeColorString(color);
        ui->tran1->setStyleSheet("*{background:"+strrgb+";}");
        list_color[4]=color.rgba();
    }
}

void color_disc::on_tran2_clicked()
{

    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        QString strrgb=makeColorString(color);
        ui->tran2->setStyleSheet("*{background:"+strrgb+";}");
        list_color[5]=color.rgba();
    }
}

void color_disc::on_tran3_clicked()
{

    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        QString strrgb=makeColorString(color);
        ui->tran3->setStyleSheet("*{background:"+strrgb+";}");
        list_color[6]=color.rgba();
    }
}

void color_disc::on_tran4_clicked()
{

    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel);
    const QColor color = QColorDialog::getColor(Qt::green, this, tr("选择颜色"), options);

    if (color.isValid())
    {
        QString strrgb=makeColorString(color);
        ui->tran4->setStyleSheet("*{background:"+strrgb+";}");
        list_color[7]=color.rgba();
    }
}
