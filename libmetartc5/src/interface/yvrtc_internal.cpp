#include <yangp2p/YangP2pFactory.h>
#include <yvrtc_interface.h>
#include <yangplayer/YangPlayerHandle.h>
#include <yangutil/yangavtype.h>
#include <iostream>
#include <string>


/*==================================================================
  ---------------------  RTCEngine  -------------------------------
===================================================================*/

static std::unique_ptr<YangP2pFactory> g_p2p;

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
    g_p2p.reset();
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

int32_t yvrtc::YVRTCEngine::putDataFrame(YVRFrame *pFrame)
{
    int32_t ret = 0;
    YangFrame YFrame = {0};
    YFrame.payload = pFrame->payload;
    YFrame.nb = pFrame->size;
    YFrame.mediaType = YANG_DATA_CHANNEL_BINARY;
    if (g_p2p)
    {
        ret = g_p2p->putTxData(&YFrame);
    }
    else
    {
        ret = -1;
    }
    return ret;
}

static int32_t (*pEngineDataReceiver)(yvrtc::YVRFrame *pFrame, void* user);
static void* pEngineDataReceiverUser = nullptr;

static void engineDataReceiver(void *context, YangFrame *pFrame)
{
    yvrtc::YVRFrame Frame = {0};
    Frame.payload = pFrame->payload;
    Frame.size = pFrame->nb;
    Frame.uid = pFrame->uid;
    if (pEngineDataReceiver) {
        pEngineDataReceiver(&Frame, pEngineDataReceiverUser);
    }
}

int32_t yvrtc::YVRTCEngine::RegisterDataReceiver(int32_t (*receiver)(YVRFrame *pFrame, void* pUser), void* user)
{
    if (nullptr != g_p2p)
    {
        pEngineDataReceiver = receiver;
        pEngineDataReceiverUser = user;
        g_p2p->w->setDataReceiver(engineDataReceiver);
    }
    return 0;
}


/*==================================================================
  ---------------------  PlayEngine  -------------------------------
===================================================================*/

static std::unique_ptr<YangPlayerHandle> g_player;

yvrtc::YVPlayEngine::YVPlayEngine()
{
    g_player.reset(YangPlayerHandle::createPlayerHandle());
}

yvrtc::YVPlayEngine::~YVPlayEngine()
{
    g_player.reset();
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
        g_player.reset();
    }
    return 0;
}

static int32_t (*pVideoReceiver)(yvrtc::YVRFrame *pFrame, void* user);
static void* pVideoReceiverUser = nullptr;

static int32_t interVideoReceiver(YangFrame *pFrame)
{
    yvrtc::YVRFrame Frame;
    Frame.frameType = (yvrtc::VideoFrameType)pFrame->frametype;
    Frame.payload = pFrame->payload;
    Frame.size = pFrame->nb;
    Frame.timestamp = pFrame->pts;
    Frame.uid = pFrame->uid;
    if (pVideoReceiver) {
        pVideoReceiver(&Frame, pVideoReceiverUser);
    }
    return 0;
}

int32_t yvrtc::YVPlayEngine::RegisterVideoReceiver(int32_t (*receiver)(YVRFrame *pFrame, void* pUser), void* user)
{
    if (nullptr != g_player)
    {
        pVideoReceiver = receiver;
        pVideoReceiverUser = user;
        g_player->setVideoReceiver(interVideoReceiver);
    }
    return 0;
}

static int32_t (*pDataReceiver)(yvrtc::YVRFrame *pFrame, void* user);
static void* pDataReceiverUser = nullptr;

static int32_t interDataReceiver(YangFrame *pFrame)
{
    yvrtc::YVRFrame Frame = {0};
    Frame.payload = pFrame->payload;
    Frame.size = pFrame->nb;
    Frame.uid = pFrame->uid;
    if (pDataReceiver) {
        pDataReceiver(&Frame, pDataReceiverUser);
    }
    return 0;
}

int32_t yvrtc::YVPlayEngine::RegisterDataReceiver(int32_t (*receiver)(YVRFrame *pFrame, void* pUser), void* user)
{
    if (nullptr != g_player)
    {
        pDataReceiver = receiver;
        pDataReceiverUser = user;
        g_player->setDataReceiver(interDataReceiver);
    }
    return 0;
}

int32_t yvrtc::YVPlayEngine::putDataFrame(YVRFrame *pFrame)
{
    int32_t ret = 0;
    YangFrame YFrame = {0};
    YFrame.payload = pFrame->payload;
    YFrame.nb = pFrame->size;
    YFrame.mediaType = YANG_DATA_CHANNEL_BINARY;
    if (g_player)
    {
        ret = g_player->putTxData(&YFrame);
    }
    else
    {
        ret = -1;
    }
    return ret;
}
