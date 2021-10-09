#ifndef SETALL_DIALOG_H
#define SETALL_DIALOG_H

#include <QDialog>
#include<color_disc.h>
namespace Ui {
class setall_dialog;
}

class setall_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit setall_dialog(QWidget *parent = nullptr);
    ~setall_dialog();
    color_disc* cdisc;
private slots:
    void on_buttonBox_accepted();
    void slot_right(int);
private:
    Ui::setall_dialog *ui;
signals:
    void signal_mute(int );
    void signal_maxsize_stop(int);
    void signal_right_button(QList<QRgb>);
};

#endif // SETALL_DIALOG_H
