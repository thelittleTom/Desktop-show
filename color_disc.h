#ifndef COLOR_DISC_H
#define COLOR_DISC_H

#include <QWidget>
#include<QColorDialog>
#include<QList>
#include<QColor>
namespace Ui {
class color_disc;
}

class color_disc : public QWidget
{
    Q_OBJECT

public:
    explicit color_disc(QWidget *parent = nullptr);
    ~color_disc();

    QList<QRgb> list_color;
private slots:
    void on_desk1_clicked();

    void on_desk2_clicked();

    void on_desk3_clicked();

    void on_desk4_clicked();

    void on_tran1_clicked();

    void on_tran2_clicked();

    void on_tran3_clicked();

    void on_tran4_clicked();

private:
    Ui::color_disc *ui;
};

#endif // COLOR_DISC_H
