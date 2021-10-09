#ifndef WININFO_H
#define WININFO_H

#include <QWidget>
#include<QProcess>
#include<QList>
#include<QDebug>
class M_process : public QWidget
{
    Q_OBJECT
public:
    M_process()
    {
        connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadData()));
        connect(&m_process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
              [=](int exitCode, QProcess::ExitStatus exitStatus){
//            qDebug()<<res;
            emit signal_finish_read();

        });
        m_process.setReadChannel(QProcess::StandardOutput);

    }
    void startprocess(QString cmd){
        {
            m_process.kill();
            m_process.start(cmd);
        }
    }
    QString res;
signals:
    void signal_finish_read();
private slots:
    void onReadData()
    {
       res=m_process.readAllStandardOutput();
    }

private:
    QProcess m_process;

};
class wininfo : public QWidget
{
    Q_OBJECT
public:
    wininfo() ;

signals:
    void signal_true();
    void signal_false();
private slots:
    void ready2();
public slots:
    void ifmaxscreen();
private:
    int ijk;
    M_process process2;
    QString act_id;
    int curindex;
    bool iffinished;
};
#endif // WININFO_H

