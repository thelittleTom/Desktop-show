#include "frame_create.h"
#include<QDir>
extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"

#include "libavdevice/avdevice.h"
}

frame_create::frame_create(vipath * vi,QWidget *parent) : QThread(parent)
{
    vip=vi;
    this->start();
}
void frame_create::run()
{

    int frameIndex = 0;
    QString fileName = vip->videopath;
//    QDir dir1(vip->videopath);
//           dir1.cdUp();
//    QString  sss= dir1.absolutePath();
    QFile file(vip->videopath);
    QString imgpath=file.fileName()+"img";
    qDebug()<<imgpath<<"ffmpeg";
    QDir dir2(imgpath);
    if(dir2.exists())
    {
        qDebug()<<"exist1";
    }
    else
    {
       bool ok = dir2.mkdir(imgpath);//只创建一级子目录，即必须保证上级目录存在
       qDebug()<<ok;
    }

    // ffmpeg相关变量预先定义与分配
    AVFormatContext *pAVFormatContext = 0;          // ffmpeg的全局上下文，所有ffmpeg操作都需要
//    AVInputFormat *pAVInputFormat = 0;              // ffmpeg的输入格式结构体
    AVDictionary *pAVDictionary = 0;                // ffmpeg的字典option，各种参数给格式编解码配置参数的
    AVCodecContext *pAVCodecContext = 0;            // ffmpeg编码上下文
    AVCodec *pAVCodec = 0;                          // ffmpeg编码器
    AVPacket *pAVPacket = 0;                        //
    AVFrame *pAVFrame = 0;                          //
    AVFrame *pAVFrameRGB32 = 0;                     //
    struct SwsContext *pSwsContext = 0;             // ffmpag编码数据格式转换

    int ret = 0;                                    // 函数执行结果
    int videoIndex = -1;                            // 音频流所在的序号
    int gotPicture = 0;                             // 解码时数据是否解码成功
    int numBytes = 0;                               // 解码后的数据长度
    uchar *outBuffer = 0;                           // 解码后的数据存放缓存区

    pAVFormatContext = avformat_alloc_context();    // 分配
    pAVPacket = av_packet_alloc();                  // ffmpag单帧数据包分配
    pAVFrame = av_frame_alloc();                    // ffmpeg单帧缓存分配
    pAVFrameRGB32 = av_frame_alloc();               // ffmpeg单帧缓存转换颜色空间后的缓存分配
    if(!pAVFormatContext || !pAVPacket || !pAVFrame || !pAVFrameRGB32)
    {
        qDebug() << "Failed to alloc";
        goto END;
    }
    // 步骤一：注册所有容器和编解码器（也可以只注册一类，如注册容器、注册编码器等）
    av_register_all();

    // 步骤二：打开文件(ffmpeg成功则返回0)
    qDebug() << "文件:" << fileName << "，是否存在：" << QFile::exists(fileName);
//    ret = avformat_open_input(&pAVFormatContext, fileName.toUtf8().data(), pAVInputFormat, 0);
    ret = avformat_open_input(&pAVFormatContext, fileName.toUtf8().data(), 0, 0);
    if(ret)
    {
        qDebug() << "Failed";
        goto END;
    }
    // 步骤三：探测流媒体信息
    // Assertion desc failed at libswscale/swscale_internal.h:668
    // 入坑：因为pix_fmt为空，需要对编码器上下文进一步探测
    ret = avformat_find_stream_info(pAVFormatContext, 0);
    if(ret < 0)
    {
        qDebug() << "Failed to avformat_find_stream_info(pAVCodecContext, 0)";
        goto END;
    }

    qDebug() << "视频文件包含流信息的数量:" << pAVFormatContext->nb_streams;

    // 步骤三：提取流信息,提取视频信息
    for(int index = 0; index < pAVFormatContext->nb_streams; index++)
    {
        pAVCodecContext = pAVFormatContext->streams[index]->codec;
        switch (pAVCodecContext->codec_type)
        {
        case AVMEDIA_TYPE_UNKNOWN:
            qDebug() << "流序号:" << index << "类型为:" << "AVMEDIA_TYPE_UNKNOWN";
            break;
        case AVMEDIA_TYPE_VIDEO:
            qDebug() << "流序号:" << index << "类型为:" << "AVMEDIA_TYPE_VIDEO";
            videoIndex = index;
            qDebug();
            break;
        case AVMEDIA_TYPE_AUDIO:
            qDebug() << "流序号:" << index << "类型为:" << "AVMEDIA_TYPE_AUDIO";
            break;
        case AVMEDIA_TYPE_DATA:
            qDebug() << "流序号:" << index << "类型为:" << "AVMEDIA_TYPE_DATA";
            break;
        case AVMEDIA_TYPE_SUBTITLE:
            qDebug() << "流序号:" << index << "类型为:" << "AVMEDIA_TYPE_SUBTITLE";
            break;
        case AVMEDIA_TYPE_ATTACHMENT:
            qDebug() << "流序号:" << index << "类型为:" << "AVMEDIA_TYPE_ATTACHMENT";
            break;
        case AVMEDIA_TYPE_NB:
            qDebug() << "流序号:" << index << "类型为:" << "AVMEDIA_TYPE_NB";
            break;
        default:
            break;
        }
        // 已经找打视频品流
        if(videoIndex != -1)
        {
            break;
        }
    }

    if(videoIndex == -1 || !pAVCodecContext)
    {
        qDebug() << "Failed to find video stream";
        goto END;
    }
    // 步骤四：对找到的视频流寻解码器
    pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);
    if(!pAVCodec)
    {
        qDebug() << "Fialed to avcodec_find_decoder(pAVCodecContext->codec_id):"
            << pAVCodecContext->codec_id;
        goto END;
    }

    // 步骤五：打开解码器
    ret = avcodec_open2(pAVCodecContext, pAVCodec, NULL);
    if(ret)
    {
        qDebug() << "Failed to avcodec_open2(pAVCodecContext, pAVCodec, pAVDictionary)";
        goto END;
    }
    qDebug() << pAVCodecContext->width << "x" << pAVCodecContext->height;
    // 步骤六：对拿到的原始数据格式进行缩放转换为指定的格式高宽大小
    pSwsContext = sws_getContext(pAVCodecContext->width,
                                 pAVCodecContext->height,
                                 pAVCodecContext->pix_fmt,
                                 pAVCodecContext->width,
                                 pAVCodecContext->height,
                                 AV_PIX_FMT_RGBA,
                                 SWS_FAST_BILINEAR,
                                 0,
                                 0,
                                 0);
    numBytes = avpicture_get_size(AV_PIX_FMT_RGBA,
                                  pAVCodecContext->width,
                                  pAVCodecContext->height);
    outBuffer = (uchar *)av_malloc(numBytes);
    // pAVFrame32的data指针指向了outBuffer
    avpicture_fill((AVPicture *)pAVFrameRGB32,
                   outBuffer,
                   AV_PIX_FMT_RGBA,
                   pAVCodecContext->width,
                   pAVCodecContext->height);

    // 步骤七：读取一帧数据的数据包
    while(av_read_frame(pAVFormatContext, pAVPacket) >= 0)
    {
        if(pAVPacket->stream_index == videoIndex)
        {
            // 步骤八：发送数据给编码器
            ret = avcodec_send_packet(pAVCodecContext, pAVPacket);
            if(ret)
            {
                qDebug() << "Failed to avcodec_send_packet(pAVCodecContext, pAVPacket) ,ret =" << ret;
                break;
            }
            // 步骤九：循环冲编码器获取解码后的数据
            while(!avcodec_receive_frame(pAVCodecContext, pAVFrame))
            {
                sws_scale(pSwsContext,
                          (const uint8_t * const *)pAVFrame->data,
                          pAVFrame->linesize,
                          0,
                          pAVCodecContext->height,
                          pAVFrameRGB32->data,
                          pAVFrameRGB32->linesize);
                QImage imageTemp((uchar *)outBuffer,
                                 pAVCodecContext->width,
                                 pAVCodecContext->height,
                                 QImage::Format_RGBA8888);
                QImage image = imageTemp.copy();
                if(frameIndex==10)   {
                    qDebug()<< image.save(QString(imgpath+"/"+"%1.jpg").arg(frameIndex));
                    vip->imagepath=QString(imgpath+"/"+"%1.jpg").arg(frameIndex);
                    emit signal_frame();
                    av_free_packet(pAVPacket);
                    goto END;
                    break;
                }
                frameIndex++;
            }
            av_free_packet(pAVPacket);
        }
        QThread::msleep(1);
    }
