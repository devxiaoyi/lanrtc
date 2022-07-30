
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

static int32_t myVideoReceiver(yvrtc::YVRFrame *pFrame)
{
    fwrite(pFrame->payload, pFrame->size, 1, fp);
    return 0;
} 

int main(int argc, char *argv[])
{
    yvrtc::YVPlayEngine* yvplay = new yvrtc::YVPlayEngine();

    // pthread_t m_thread;
    // pthread_create(&m_thread, 0, pollingThread, yvplay);
    // pthread_join(m_thread, NULL);

    yvplay->YVPlayStart("webrtc://172.18.0.223:1988/live/livestream");
    fp = fopen("./yvplay_0730.h264", "ab+");

    yvplay->RegisterVideoReceiver(myVideoReceiver);

    while (1)
    {
        Sleep(1 * 1000);
    }

    fclose(fp);

    return 0;
}
