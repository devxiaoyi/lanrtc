﻿
#include <yangp2p/YangP2pFactory.h>

#include <iostream>
#include <errno.h>
#include <sys/timeb.h>

typedef struct
{
    int32_t mediaType;
    int32_t uid;
    int32_t frametype;
    int32_t nb;
    int64_t pts;
    int64_t dts;
    uint8_t *payload;
} RTCFrame;

UINT64 getCurrentTimeMillis()
{
    timeb t;
    ftime(&t); //获取毫秒

    return t.time * 1000 + t.millitm;
}

#define CHK(condition, errRet)    \
    do                            \
    {                             \
        if (!(condition))         \
        {                         \
            retStatus = (errRet); \
            goto CleanUp;         \
        }                         \
    } while (FALSE)

int readFile(char *filePath, uint8_t *pBuffer, int32_t *pSize)
{
    int32_t fileLen;
    int retStatus = 0;
    FILE *fp = NULL;

    CHK(filePath != NULL && pSize != NULL, -1);

    errno = 0;
    fp = fopen(filePath, "rb");
    if (fp == NULL)
    {
        printf("Error no.%d: %s\n", errno, strerror(errno));
    }

    CHK(fp != NULL, -2);

    // Get the size of the file
    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);

    if (pBuffer == NULL)
    {
        // requested the length - set and early return
        CHK(FALSE, 0);
    }
    *pSize = fileLen;

    // Validate the buffer size
    CHK(fileLen <= *pSize, -4);

    // Read the file into memory buffer
    fseek(fp, 0, SEEK_SET);
    CHK(fread(pBuffer, (size_t)fileLen, 1, fp) == 1, -5);

CleanUp:

    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }

    return retStatus;
}

YangP2pFactory *mf;

void *senderThread(void *arg)
{
    UINT32 fileIndex = 0, frameSize;
    const int MAX_PATH_LEN = 4096;
    CHAR filePath[MAX_PATH_LEN + 1];
    const int NUMBER_OF_H264_FRAME_FILES = 403;

    YangFrame pframe;
    const int buffLen = 120 * 1024 * 1024;
    uint8_t *tmpbuff = (uint8_t *)calloc(1, buffLen);
    if (tmpbuff == NULL)
    {
        exit(0);
    }
    int32_t tmpsize = 0;
    FILE *pFile;
    int flag = 0;
    int offset = 0;
    int ret = -1;
    while (1)
    {
        if (flag == 0)
        {
            snprintf(filePath, MAX_PATH_LEN, "C:\\YVR\\webrtc\\metaRTC\\win5b0\\bin\\app_win_debug\\alvr_server_out_small.h264");
            memset(tmpbuff, 0, buffLen);
            int ret = readFile(filePath, tmpbuff, &tmpsize);
            if (ret != 0)
            {
                printf("senderThread::failed:%d...size:%d\n", ret, tmpsize);
            }

            pFile = fopen("C:\\YVR\\webrtc\\metaRTC\\win5b0\\bin\\app_win_debug\\alvr_server_out_small.txt", "r");
            if (pFile == NULL)
                perror("Error opening file");

            flag = 1;
        }

        char mystring[100];
        int frameSize = 0;
        if (pFile && fgets(mystring, 100, pFile) != NULL)
        {
            // printf("alvr_server_out_small size:%s\n",mystring);
            frameSize = atoi(mystring);
        }
        pframe.payload = tmpbuff + offset;
        pframe.nb = frameSize;
        pframe.mediaType = 9;
        pframe.frametype = fileIndex++ % 180 == 0 ? 1 : 0; //  I(1)  P(0)
        pframe.uid = 0;
        pframe.dts = getCurrentTimeMillis();
        pframe.pts = pframe.dts;
        ret = mf->putTxVideo(&pframe);
        offset += frameSize;

        Sleep(11);
    }
    if (pFile)
        fclose(pFile);
}

int main(int argc, char *argv[])
{
    mf = new YangP2pFactory();
    mf->init();

    pthread_t m_thread;
    pthread_create(&m_thread, 0, senderThread, NULL);

    pthread_join(m_thread, NULL);

    return 0;
}
