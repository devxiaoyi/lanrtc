#include <yangp2p/YangP2pFactory.h>
#include <yvrtc_interface.h>
#include <yangplayer/YangPlayerHandle.h>
#include <iostream>
#include <string>

static YangP2pFactory *g_p2p = NULL;
static YangPlayerHandle *g_player = nullptr;

yvrtc::YVRTCEngine::YVRTCEngine()
{
    g_p2p = new YangP2pFactory();
    g_p2p->init();
}

yvrtc::YVRTCEngine::~YVRTCEngine()
{
    if (g_p2p)
    {
        delete (g_p2p);
    }
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
    if (g_player == NULL)
        g_player = YangPlayerHandle::createPlayerHandle();
}

yvrtc::YVPlayEngine::~YVPlayEngine()
{
    if (g_player == NULL)
        delete(g_player);
}

int32_t yvrtc::YVPlayEngine::YVPlayStart(std::string url)
{
    int ret = -1;
    if (g_player->play((char*)url.c_str()) == Yang_Ok)
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

int32_t yvrtc::YVPlayEngine::PollVideoFrame(YVRFrame *pFrame)
{
    int32_t ret = -1;
    if (nullptr != g_player)
    {
        YangFrame Frame;
        Frame.payload = pFrame->payload;
        ret = g_player->getVideoFrame(&Frame);
        pFrame->frameType = (VideoFrameType)Frame.frametype;
        pFrame->size = Frame.nb;
        pFrame->timestamp = Frame.dts;
        pFrame->uid = Frame.uid;
    }
    return ret;
}
