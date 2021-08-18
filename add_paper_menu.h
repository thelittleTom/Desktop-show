#ifndef add_paper_menu_H
#define add_paper_menu_H

#include <QWidget>
#include<QPushButton>
#include<QMenu>
class add_paper_menu : public QPushButton
{
    Q_OBJECT
public:
    explicit add_paper_menu(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;
signals:
    void signal_url();
    void signal_picture();
    void signal_video();
    void signal_delete();
private:
    QPushButton *m_pSetButton;
};

#endif // add_paper_menu_H
