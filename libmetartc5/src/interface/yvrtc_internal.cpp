#include <yangp2p/YangP2pFactory.h>
#include <yvrtc_interface.h>
#include <yangplayer/YangPlayerHandle.h>
#include <iostream>
#include <string>

static std::unique_ptr<YangP2pFactory> g_p2p;
static std::unique_ptr<YangPlayerHandle> g_player;

yvrtc::YVRTCEngine::YVRTCEngine()
{
    if (!g_p2p)
    {
        g_p2p.reset(new YangP2pFactory());
        g_p2p->init();
    }
}

yvrtc::YVRTCEngine::~YVRTCEngine()
{
}

int32_t yvrtc::YVRTCEngine::putVideoFrame(YVRFrame *pFrame)
{
    int32_t ret = 0;
    YangFrame YFrame;
    YFrame.payload = pFrame->payload;
    YFrame.nb = pFrame->size;
    YFrame.mediaType = 9;
    YFrame.dts = pFrame->timestamp;
    YFrame.pts = pFrame->timestamp;
    YFrame.uid = pFrame->uid;
    YFrame.frametype = pFrame->frameType;
    if (g_p2p)
    {
        ret = g_p2p->putTxVideo(&YFrame);
    }
    else
    {
        ret = -1;
    }
    return ret;
}

yvrtc::YVPlayEngine::YVPlayEngine()
{
    if (!g_player)
        g_player.reset(YangPlayerHandle::createPlayerHandle());
}

yvrtc::YVPlayEngine::~YVPlayEngine()
{

}

int32_t yvrtc::YVPlayEngine::YVPlayStart(std::string url)
{
    int ret = -1;
    if (g_player->play((char *)url.c_str()) == Yang_Ok)
    {
        ret = 0;
    }
    return ret;
}

int32_t yvrtc::YVPlayEngine::YVPlayStop()
{
    if (nullptr != g_player)
    {
        g_player->stopPlay();
    }
    return 0;
}

#if 0
int32_t yvrtc::YVPlayEngine::PollVideoFrame(YVRFrame *pFrame)
{
    int32_t ret = -1;
    if (nullptr != g_player)
    {
        YangFrame Frame = {0};
        ret = g_player->getVideoFrame(&Frame);
        if (ret == 0) {
            pFrame->payload = Frame.payload;
            pFrame->frameType = (VideoFrameType)Frame.frametype;
            pFrame->size = Frame.nb;
            pFrame->timestamp = Frame.dts;
            pFrame->uid = Frame.uid;
        }
        else {
            pFrame->payload = nullptr;
            pFrame->frameType = VideoFrameUnknow;
            pFrame->size = 0;
            pFrame->timestamp = 0;
            pFrame->uid = 0;
        }
    }
    return ret;
}
#endif

static int32_t (*pVideoReceiver)(yvrtc::YVRFrame *pFrame);

static int32_t interVideoReceiver(YangFrame *pFrame)
{
    yvrtc::YVRFrame Frame;
    Frame.frameType = (yvrtc::VideoFrameType)pFrame->frametype;
    Frame.payload = pFrame->payload;
    Frame.size = pFrame->nb;
    Frame.timestamp = pFrame->pts;
    Frame.uid = pFrame->uid;
    pVideoReceiver(&Frame);
    return 0;
}

int32_t yvrtc::YVPlayEngine::RegisterVideoReceiver(int32_t (*receiver)(YVRFrame *pFrame))
{
    if (nullptr != g_player)
    {
        pVideoReceiver = receiver;
        g_player->setVideoReceiver(interVideoReceiver);
    }
    return 0;
}
