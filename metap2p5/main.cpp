﻿//
// Copyright (c) 2019-2022 yanggaofeng
//
#include "recordmainwindow.h"
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif
#include <QApplication>
#include <yangp2p/YangP2pFactory.h>
#include <video/yangrecordthread.h>
#include <yangutil/sys/YangSysMessageHandle.h>

#include <QTextCodec>

#include "yangutil/buffer/YangVideoEncoderBuffer.h"
#include "yangutil/sys/YangTime.h"
#include "yangutil/sys/YangThread.h"
#include "yangutil/sys/YangLog.h"

#include <iostream>
#include <errno.h>



#include <sys/timeb.h>

UINT64 getCurrentTimeMillis()
{
    timeb t;
    ftime(&t);//获取毫秒

    return t.time * 1000 + t.millitm;
}



#define CHK(condition, errRet)                                                                                                                       \
    do {                                                                                                                                             \
        if (!(condition)) {                                                                                                                          \
            retStatus = (errRet);                                                                                                                    \
            goto CleanUp;                                                                                                                            \
        }                                                                                                                                            \
    } while (FALSE)

int readFile(char* filePath, uint8_t* pBuffer, int32_t* pSize)
{
    int32_t fileLen;
    int retStatus = 0;
    FILE* fp = NULL;

    CHK(filePath != NULL && pSize != NULL, -1);

    errno = 0;
    fp = fopen(filePath,"rb");
    if(fp == NULL) {
        printf("Error no.%d: %s\n", errno, strerror(errno));
    }
    
    CHK(fp != NULL, -2);

    // Get the size of the file
    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);

    if (pBuffer == NULL) {
        // requested the length - set and early return
        CHK(FALSE, 0);
    }
     *pSize = fileLen;

    // Validate the buffer size
    CHK(fileLen <= *pSize, -4);

    // Read the file into memory buffer
    fseek(fp, 0, SEEK_SET);
    CHK(fread(pBuffer, (size_t) fileLen, 1, fp) == 1, -5);

CleanUp:

    if (fp != NULL) {
        fclose(fp);
        fp = NULL;
    }

    return retStatus;
}

YangP2pFactory mf;

void* senderThread(void *arg)
{
    YangSysMessageHandle* sysmessage = (YangSysMessageHandle*)arg;
    UINT32 fileIndex = 0, frameSize;
    const int MAX_PATH_LEN = 4096;
    CHAR filePath[MAX_PATH_LEN + 1];
    const int NUMBER_OF_H264_FRAME_FILES = 403;

    YangFrame pframe;
    uint8_t* tmpbuff = (uint8_t*)calloc(1, 200 * 1024);
    if (tmpbuff == NULL) {
        exit(0);
    }

    int flag = 0;
    while(1) {
        YangVideoEncoderBuffer* txBuf = mf.getTxVideoBuffer(sysmessage);
        if (txBuf) {
            if (flag == 0) {
                yang_usleep(1000 * 1000);
                flag = 1;
            }
            int32_t tmpsize = 0;
            memset(tmpbuff, 0, 200 * 1024);
            fileIndex = fileIndex % NUMBER_OF_H264_FRAME_FILES + 1;
            snprintf(filePath, MAX_PATH_LEN, "C:\\YVR\\webrtc\\metaRTC\\win5b0\\bin\\app_win_debug\\h264SampleFrames\\frame-%03d.h264", fileIndex);
            int ret = readFile(filePath, tmpbuff, &tmpsize);
            if (ret != 0) {
                yang_info("senderThread::failed:%d...size:%d", ret, tmpsize);
                continue;
            }
            pframe.payload = tmpbuff;
            pframe.nb = tmpsize;
            pframe.mediaType = 9;
            pframe.frametype = (fileIndex-1) % 45 == 0 ? 1 : 0;  //  I(1)  P(0)
            // pframe.frametype = 1;
            pframe.uid = 0;
            pframe.dts = getCurrentTimeMillis();
            pframe.pts = pframe.dts;
//            yang_info("senderThread::running...size:%d", tmpsize);
            txBuf->putEVideo(&pframe);
        }
        yang_usleep(40*1000);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#endif


    RecordMainWindow w;
    // YangP2pFactory mf;

    YangSysMessageHandle *sysmessage=mf.createP2pMessageHandle(w.m_hasAudio,w.m_context,&w,&w);

    pthread_t m_thread;
    pthread_create( &m_thread, 0, senderThread, sysmessage);

    w.m_message=sysmessage;
    sysmessage->start();

   YangRecordThread videoThread;
    w.initVideoThread(&videoThread);
    videoThread.start();
    w.show();
    QThread::msleep(200);
    w.initPreview();


    return a.exec();
}
