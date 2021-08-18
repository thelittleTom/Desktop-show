#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include<QTime>
#include<QTimeEdit>
namespace Ui {
class setDialog;
}

class setDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setDialog(QWidget *parent = nullptr);
    long long int second;
    ~setDialog();
    void setsecond();
signals:
    void signal_ok();
    void signal_shuffle(int);
private slots:
    void on_buttonBox_accepted();
private:
    Ui::setDialog *ui;
};

#endif // SETDIALOG_H
