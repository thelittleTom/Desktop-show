#ifndef PROVIDE_FRAME_H
#define PROVIDE_FRAME_H
#include<QAbstractVideoSurface>
#include <QWidget>

class provide_frame : public QAbstractVideoSurface
{
    Q_OBJECT
public:
     provide_frame(QWidget *parent = nullptr);
        ~provide_frame();
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool present(const QVideoFrame &frame);
signals:
    void frameAvailable(QVideoFrame frame);
};

#endif // PROVIDE_FRAME_H
