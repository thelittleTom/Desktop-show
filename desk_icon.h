#ifndef DESK_ICON_H
#define DESK_ICON_H

#include <QWidget>

namespace Ui {
class desk_icon;
}

class desk_icon : public QWidget
{
    Q_OBJECT

public:
    explicit desk_icon(QWidget *parent = 0);
    ~desk_icon();

private slots:
    void on_pushButton_pressed();

private:
    Ui::desk_icon *ui;
};

#endif // DESK_ICON_H
