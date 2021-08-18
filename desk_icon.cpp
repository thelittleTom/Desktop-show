#include "desk_icon.h"
#include "ui_desk_icon.h"

desk_icon::desk_icon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::desk_icon)
{
    ui->setupUi(this);
}

desk_icon::~desk_icon()
{
    delete ui;
}

void desk_icon::on_pushButton_pressed()
{

}
