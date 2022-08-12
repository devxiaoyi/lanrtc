
#include <iostream>
#include <errno.h>
#include <sys/timeb.h>
#include <yvrtc_interface.h>
#include <windows.h>
#include <pthread.h>

uint64_t getCurrentTimeMillis()
{
    timeb t;
    ftime(&t); //获取毫秒

    return t.time * 1000 + t.millitm;
}

#if 0
void *pollingThread(void *arg)
{
    yvrtc::YVPlayEngine* yvplay = (yvrtc::YVPlayEngine*) arg;
    yvplay->YVPlayStart("webrtc://172.18.0.223:1988/live/livestream");

    yvrtc::YVRFrame Frame;

    int32_t ret = 0;

    FILE* fp = fopen("./yvplay_0729.h264", "ab+");

    while (1) {

        ret = yvplay->PollVideoFrame(&Frame);
        if (ret == 0 && Frame.size > 0) {
            fwrite(Frame.payload, Frame.size, 1, fp);
        }

        Sleep(10);
    }
    fclose(fp);
}
#endif


FILE* fp = NULL;

static int32_t myVideoReceiver(yvrtc::YVRFrame *pFrame, void* user)
{
    fwrite(pFrame->payload, pFrame->size, 1, fp);

    return 0;
} 

static int32_t myDataReceiver(yvrtc::YVRFrame *pFrame, void* user)
{
    std::cout << pFrame->payload << std::endl;
    //fwrite(pFrame->payload, pFrame->size, 1, fp);

    return 0;
} 

int main(int argc, char *argv[])
{
    yvrtc::YVPlayEngine* yvplay = new yvrtc::YVPlayEngine();

    // pthread_t m_thread;
    // pthread_create(&m_thread, 0, pollingThread, yvplay);
    // pthread_join(m_thread, NULL);

    yvplay->RegisterVideoReceiver(myVideoReceiver, NULL);
    yvplay->RegisterDataReceiver(myDataReceiver, NULL);

    yvplay->YVPlayStart("webrtc://172.18.0.27:1988/live/livestream");
    remove("./yvplay_debug.h264");
    fp = fopen("./yvplay_debug.h264", "ab+");

    while (1)
    {
        Sleep(1 * 1000);

        yvrtc::YVRFrame pData;
        std::string datastr = "qwertyu_for_player";
        pData.payload = (uint8_t*)(datastr.c_str());
        pData.size = datastr.length();
        yvplay->putDataFrame(&pData);
    }

    fclose(fp);

    return 0;
}
