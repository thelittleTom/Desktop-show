#include "imagepaper.h"

imagepaper::imagepaper(QWidget *parent) : QWidget(parent)
{
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnBottomHint );
    this->raise();
    this->setFixedSize(desktop_width,desktop_height);
    this->setAttribute(Qt::WA_TranslucentBackground);

    imagepath="/home/kylin/Desktop/image.jpg";

    QImage image(imagepath);
    image=convert_Alpha(image);

    QLabel *lb = new QLabel(this);
    lb->resize(this->size());

    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小
    lb->setScaledContents(true);//设置全填效果
    lb->setPixmap(pixmap);
    lb->show();


}
QImage imagepaper::convert_Alpha(QImage val){

    QImage imageAlpha = val.convertToFormat(QImage::Format_RGBA8888_Premultiplied, Qt::NoFormatConversion);
    int nWidth = imageAlpha.width();
    int nHeight = imageAlpha.height();

    for (int nCol = 0; nCol < nWidth; ++nCol)
    {
        for (int nRow = 0; nRow < nHeight; ++nRow)
        {
            QColor pixelColor = imageAlpha.pixelColor(nCol, nRow);

            // 如果该像素点的各分量值均大于240则认为该像素点的颜色为白色
            if (pixelColor.red() > 130 && pixelColor.green() > 130&& pixelColor.blue() > 130)
            {
                pixelColor.setAlpha(0);
                imageAlpha.setPixelColor(nCol, nRow, pixelColor);
            }
        }
    }

    return imageAlpha;
}