END:
    qDebug() << "释放回收资源";
    if(outBuffer)
    {
        av_free(outBuffer);
        outBuffer = 0;
    }
    if(pSwsContext)
    {
        sws_freeContext(pSwsContext);
        pSwsContext = 0;
        qDebug() << "sws_freeContext(pSwsContext)";
    }
    if(pAVFrameRGB32)
    {
        av_frame_free(&pAVFrameRGB32);
        pAVFrame = 0;
        qDebug() << "av_frame_free(pAVFrameRGB888)";
    }
    if(pAVFrame)
    {
        av_frame_free(&pAVFrame);
        pAVFrame = 0;
        qDebug() << "av_frame_free(pAVFrame)";
    }
    if(pAVPacket)
    {
        av_free_packet(pAVPacket);
        pAVPacket = 0;
        qDebug() << "av_free_packet(pAVPacket)";
    }
    if(pAVCodecContext)
    {
        avcodec_close(pAVCodecContext);
        pAVCodecContext = 0;
        qDebug() << "avcodec_close(pAVCodecContext);";
    }
    if(pAVFormatContext)
    {
        avformat_close_input(&pAVFormatContext);
        avformat_free_context(pAVFormatContext);
        pAVFormatContext = 0;
        qDebug() << "avformat_free_context(pAVFormatContext)";
    }
}
